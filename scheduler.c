#include "scheduler.h"

//  FCFS Scheduling 
Metrics fcfs_metrics(Process proc[], int n) {
    int time = 0;
    float total_wait = 0, total_turn = 0, total_resp = 0;

    for (int i = 0; i < n; i++) {
        if (time < proc[i].arrivalTime)
            time = proc[i].arrivalTime;

        proc[i].startTime = time;
        proc[i].completionTime = time + proc[i].burstTime;
        int turnaround = proc[i].completionTime - proc[i].arrivalTime;
        int waiting = proc[i].startTime - proc[i].arrivalTime;
        int response = waiting;

        total_turn += turnaround;
        total_wait += waiting;
        total_resp += response;

        time = proc[i].completionTime;
    }

    Metrics m = {
        .avgTurnaround = total_turn / n,
        .avgWaiting = total_wait / n,
        .avgResponse = total_resp / n
    };
    return m;
}

//  SJF Scheduling (Non-preemptive) 
Metrics sjf_metrics(Process proc[], int n) {
    int completed = 0, time = 0;
    float total_wait = 0, total_turn = 0, total_resp = 0;
    int done[100] = {0};

    while (completed < n) {
        int idx = -1, min_burst = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && proc[i].arrivalTime <= time && proc[i].burstTime < min_burst) {
                min_burst = proc[i].burstTime;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        proc[idx].startTime = time;
        proc[idx].completionTime = time + proc[idx].burstTime;

        int turnaround = proc[idx].completionTime - proc[idx].arrivalTime;
        int waiting = proc[idx].startTime - proc[idx].arrivalTime;
        int response = waiting;

        total_turn += turnaround;
        total_wait += waiting;
        total_resp += response;

        time = proc[idx].completionTime;
        done[idx] = 1;
        completed++;
    }

    Metrics m = {
        .avgTurnaround = total_turn / n,
        .avgWaiting = total_wait / n,
        .avgResponse = total_resp / n
    };
    return m;
}

//  Round Robin Scheduling 
Metrics rr_metrics(Process proc[], int n, int timeQuantum) {
    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};
    float total_wait = 0, total_turn = 0, total_resp = 0;

    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].startTime = -1;
    }

    
    int first_proc = -1;
    for (int i = 0; i < n; i++) {
        if (first_proc == -1 || proc[i].arrivalTime < proc[first_proc].arrivalTime) {
            first_proc = i;
        }
    }

    queue[rear++] = first_proc;
    visited[first_proc] = 1;
    time = proc[first_proc].arrivalTime;

    while (completed < n) {
        if (front == rear) {
            
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    time = proc[i].arrivalTime;
                    break;
                }
            }
        }

        int idx = queue[front++];

        if (proc[idx].startTime == -1) {
            proc[idx].startTime = time;
            total_resp += time - proc[idx].arrivalTime;
        }

        int exec_time = (proc[idx].remainingTime > timeQuantum) ? timeQuantum : proc[idx].remainingTime;
        proc[idx].remainingTime -= exec_time;
        time += exec_time;

        
        for (int i = 0; i < n; i++) {
            if (!visited[i] && proc[i].arrivalTime <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (proc[idx].remainingTime > 0) {
            queue[rear++] = idx;
        } else {
            proc[idx].completionTime = time;
            int turnaround = proc[idx].completionTime - proc[idx].arrivalTime;
            int waiting = turnaround - proc[idx].burstTime;

            total_turn += turnaround;
            total_wait += waiting;
            completed++;
        }
    }

    Metrics m = {
        .avgTurnaround = total_turn / n,
        .avgWaiting = total_wait / n,
        .avgResponse = total_resp / n
    };
    return m;
}
