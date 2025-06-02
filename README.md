This project implements three fundamental CPU scheduling algorithms in C as part of an Operating Systems course project.

FCFS (First Come First Serve) and  SJF(Shortest Job First - Non-Preemptive) and   Round Robin (RR)  are that three CPU scheduling algorithms. 

 Each algorithm calculates  Time Average Turnaround  and Time Average Waiting  and  Time Average Response .

 you can check the time with expected time . they should be same . 

 these are outputs  of three algoritms for first test case :

 ==== Test Case 1 ====
FCFS: Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
SJF:  Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
RR (Quantum = 4): Calculated: Turnaround: 19.33, Waiting: 11.67, Response: 3.00
         Expected:   Turnaround: 19.33, Waiting: 11.67, Response: 3.00
>>> Test Case 1 PASSED.
