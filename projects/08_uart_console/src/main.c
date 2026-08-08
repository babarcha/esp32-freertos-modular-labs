#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "status_led.h"

#ifndef STATUS_LED_GPIO
#define STATUS_LED_GPIO 2
#endif

static void execute(char *line)
{
    if (strcmp(line, "help") == 0) ESP_LOGI("console", "Commands: help, led on, led off, status");
    else if (strcmp(line, "led on") == 0) ESP_ERROR_CHECK(status_led_set(true));
    else if (strcmp(line, "led off") == 0) ESP_ERROR_CHECK(status_led_set(false));
    else if (strcmp(line, "status") == 0) ESP_LOGI("console", "LED is %s", status_led_is_on() ? "on" : "off");
    else ESP_LOGW("console", "Unknown command: %s", line);
}

static void console_task(void *arg)
{
    (void)arg;
    char line[64];
    size_t used = 0;
    ESP_LOGI("console", "Type help then press Enter");
    while (true) {
        uint8_t byte;
        int count = uart_read_bytes(UART_NUM_0, &byte, 1, pdMS_TO_TICKS(100));
        if (count != 1) continue;
        if (byte == '\r' || byte == '\n') {
            if (used > 0) { line[used] = '\0'; execute(line); used = 0; }
        } else if (used < sizeof(line) - 1) {
            line[used++] = (char)byte;
        } else {
            used = 0;
            ESP_LOGW("console", "Command too long");
        }
    }
}

void app_main(void)
{
    const status_led_config_t led = {.gpio_num = STATUS_LED_GPIO, .active_high = true};
    ESP_ERROR_CHECK(status_led_init(&led));
    const uart_config_t uart = {
        .baud_rate = 115200, .data_bits = UART_DATA_8_BITS, .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1, .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0));
    configASSERT(xTaskCreate(console_task, "console", 4096, NULL, 5, NULL) == pdPASS);
}
