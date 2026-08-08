# Project 02 — Task Scheduling

Runs an LED task at priority 5 and a metrics task at priority 3. The metrics
task reports both priorities and minimum remaining stack space every two
seconds. Observe that both tasks make progress because each blocks between
periods.

Build with `pio run`, upload with `pio run -t upload`, then monitor at 115200.
Expected: a blinking LED and repeated `app_metrics` lines. Experiment by
changing priorities and periods; do not create an endless high-priority loop.

Review: What are Running, Ready and Blocked states? Why does a lower-priority
task still run? What does the stack high-water mark tell you?
