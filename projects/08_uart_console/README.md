# Project 08 — UART Command Console

The console task reads UART0 without busy waiting, accumulates a bounded line
and dispatches four commands: `help`, `led on`, `led off` and `status`.

Build, upload and open an interactive 115200-baud monitor. Enter each command
followed by Enter. Unknown and overlong commands must be handled safely.

Review: Why is the input buffer bounded? What happens on CRLF input? How would
you separate parsing from UART transport in a larger product?
