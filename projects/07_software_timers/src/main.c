#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "status_led.h"

#ifndef STATUS_LED_GPIO
#define STATUS_LED_GPIO 2
#endif

static void blink_callback(TimerHandle_t timer)
{
    (void)timer;
    if (status_led_toggle() != ESP_OK)
        ESP_LOGE("timer", "LED toggle failed");
}

static void stop_callback(TimerHandle_t timer)
{
    TimerHandle_t blink = pvTimerGetTimerID(timer);
    xTimerStop(blink, 0);
    status_led_set(false);
    ESP_LOGI("timer", "One-shot timer stopped blinking");
}

void app_main(void)
{
    const status_led_config_t led = {.gpio_num = STATUS_LED_GPIO, .active_high = true};
    ESP_ERROR_CHECK(status_led_init(&led));
    TimerHandle_t blink = xTimerCreate("blink", pdMS_TO_TICKS(250), pdTRUE, NULL, blink_callback);
    TimerHandle_t stop = xTimerCreate("stop", pdMS_TO_TICKS(5000), pdFALSE, blink, stop_callback);
    configASSERT(blink != NULL && stop != NULL);
    configASSERT(xTimerStart(blink, 0) == pdPASS);
    configASSERT(xTimerStart(stop, 0) == pdPASS);
}
