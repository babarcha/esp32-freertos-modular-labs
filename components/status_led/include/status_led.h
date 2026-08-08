#pragma once

#include <stdbool.h>

#include "esp_err.h"
#include "hal/gpio_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Configuration for a single digital status LED. */
typedef struct {
    gpio_num_t gpio_num;
    bool active_high;
} status_led_config_t;

/** Configure the LED GPIO and leave the LED off. */
esp_err_t status_led_init(const status_led_config_t *config);

/** Set the logical LED state. The component handles active-low wiring. */
esp_err_t status_led_set(bool on);

/** Invert the current logical LED state. */
esp_err_t status_led_toggle(void);

/** Return the last logical state requested through this component. */
bool status_led_is_on(void);

/** Turn the LED off and reset its GPIO configuration. */
esp_err_t status_led_deinit(void);

#ifdef __cplusplus
}
#endif

