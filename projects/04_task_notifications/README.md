# Project 04 — Task Notifications

An event-source task gives a direct task notification once per second. The
worker consumes the notification count and otherwise uses no CPU.

Build, upload and monitor at 115200. Expected: `Handled 1 event(s)` once per
second. Increase the producer rate and add work to the consumer to see events
coalesce into a count.

Review: When is a task notification preferable to a queue? What information is
lost compared with a queue carrying structured messages?
