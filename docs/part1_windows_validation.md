# Part 1 — Windows Compilation and Hardware Validation

Run this plan only after cloning the complete Part 1 repository. Test one lab at
a time; each directory is an independent PlatformIO project.

## Preparation

1. Install VS Code and the PlatformIO extension.
2. Connect the ESP32 with a USB data cable and run `pio device list`.
3. Disconnect USB before changing wires.
4. Wire the LED as described by Project 01. For Project 06, add a normally-open
   push button between GPIO 18 and GND; the internal pull-up is enabled.
5. Use a serial terminal that can send text for Project 08.

## Standard commands

Run these from each project directory:

```powershell
pio run
pio run --target upload
pio device monitor
```

If automatic port detection fails, add `upload_port = COMx` and
`monitor_port = COMx` to that project's `platformio.ini`.

## Test record

| Lab | Build | Upload | Behaviour | Key check |
|---|---|---|---|---|
| 01 LED blink | ☐ | ☐ | ☐ | LED changes every 500 ms |
| 02 Scheduling | ☐ | ☐ | ☐ | Two tasks log stack/priority data |
| 03 Queue pipeline | ☐ | ☐ | ☐ | Ordered simulated samples arrive |
| 04 Notifications | ☐ | ☐ | ☐ | Worker wakes once per second |
| 05 Mutex | ☐ | ☐ | ☐ | Two tasks safely reach 2000 total |
| 06 Button interrupt | ☐ | ☐ | ☐ | One LED toggle per physical press |
| 07 Timers | ☐ | ☐ | ☐ | Blinks for 5 s, then stops off |
| 08 UART console | ☐ | ☐ | ☐ | All documented commands respond |

## Failure capture

For each failure, record the lab, board name, COM port, full build error or
serial exception, wiring changes and the last command run. Fix one failure at a
time and rerun that lab before continuing.

## Completion gate

Part 1 becomes hardware validated only when all 32 boxes above are checked.
Afterward, commit only necessary fixes and tag the validated revision
`part-1-hardware-validated`.
