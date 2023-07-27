#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int remainingTime;
    int waitingTime;
    int completionTime;
};
float calculate_avg_wt(struct Process processes[], int n)
{
    int total_wt = 0;
    for (int i = 0; i < n; i++)
    {
        total_wt += processes[i].waitingTime;
    }
    return (float)total_wt / (float)n;
}

float calculate_avg_tt(struct Process processes[], int n)
{
    int total_tt = 0;
    for (int i = 0; i < n; i++)
    {
        total_tt += processes[i].turnaroundTime;
    }
    return (float)total_tt / (float)n;
}
int main()
{
    struct Process processes[20];
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter quantum: ");
    scanf("%d", &quantum);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter the burst time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    int timer = 0;
    int completed_process = 0;
   

    while (completed_process <= n - 1)
    {
        int processExecuted = 0;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= timer)
            {
                if (processes[i].remainingTime <= quantum)
                {
                    
                    completed_process++;
                    processExecuted = 1;
                    timer += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].completionTime = timer;
                    processes[i].turnaroundTime = timer - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    printf("Process %d turnaround time: %d, %d\n",i, processes[i].turnaroundTime,timer);
                }
                else
                {
                    processExecuted = 1;
                    processes[i].remainingTime -= quantum;
                    timer += quantum;
                }

                
            }
        }

        if (!processExecuted)
        {
            timer++;
            continue;
        }
    }

    float avg_wt = calculate_avg_wt(processes, n);
    float avg_tt = calculate_avg_tt(processes, n);
    printf("Average waiting time: %f\n", avg_wt);
    printf("Average turnaround time: %f\n", avg_tt);

    return 0;
}
