#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_metrics_log_task(const char *label, TaskHandle_t task);
