#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sensor_source.h"

static QueueHandle_t s_samples;

static void producer(void *arg)
{
    (void)arg;
    while (true) {
        sensor_sample_t sample = sensor_source_next();
        if (xQueueSend(s_samples, &sample, pdMS_TO_TICKS(100)) != pdPASS)
            ESP_LOGW("producer", "Queue full; sample dropped");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void consumer(void *arg)
{
    (void)arg;
    sensor_sample_t sample;
    while (true) {
        if (xQueueReceive(s_samples, &sample, portMAX_DELAY) == pdPASS)
            ESP_LOGI("consumer", "sample=%lu value=%ld.%03ld",
                     (unsigned long)sample.sequence, (long)(sample.value_milli / 1000),
                     (long)(sample.value_milli % 1000));
    }
}

void app_main(void)
{
    sensor_source_reset();
    s_samples = xQueueCreate(8, sizeof(sensor_sample_t));
    configASSERT(s_samples != NULL);
    configASSERT(xTaskCreate(producer, "producer", 2048, NULL, 4, NULL) == pdPASS);
    configASSERT(xTaskCreate(consumer, "consumer", 3072, NULL, 5, NULL) == pdPASS);
}
