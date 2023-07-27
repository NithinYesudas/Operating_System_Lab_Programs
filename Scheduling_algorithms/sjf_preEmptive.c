#include <stdio.h>
#include <stdlib.h>

struct Process{
    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int remaining_time;
    int completed_time;
    int turnaround_time;
};
int shortestJob(struct Process process[],int n,int time)
{
    int minRemainingTime = 100;
    int minPid = -1;
    for (int i = 0; i < n;i++){
        if(process[i].arrival_time <= time && process[i].remaining_time>0){
            if(process[i].remaining_time<minRemainingTime){
                minRemainingTime = process[i].remaining_time;
                minPid = process[i].pid;
            }

        }
    }
   
    return minPid;
}



    int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[10];
    for (int i = 0; i < n;i++){
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i;
        processes[i].remaining_time = processes[i].burst_time;
    }

    int completedProcess = 0;
    int time = 0;
    int total_wt = 0, total_tt = 0;
    while(completedProcess<n){
        int processSelected = 0;
        processSelected = shortestJob(processes, n, time);
        
        if(processSelected != -1 && processes[processSelected].remaining_time>0){
            time++;
            processes[processSelected].remaining_time--;
            if(processes[processSelected].remaining_time==0){
                completedProcess++;
                processes[processSelected].completed_time = time;
                processes[processSelected].turnaround_time = time - processes[processSelected].arrival_time;
                processes[processSelected].waiting_time = processes[processSelected].turnaround_time - processes[processSelected].burst_time;
                total_tt += processes[processSelected].turnaround_time;
                total_wt += processes[processSelected].waiting_time;
                printf("waiting time of %d is: %d\n", processSelected+1, processes[processSelected].waiting_time);
            }
           
        }
        else{
            time++;
        }
        
    }
    float avg_wt = (float)total_wt / (float)n;
    float avg_tt = (float)total_tt / (float)n;
    printf("Avg waiting time: %f", avg_wt);
    printf("Avg TurnAround time: %f", avg_tt);
}