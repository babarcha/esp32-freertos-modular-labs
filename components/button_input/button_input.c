#include "button_input.h"

#include <stdbool.h>
#include "driver/gpio.h"
#include "esp_check.h"
#include "esp_timer.h"

static button_input_config_t s_config;
static TaskHandle_t s_notify_task;
static int64_t s_last_event_us;
static bool s_initialized;

static void IRAM_ATTR button_isr(void *context)
{
    (void)context;
    BaseType_t higher_priority_woken = pdFALSE;
    vTaskNotifyGiveFromISR(s_notify_task, &higher_priority_woken);
    portYIELD_FROM_ISR(higher_priority_woken);
}

esp_err_t button_input_init(const button_input_config_t *config, TaskHandle_t notify_task)
{
    ESP_RETURN_ON_FALSE(config != NULL && notify_task != NULL, ESP_ERR_INVALID_ARG,
                        "button_input", "invalid configuration");
    ESP_RETURN_ON_FALSE(GPIO_IS_VALID_GPIO(config->gpio_num), ESP_ERR_INVALID_ARG,
                        "button_input", "invalid GPIO");
    const gpio_config_t gpio_config = {
        .pin_bit_mask = 1ULL << config->gpio_num,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = config->active_low ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .pull_down_en = config->active_low ? GPIO_PULLDOWN_DISABLE : GPIO_PULLDOWN_ENABLE,
        .intr_type = config->active_low ? GPIO_INTR_NEGEDGE : GPIO_INTR_POSEDGE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&gpio_config), "button_input", "GPIO setup failed");
    esp_err_t result = gpio_install_isr_service(0);
    ESP_RETURN_ON_FALSE(result == ESP_OK || result == ESP_ERR_INVALID_STATE, result,
                        "button_input", "ISR service setup failed");
    ESP_RETURN_ON_ERROR(gpio_isr_handler_add(config->gpio_num, button_isr, NULL),
                        "button_input", "ISR handler setup failed");
    s_config = *config;
    s_notify_task = notify_task;
    s_last_event_us = 0;
    s_initialized = true;
    return ESP_OK;
}

bool button_input_accept_event(void)
{
    if (!s_initialized) return false;
    const int64_t now = esp_timer_get_time();
    const int64_t debounce_us = (int64_t)s_config.debounce_ms * 1000;
    if (s_last_event_us != 0 && now - s_last_event_us < debounce_us) return false;
    s_last_event_us = now;
    return true;
}

esp_err_t button_input_deinit(void)
{
    ESP_RETURN_ON_FALSE(s_initialized, ESP_ERR_INVALID_STATE, "button_input", "not initialized");
    ESP_RETURN_ON_ERROR(gpio_isr_handler_remove(s_config.gpio_num), "button_input", "remove failed");
    s_initialized = false;
    s_notify_task = NULL;
    return gpio_reset_pin(s_config.gpio_num);
}
