#include "sensor_source.h"

static uint32_t s_sequence;

void sensor_source_reset(void)
{
    s_sequence = 0;
}

sensor_sample_t sensor_source_next(void)
{
    sensor_sample_t sample = {
        .sequence = s_sequence,
        .value_milli = 20000 + (int32_t)((s_sequence % 21U) * 125U),
    };
    ++s_sequence;
    return sample;
}
