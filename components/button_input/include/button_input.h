#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"

typedef struct {
    gpio_num_t gpio_num;
    bool active_low;
    uint32_t debounce_ms;
} button_input_config_t;

esp_err_t button_input_init(const button_input_config_t *config, TaskHandle_t notify_task);
bool button_input_accept_event(void);
esp_err_t button_input_deinit(void);
