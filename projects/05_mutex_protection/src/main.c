#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_log.h"

static SemaphoreHandle_t s_mutex;
static uint32_t s_counter;

static void counter_task(void *arg)
{
    const char *name = arg;
    for (uint32_t i = 0; i < 1000; ++i) {
        if (xSemaphoreTake(s_mutex, pdMS_TO_TICKS(100)) == pdPASS) {
            ++s_counter;
            xSemaphoreGive(s_mutex);
        } else {
            ESP_LOGW(name, "Mutex timeout");
        }
        taskYIELD();
    }
    ESP_LOGI(name, "Finished; shared counter=%lu", (unsigned long)s_counter);
    vTaskDelete(NULL);
}

void app_main(void)
{
    s_mutex = xSemaphoreCreateMutex();
    configASSERT(s_mutex != NULL);
    configASSERT(xTaskCreate(counter_task, "counter_a", 2048, "counter_a", 4, NULL) == pdPASS);
    configASSERT(xTaskCreate(counter_task, "counter_b", 2048, "counter_b", 4, NULL) == pdPASS);
}
