#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char id[5], user[20], doc[20];
    int pages, arrival, burst;
    int start, completion, waiting, turnaround;
} Job;

/* Sort jobs by arrival time (FCFS) */
void sortByArrival(Job j[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int k = 0; k < n - i - 1; k++)
            if (j[k].arrival > j[k + 1].arrival) {
                Job t = j[k]; j[k] = j[k + 1]; j[k + 1] = t;
            }
}

void schedule(Job j[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < j[i].arrival) time = j[i].arrival;   /* printer idle */
        j[i].start = time;
        j[i].completion = time + j[i].burst;
        j[i].turnaround = j[i].completion - j[i].arrival;
        j[i].waiting = j[i].turnaround - j[i].burst;
        time = j[i].completion;
    }
}

void printTable(Job j[], int n) {
    float tw = 0, tt = 0;
    printf("\n================ FCFS PRINT SCHEDULE ================\n");
    printf("%-5s %-10s %-12s %-6s %-8s %-6s %-6s %-6s %-6s\n",
           "Job", "User", "Document", "Pages", "Arrival", "Burst", "Start", "End", "Wait");
    for (int i = 0; i < n; i++) {
        printf("%-5s %-10s %-12s %-6d %-8d %-6d %-6d %-6d %-6d\n",
               j[i].id, j[i].user, j[i].doc, j[i].pages, j[i].arrival,
               j[i].burst, j[i].start, j[i].completion, j[i].waiting);
        tw += j[i].waiting;
        tt += j[i].turnaround;
    }
    printf("\nAverage Waiting Time    : %.2f min\n", tw / n);
    printf("Average Turnaround Time : %.2f min\n", tt / n);
}

void printGantt(Job j[], int n) {
    int time = 0;
    printf("\n---------------- GANTT CHART ----------------\n|");
    for (int i = 0; i < n; i++) {
        if (j[i].start > time) printf(" IDLE |");
        printf(" %-4s |", j[i].id);
        time = j[i].completion;
    }
    printf("\n0      ");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (j[i].start > time) printf("%-7d", j[i].start);
        printf("%-7d", j[i].completion);
        time = j[i].completion;
    }
    printf("\n");
}

int main() {
    Job jobs[MAX];
    int n, choice;

    printf("=== Printing Service Scheduler (FCFS) ===\n");
    printf("1. Use sample data\n2. Enter my own jobs\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        Job s[4] = {
            {"J1", "Nithya", "Report.pdf", 20, 0, 5},
            {"J2", "Arun",   "Resume.doc",  2, 1, 2},
            {"J3", "Priya",  "Notes.pdf",  40, 2, 8},
            {"J4", "Kiran",  "Ticket.pdf",  1, 3, 1}
        };
        n = 4;
        for (int i = 0; i < n; i++) jobs[i] = s[i];
    } else {
        printf("Number of print jobs: ");
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            sprintf(jobs[i].id, "J%d", i + 1);
            printf("\nJob %d\nUser name       : ", i + 1);  scanf("%s", jobs[i].user);
            printf("Document name   : ");                   scanf("%s", jobs[i].doc);
            printf("Pages           : ");                   scanf("%d", &jobs[i].pages);
            printf("Arrival time    : ");                   scanf("%d", &jobs[i].arrival);
            printf("Print time (min): ");                   scanf("%d", &jobs[i].burst);
        }
    }

    sortByArrival(jobs, n);
    schedule(jobs, n);
    printTable(jobs, n);
    printGantt(jobs, n);
    return 0;
}
