# ESP32 FreeRTOS Modular Labs

Small, independently runnable ESP32 projects that teach FreeRTOS one concept at
a time. Reusable functionality lives in ESP-IDF components so later labs can
combine it into a larger embedded application.

The first labs use **PlatformIO with ESP-IDF**. A later phase will add the native
ESP-IDF workflow without rewriting the reusable components.

## Learning roadmap

| Phase | Project | Main concepts | Reusable result |
|---|---|---|---|
| 1 | `01_led_blink` | GPIO, task creation, periodic blocking | `status_led` |
| 1 | `02_task_scheduling` | Priorities, task states, stack monitoring | `app_metrics` |
| 2 | `03_queue_pipeline` | Queues, producer-consumer design | Message types |
| 2 | `04_task_notifications` | Direct-to-task notifications | Event signalling |
| 3 | `05_mutex_protection` | Race conditions, mutexes | Safe resource wrapper |
| 4 | `06_button_interrupt` | ISR-to-task handoff, debounce | `button_input` |
| 4 | `07_software_timers` | FreeRTOS timers | LED timing controller |
| 5–6 | Later labs | Peripherals and reliable architecture | Sensor-node foundation |

## Repository layout

```text
components/              Reusable ESP-IDF components
projects/                Independently buildable PlatformIO applications
docs/                    Shared hardware and learning notes
```

## Requirements

- ESP32 development board (the initial configuration uses `esp32dev`)
- USB data cable
- One LED, one 220–330 ohm resistor, breadboard and jumper wires
- VS Code with the PlatformIO extension, or PlatformIO Core

## Build the first project

Open `projects/01_led_blink` as the PlatformIO project, or run:

```bash
cd projects/01_led_blink
pio run
pio run --target upload
pio device monitor
```

See the [first project's README](projects/01_led_blink/README.md) for wiring,
configuration, expected output and exercises.

## Design rules

- Each lab demonstrates one small set of concepts.
- Applications depend on reusable components; they do not copy component code.
- ISR code stays short and defers work to tasks.
- Tasks block while idle rather than busy-waiting.
- Public component APIs do not expose unnecessary implementation details.
- Every completed phase includes build instructions, expected behaviour and a
  stable Git tag.

## License

MIT

