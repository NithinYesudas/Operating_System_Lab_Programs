#include <stdio.h>
#include <stdlib.h>

struct Process{
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int completionTime;
};

int main(){
    struct Process processes[20];
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i =0; i < n;i++){
        printf("Enter arrival time of process %d: ", i+1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }
   struct Process temp;
    for (int i = 0; i < n;i++){
        for (int j = i + 1; j < n;j++){
            if(processes[i].arrivalTime>processes[j].arrivalTime){
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    int total_wt = 0, total_tt = 0;
    int timer = processes[0].arrivalTime;
    
    for (int i = 0; i < n;i++){
        if(processes[i].arrivalTime>timer){
            timer = processes[i].arrivalTime;
        }else{
            timer += processes[i].burstTime;
        }
        processes[i].completionTime = timer;
        processes[i].turnaroundTime = timer - processes[i].arrivalTime;
        processes[i].waitingTime =  processes[i].turnaroundTime - processes[i].burstTime;
        total_tt += processes[i].turnaroundTime;
        total_wt += processes[i].waitingTime;
        }
        float avg_wt = (float)total_wt / (float)n;
        float avg_tt = (float)total_tt / (float)n;
        printf("Average waiting time: %f", avg_wt);
        printf("Average turnaround time: %f", avg_tt);
        return 0;
}

