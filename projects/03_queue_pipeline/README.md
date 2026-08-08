# Project 03 — Queue Pipeline

A producer generates deterministic `sensor_sample_t` values and sends each
value through a FreeRTOS queue. A consumer blocks on the queue and logs samples
in order. No physical sensor is required.

Build, upload and monitor at 115200. Expected: sequence numbers increase every
500 ms. Reduce the queue length or slow the consumer to observe backpressure.

Review: Does a queue copy its item? What happens when it is full? Why is
`portMAX_DELAY` appropriate for the consumer but not necessarily the producer?
