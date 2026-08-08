#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_check.h"
#include "esp_log.h"
#include "status_led.h"

#ifndef STATUS_LED_GPIO
#define STATUS_LED_GPIO 2
#endif

#ifndef STATUS_LED_ACTIVE_HIGH
#define STATUS_LED_ACTIVE_HIGH 1
#endif

#define BLINK_PERIOD_MS 500
#define LED_TASK_STACK_SIZE 2048
#define LED_TASK_PRIORITY 5

static const char *TAG = "led_blink";

static void led_task(void *context)
{
    (void)context;
    TickType_t last_wake_time = xTaskGetTickCount();

    while (true) {
        ESP_ERROR_CHECK(status_led_toggle());
        ESP_LOGI(TAG, "LED %s", status_led_is_on() ? "ON" : "OFF");

        vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(BLINK_PERIOD_MS));
    }
}

void app_main(void)
{
    const status_led_config_t led_config = {
        .gpio_num = (gpio_num_t)STATUS_LED_GPIO,
        .active_high = STATUS_LED_ACTIVE_HIGH != 0,
    };

    ESP_ERROR_CHECK(status_led_init(&led_config));
    ESP_LOGI(TAG, "Starting periodic LED task on GPIO %d", STATUS_LED_GPIO);

    const BaseType_t task_created =
        xTaskCreate(led_task, "led_task", LED_TASK_STACK_SIZE, NULL,
                    LED_TASK_PRIORITY, NULL);
    ESP_ERROR_CHECK(task_created == pdPASS ? ESP_OK : ESP_ERR_NO_MEM);
}

