# ESP32 Initial Setup

## Before connecting hardware

1. Check the board label and USB connector.
2. Use a known USB data cable; charge-only cables cannot upload firmware.
3. Place the ESP32 across the breadboard centre gap so pins on both sides remain
   accessible.
4. Disconnect USB power before adding or changing wires.
5. Use only 3.3 V-compatible signals on ESP32 GPIO pins.

## First connection

1. Connect the ESP32 directly to the computer, not through an unpowered hub.
2. Open `projects/01_led_blink` in VS Code.
3. Let PlatformIO install the Espressif platform and toolchain on the first
   build. This can take several minutes.
4. If automatic upload fails, identify the serial port with
   `pio device list` and add `upload_port = COMx` under the environment in
   `platformio.ini`.
5. Some boards require holding **BOOT** when upload begins and releasing it when
   writing starts.

## Safety notes

- Do not connect 5 V directly to a GPIO pin.
- Add a current-limiting resistor in series with every ordinary LED.
- Confirm GPIO numbers from the board's pinout; printed physical pin positions
  and GPIO numbers are not interchangeable.
- Avoid changing strapping-pin levels during reset until you understand their
  boot functions.

