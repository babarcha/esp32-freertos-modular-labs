#pragma once

#include <stdint.h>

typedef struct {
    uint32_t sequence;
    int32_t value_milli;
} sensor_sample_t;

void sensor_source_reset(void);
sensor_sample_t sensor_source_next(void);
