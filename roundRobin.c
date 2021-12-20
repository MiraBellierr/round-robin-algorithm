#include<stdio.h>
#include<stdlib.h>

// function to find waiting time for round robin algorithm
void findWaitingTime(int processes[], int n, int bt[], int wt[])
{
    int rem_bt[n], i, j;
    for (i = 0; i < n; i++)
        rem_bt[i] = bt[i];
    int t = 0;
    while (1)
    {
        int done = 1;
        for (i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0;
                if (rem_bt[i] > bt[i])
                {
                    t += bt[i];
                    rem_bt[i] -= bt[i];
                }
                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
}

// function to calculate average waiting and turnaround time
void findavgTime(int processes[], int n, int bt[], int wt[], int quantum)
{
    int wt_total = 0, tat_total = 0;
    printf("\nProcesses    Burst time    Waiting time    Turn around time\n");
    for (int i = 0; i < n; i++)
    {
        printf("\n %d\t\t %d\t\t %d\t\t %d", processes[i], bt[i], wt[i], bt[i] + wt[i]);
        wt_total += wt[i];
        tat_total += bt[i] + wt[i];
    }
    printf("\n\nAverage waiting time = %f", (float)wt_total / (float)n);
    printf("\nAverage turn around time = %f", (float)tat_total / (float)n);
}

int main() {
    FILE *fptr = fopen("joblist.txt", "r");
    char ch;
    int n = 0, quantum;

    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == ' ' || ch == '\n') {
            n++;
        }
    }
    fclose(fptr);

    int processes[n], burst_time[n], waiting_time[n], turn_around_time[n];

    // take burst time from txt file
    FILE *fptr2 = fopen("joblist.txt", "r");
    if (fptr2 == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(fptr2, "%d", &burst_time[i]);
        processes[i] = i + 1;
    }
    fclose(fptr2);

    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    findWaitingTime(processes, n, burst_time, waiting_time);
    findavgTime(processes, n, burst_time, waiting_time, quantum);
    return 0;
}