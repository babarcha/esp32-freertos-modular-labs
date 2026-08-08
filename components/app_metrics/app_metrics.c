#include "app_metrics.h"

#include "esp_log.h"

void app_metrics_log_task(const char *label, TaskHandle_t task)
{
    TaskHandle_t target = task == NULL ? xTaskGetCurrentTaskHandle() : task;
    ESP_LOGI("app_metrics", "%s: priority=%u stack_free_min=%u bytes",
             label, (unsigned)uxTaskPriorityGet(target),
             (unsigned)uxTaskGetStackHighWaterMark(target));
}
