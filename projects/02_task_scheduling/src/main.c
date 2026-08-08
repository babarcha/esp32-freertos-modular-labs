#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_metrics.h"
#include "esp_log.h"
#include "status_led.h"

#ifndef STATUS_LED_GPIO
#define STATUS_LED_GPIO 2
#endif

static void led_task(void *arg)
{
    (void)arg;
    TickType_t wake = xTaskGetTickCount();
    while (true) {
        ESP_ERROR_CHECK(status_led_toggle());
        vTaskDelayUntil(&wake, pdMS_TO_TICKS(500));
    }
}

static void metrics_task(void *arg)
{
    TaskHandle_t led = arg;
    while (true) {
        app_metrics_log_task("LED task", led);
        app_metrics_log_task("Metrics task", NULL);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    const status_led_config_t config = {.gpio_num = STATUS_LED_GPIO, .active_high = true};
    ESP_ERROR_CHECK(status_led_init(&config));
    TaskHandle_t led = NULL;
    configASSERT(xTaskCreate(led_task, "led", 2048, NULL, 5, &led) == pdPASS);
    configASSERT(xTaskCreate(metrics_task, "metrics", 3072, led, 3, NULL) == pdPASS);
    ESP_LOGI("scheduling", "Two periodic tasks started");
}
