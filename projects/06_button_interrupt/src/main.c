#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "button_input.h"
#include "esp_log.h"
#include "status_led.h"

#ifndef BUTTON_GPIO
#define BUTTON_GPIO 18
#endif
#ifndef STATUS_LED_GPIO
#define STATUS_LED_GPIO 2
#endif

static void button_task(void *arg)
{
    (void)arg;
    const button_input_config_t button = {
        .gpio_num = BUTTON_GPIO, .active_low = true, .debounce_ms = 50,
    };
    ESP_ERROR_CHECK(button_input_init(&button, xTaskGetCurrentTaskHandle()));
    while (true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (button_input_accept_event()) {
            ESP_ERROR_CHECK(status_led_toggle());
            ESP_LOGI("button", "Accepted press; LED=%s", status_led_is_on() ? "on" : "off");
        }
    }
}

void app_main(void)
{
    const status_led_config_t led = {.gpio_num = STATUS_LED_GPIO, .active_high = true};
    ESP_ERROR_CHECK(status_led_init(&led));
    configASSERT(xTaskCreate(button_task, "button", 3072, NULL, 6, NULL) == pdPASS);
}
