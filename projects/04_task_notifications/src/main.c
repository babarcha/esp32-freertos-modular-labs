#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static TaskHandle_t s_worker;

static void worker(void *arg)
{
    (void)arg;
    while (true) {
        uint32_t events = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        ESP_LOGI("worker", "Handled %lu event(s)", (unsigned long)events);
    }
}

static void event_source(void *arg)
{
    (void)arg;
    while (true) {
        xTaskNotifyGive(s_worker);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    configASSERT(xTaskCreate(worker, "worker", 2048, NULL, 5, &s_worker) == pdPASS);
    configASSERT(xTaskCreate(event_source, "event_source", 2048, NULL, 4, NULL) == pdPASS);
}
