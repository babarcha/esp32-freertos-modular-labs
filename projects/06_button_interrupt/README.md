# Project 06 — Button Interrupt and Debounce

Wire a normally-open button between GPIO 18 and GND. The reusable component
enables the internal pull-up. A falling-edge ISR only gives a task notification;
the task performs debounce and toggles the LED.

Build, upload and monitor at 115200. Expected: one accepted log and one LED
toggle for each deliberate press. Change `debounce_ms` to compare behavior.

Review: Why must the ISR stay short? Why use `vTaskNotifyGiveFromISR()`? What
causes contact bounce, and why is application work done in the task?
