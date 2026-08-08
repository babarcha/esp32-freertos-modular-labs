# Project 05 — Mutex Protection

Two equal-priority tasks each increment the same counter 1000 times. A mutex
protects the read-modify-write operation. Both completion messages should
eventually show a shared value of 2000 (the first may finish slightly earlier
and print a smaller intermediate value).

Build, upload and monitor at 115200. As a controlled experiment, remove only
the take/give operations, observe the race, then restore them.

Review: Why is `volatile` not a mutex? What is priority inheritance? Why should
a mutex be held for the shortest practical time?
