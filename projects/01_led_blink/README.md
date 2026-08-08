# Project 01 — Periodic LED Blink

The first lab creates one FreeRTOS task that toggles an LED every 500 ms. The
task uses `vTaskDelayUntil()` so it blocks between deadlines instead of wasting
CPU time in a busy loop.

## What you learn

- Build and flash an ESP-IDF application through PlatformIO
- Configure an ESP32 GPIO as a digital output
- Create a FreeRTOS task with `xTaskCreate()`
- Use a periodic delay and understand the Blocked task state
- Call a reusable ESP-IDF component through its public API

## Hardware

- ESP32 development board
- LED
- 220–330 ohm resistor
- Breadboard and two jumper wires
- USB data cable

## Wiring

Disconnect USB power while changing the wiring.

```text
ESP32 GPIO 2 ---- 220–330 ohm resistor ---- LED anode (+)
ESP32 GND --------------------------------- LED cathode (-)
```

The longer LED leg is normally the anode. The flat edge on the LED body marks
the cathode. Never connect an LED directly between GPIO and ground without a
current-limiting resistor.

If GPIO 2 affects booting on your particular board, use another output-capable
GPIO such as GPIO 4 and update `STATUS_LED_GPIO` in `platformio.ini`. Avoid
input-only GPIOs 34–39.

## Build, flash and monitor

Open this directory in VS Code and use the PlatformIO toolbar, or run:

```bash
pio run
pio run --target upload
pio device monitor
```

If PlatformIO cannot find the port, connect the board with a USB **data** cable
and inspect available devices with `pio device list`. On Windows, the port will
normally look like `COM3` or another `COM` number.

## Expected behaviour

- The LED changes state every 500 ms.
- One full on/off cycle takes approximately one second.
- The serial monitor prints messages similar to:

```text
I (...) led_blink: Starting periodic LED task on GPIO 2
I (...) led_blink: LED ON
I (...) led_blink: LED OFF
```

Press `Ctrl+C` to close the serial monitor.

## Architecture

```text
app_main
  ├── initializes status_led
  └── creates led_task
          ├── toggles status_led
          ├── logs the logical state
          └── blocks until the next 500 ms deadline
```

`../../components/status_led` owns GPIO details. The application owns the task
period and scheduling. This separation allows later projects to reuse the LED
without copying its driver code.

## Code observations

- `app_main()` is already executed by an ESP-IDF FreeRTOS task.
- `xTaskCreate()` creates a separate application task.
- `vTaskDelayUntil()` maintains a regular period better than repeatedly calling
  `vTaskDelay()` after variable-duration work.
- Task stack sizes in ESP-IDF are specified in **bytes**, unlike upstream
  FreeRTOS ports that commonly express them in stack words.
- `ESP_ERROR_CHECK()` stops execution on an unexpected initialization failure,
  which makes a first lab's failures visible.

## Experiments

1. Change `BLINK_PERIOD_MS` to 100 and observe the result.
2. Change it to 1000 and calculate the full on/off cycle time.
3. Replace `vTaskDelayUntil()` temporarily with an empty busy loop. Observe why
   this is poor task behaviour, then restore the blocking delay.
4. Move the LED to GPIO 4 and change the build flag in `platformio.ini`.

## Completion checklist

- [ ] Project builds without errors
- [ ] Firmware uploads successfully
- [ ] LED toggles at the expected rate
- [ ] Serial output reports ON and OFF states
- [ ] You can explain why the task blocks between toggles
- [ ] You completed at least one timing experiment

## Interview checks

1. Why is a blocking delay preferable to busy waiting in this task?
2. What states does `led_task` alternate between?
3. Why is the GPIO implementation kept outside `main.c`?
4. What is the difference between `vTaskDelay()` and `vTaskDelayUntil()`?

