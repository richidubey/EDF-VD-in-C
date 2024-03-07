# EDF-VD-in-C

EDF VD Scheduling Algorithm for mixed criticality systems as described in the paper "Mixed-Criticality Scheduling of Sporadic Task Systems" by Sanjoy Baruah, Vincenzo Bonifaci, Gianlorenzo d’Angelo, Alberto Marchetti-Spaccamela, Suzanne Ster, Leen Stougi [[Link to the paper]](https://inria.hal.science/hal-00643987).

## Set up

To download the repository and compile the program, run the following commands:    

```bash
git clone https://github.com/richidubey/EDF-VD-in-C.git # replace [richidubey] with your github username if you fork first.
cd EDF-VD-in-C
make
``` 


## Running

Run the following command to start the program. You can pass the input file or enter the system parameters manually.    

```bash
./edfvd < sampleinput.txt
```

## Sample run
```
Enter the System's Criticality Level : 2
Enter number of Tasks: 2

For Task 1
Release Time : 5
Deadline : 8
Criticality : 1 
WCET at level 1: 1

For Task 2
Release Time : 5
Deadline : 11
Criticality : 2
WCET at level 1: 1
WCET at level 2: 2

-----------------Entry Completed---------------
HyperPeriod : 6
Total Num of Jobs: 3
Job 1,Task=1 r = 5.000000  d = 8.000000 p = 3.000000 x = 1
Job 2,Task=2 r = 5.000000  d = 11.000000 p = 6.000000 x = 2
Job 3,Task=1 r = 8.000000  d = 11.000000 p = 3.000000 x = 1

This Falls in case 1, i.e. U1(1) + U2(2) <=1

With U1(1) = 0.333333, U2(1) = 0.166667, U2(2)=0.333333

**For Task 1, Job 1
Level  1's Realised Value: 0.862248
Level  1's entered WCET  : 1.000000

**For Task 2, Job 1
Level  1's Realised Value: 0.941447
Level  1's entered WCET  : 1.000000
Level  2's Realised Value: 1.829546
Level  2's entered WCET  : 2.000000

**For Task 1, Job 2
Level  1's Realised Value: 0.826164
Level  1's entered WCET  : 1.000000



---------------------Scheduling Started-------------------
Executing Task 1, Job = 1 at t= 5.000000 (Arrival = 5.000000)
Finished Executing Task 1, Job  1 at t= 5.862248 (Deadline = 8.000000) 
Executing Task 2, Job = 1 at t= 5.862248 (Arrival = 5.000000)
Finished Executing Task 2, Job  1 at t= 6.803695 (Deadline = 11.000000) 
Executing Task 1, Job = 2 at t= 8.000000 (Arrival = 8.000000)
Finished Executing Task 1, Job  2 at t= 8.826164 (Deadline = 11.000000) 
!!Execution of all jobs in this HyperPeriod Finished !! 
```


## Contributing

Contributions are actively encouraged. Please suggest changes/improvements by submitting issues. If you find a bug, please [email](mailto:richidubey@gmail.com) me, submit a pull request (I'll buy you a coffee as a thank you); or submit an issue.

