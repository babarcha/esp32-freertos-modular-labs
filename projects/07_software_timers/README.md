# Project 07 — Software Timers

An auto-reload timer toggles the LED every 250 ms. A one-shot timer fires after
five seconds, stops the repeating timer and leaves the LED off.

Build, upload and monitor at 115200. Expected: rapid blinking for five seconds,
then a stop message and an off LED.

Review: Which task executes timer callbacks? Why must callbacks not block? What
is the difference between one-shot and auto-reload timers?
