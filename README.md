# Printing Service Scheduler (FCFS) - C

A C console program that schedules print jobs using First Come First Served (FCFS).

- Input: user, document, pages, arrival time, print time
- Output: Start, Completion, Waiting, Turnaround time, Gantt chart, averages

Turnaround = Completion - Arrival | Waiting = Turnaround - Burst

## Run
```
gcc printing_scheduler.c -o printing_scheduler
./printing_scheduler
```
(Windows: `printing_scheduler.exe`)
