#include "status_led.h"

#include "driver/gpio.h"
#include "esp_check.h"

static bool s_initialized;
static bool s_is_on;
static status_led_config_t s_config;

static uint32_t physical_level(bool on)
{
    return (uint32_t)(s_config.active_high ? on : !on);
}

esp_err_t status_led_init(const status_led_config_t *config)
{
    ESP_RETURN_ON_FALSE(config != NULL, ESP_ERR_INVALID_ARG, "status_led",
                        "config must not be NULL");
    ESP_RETURN_ON_FALSE(GPIO_IS_VALID_OUTPUT_GPIO(config->gpio_num),
                        ESP_ERR_INVALID_ARG, "status_led",
                        "GPIO is not output-capable");

    const gpio_config_t io_config = {
        .pin_bit_mask = 1ULL << config->gpio_num,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    ESP_RETURN_ON_ERROR(gpio_config(&io_config), "status_led",
                        "failed to configure GPIO");

    s_config = *config;
    s_initialized = true;
    s_is_on = false;
    return gpio_set_level(s_config.gpio_num, physical_level(false));
}

esp_err_t status_led_set(bool on)
{
    ESP_RETURN_ON_FALSE(s_initialized, ESP_ERR_INVALID_STATE, "status_led",
                        "component is not initialized");

    ESP_RETURN_ON_ERROR(gpio_set_level(s_config.gpio_num, physical_level(on)),
                        "status_led", "failed to set GPIO level");
    s_is_on = on;
    return ESP_OK;
}

esp_err_t status_led_toggle(void)
{
    return status_led_set(!s_is_on);
}

bool status_led_is_on(void)
{
    return s_initialized && s_is_on;
}

esp_err_t status_led_deinit(void)
{
    ESP_RETURN_ON_FALSE(s_initialized, ESP_ERR_INVALID_STATE, "status_led",
                        "component is not initialized");

    ESP_RETURN_ON_ERROR(status_led_set(false), "status_led",
                        "failed to turn LED off");
    ESP_RETURN_ON_ERROR(gpio_reset_pin(s_config.gpio_num), "status_led",
                        "failed to reset GPIO");
    s_initialized = false;
    return ESP_OK;
}
