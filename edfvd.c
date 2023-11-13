#include <limits.h>  //For INT_MAX
#include <stdbool.h> //To use bool in C, this header file is required.
#include <stdio.h>
#include <stdlib.h> //For random number generation
#include <time.h>   //For seeding with currrent time

int checknexttask(float t, int n, float r[], float d[], bool done[]) {
    int mintask = -1;

    bool flagprev = false;

    for (int i = 0; i < n; i++) {
        if (r[i] < t && done[i] == false)
            flagprev = true;
    }

    if (flagprev == false) {
        int rmin = INT_MAX, dmin = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (r[i] <= rmin && done[i] == false) {
                if (r[i] == rmin) {
                    if (d[i] < dmin) {
                        dmin = d[i];
                        mintask = i;
                    }
                } else {
                    rmin = r[i];
                    dmin = d[i];
                    mintask = i;
                }
            }
        }
    }

    else {
        int rmin = INT_MAX, dmin = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (r[i] <= t && d[i] < dmin && done[i] == false) {
                mintask = i;
                dmin = d[i];
            }
        }
    }

    return mintask;
}

int main() {

    int X, n;

    printf("\t\tHello\n\nEnter the System's Criticality Level : ");
    scanf("%d", &X);

    printf("Enter number of Tasks: ");
    scanf("%d", &n);

    float *r, *d, *p, **C;

    r = (float *)malloc(n * sizeof(float));
    d = (float *)malloc(n * sizeof(float));
    p = (float *)malloc(n * sizeof(float));

    C = (float **)malloc(n * sizeof(float *));

    for (int i = 0; i < n; i++)
        C[i] = (float *)malloc(X * sizeof(float));

    float **c;
    int *x;

    x = (int *)malloc(n * sizeof(int));
    c = (float **)malloc(n * sizeof(float *));

    for (int i = 0; i < n; i++)
        c[i] = (float *)malloc(X * sizeof(float));

    int hp = 1; // Hyperperiod
    int nj = 0; // Denotes number of Jobs
    int max = 0;

    for (int i = 0; i < n; i++) {
        printf("\n\tFor Task %d", i + 1);

        printf("\nRelease Time : ");
        scanf("%f", &r[i]);

        printf("Deadline : ");
        scanf("%f", &d[i]);

        p[i] = d[i] - r[i];

        max = (hp > p[i]) ? hp : p[i];

        while (1) {
            if (max % hp == 0 && max % (int)p[i] == 0)
                break;

            max++;
        }

        hp = max;

        do {
            printf("Criticality : ");
            scanf("%d", &x[i]);

            if (x[i] > 2)
                printf("\n!!Criticality Greater than 2 not accepted. Please try again!\n\n");

        } while (x[i] > 2);

        for (int j = 0; j < x[i]; j++) {
            printf("WCET at level %d:", j + 1);
            scanf("%f", &C[i][j]);
        }
    }

    printf("\n\n-----------------Entry Completed---------------\n");
    printf("HyperPeriod : %d\n", hp);

    for (int i = 0; i < n; i++)
        nj += hp / p[i];

    printf("Total Num of Jobs: %d\n", nj);

    r = (float *)realloc(r, nj * sizeof(float));
    d = (float *)realloc(d, nj * sizeof(float));
    p = (float *)realloc(p, nj * sizeof(float));

    int *task = (int *)malloc(nj * sizeof(int));

    C = (float **)realloc(C, nj * sizeof(float *));

    for (int i = 0; i < nj; i++)
        C[i] = (float *)realloc(C[i], X * sizeof(float));

    x = (int *)realloc(x, nj * sizeof(int));

    c = (float **)realloc(c, nj * sizeof(float *));

    for (int i = 0; i < nj; i++)
        c[i] = (float *)realloc(c[i], X * sizeof(float));

    // printf("Reached after redeclaration");
    // fflush(stdout);

    int counter = 0;

    // Populating all the jobs
    for (int i = 0; i < n; i++) {
        /*		printf("Going for i = %d, Counter= %d\n",i,counter);*/
        /*		fflush(stdout);*/

        task[i] = i + 1;
        for (int j = 1; j < hp / p[i]; j++) {
            /*		  printf("Going for j = %d, So Job num = %d\n",j,n+j-1+counter);*/
            /*		fflush(stdout);*/
            r[n + j - 1 + counter] = d[i] + p[i] * (j - 1);
            task[n + j - 1 + counter] = task[i];
            d[n + j - 1 + counter] = d[i] + p[i] * (j);
            p[n + j - 1 + counter] = p[i];
            x[n + j - 1 + counter] = x[i];

            for (int k = 0; k < x[i]; k++)
                C[n + j - 1 + counter][k] = C[i][k];
        }

        counter += (hp / p[i]) - 1; // All the -1's are because of first pre entered job
    }

    for (int i = 0; i < nj; i++)
        printf("Job %d,Task=%d r = %f  d = %f p = %f x = %d\n", i + 1, task[i], r[i], d[i], p[i], x[i]);

    float u11 = 0, u22 = 0, u21 = 0;

    for (int i = 0; i < n; i++) {
        if (x[i] == 1)
            u11 += ((float)C[i][0] / (d[i] - r[i]));

        if (x[i] == 2) {
            u21 += ((float)C[i][0] / (d[i] - r[i]));
            u22 += ((float)C[i][1] / (d[i] - r[i]));
        }
    }

    int work;

    if (u11 + u22 <= 1) {
        work = 1;
        printf("\nThis Falls in case 1, i.e. U1(1) + U2(2) <=1\n");
    } else if (u11 + (u21 / (1 - u22)) <= 1) {
        work = 2;
        printf("\nThis Falls in case 2, i.e. U1(1) + U2(1)/1-U2(2) <=1\n");
    }

    else {
        printf("Doesnt belong to any case! \n");
        printf("\nWith U1(1) = %f, U2(1) = %f, U2(2)=%f\n", u11, u21, u22);
        return 0;
    }

    printf("\nWith U1(1) = %f, U2(1) = %f, U2(2)=%f\n", u11, u21, u22);

    srand(time(0)); // To seed with current time. Keep outside loop where rand nos. are generated.

    int *jobtemp = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        jobtemp[i] = 0; //++ is added before the term everytime

    for (int i = 0; i < nj; i++) {
        printf("\n**For Task %d, Job %d\n", task[i], ++jobtemp[task[i]]);

        //	fflush(stdout);
        for (int j = 0; j < x[i]; j++) {
	
            float use;

            int choice = rand() % 2;

            use = ((float)rand() / (float)(RAND_MAX)) * ((float)C[i][j] - (float).7 * C[i][j]) + (float).7 * C[i][j]; // To gen random nos. between .7 to 1.0
			//final value lies anywhere from .5C[i][j] to 1.5C[i][j]. 
			         
            c[i][j] = use;
            printf("Level  %d's Realised Value: %f\n", j + 1, c[i][j]);
            printf("Level  %d's entered WCET  : %f\n", j + 1, C[i][j]);

        }
    }

    printf("\n");

    int choose;

    int *predict = (int *)malloc(nj * sizeof(int));

    for (int i = 0; i < nj; i++) {
        predict[i] = 0;

        if (x[i] == 2) {

            choose = rand() % 2;

            if (choose == 1) {
                predict[i] = 1;
                printf("**Task %d choosen for Level 2\n", i + 1);
            }
        }
    }

    printf("\n\n---------------------Scheduling Started-------------------\n");

    if (work == 1) // 1st Case
    {
        // Apply EDF to normal unmodified deadlines, if system reaches level 2, discard all level 1 jobs and execute only level 2 jobs.

        // Step 1 : Applying EDF

        bool done[nj]; // notes whether the job of a task is completed or not

        int *job = (int *)malloc(n * sizeof(int)); // To denote which job of a task it is

        for (int i = 0; i < nj; i++) {
            done[i] = false;
            job[i] = 1; // Starts with 1st job of every task
        }

        int min = INT_MAX, mintask, count = 0, level = 1, rmin = INT_MAX, begin = INT_MAX;

        for (int i = 0; i < n; i++) { // No need to check further jobs as next jobs are dependent on 1st one
            if (r[i] < begin)
                begin = r[i];
        }

        float t = 0;

        // t is current system time

        while (t < hp + begin) {

            mintask = checknexttask(t, nj, r, d, done);

            if (mintask == -1) {
                printf("!!Execution of all jobs in this HyperPeriod Finished !! \n");
                exit(0);
            }

            printf("DEBUG: Mintask= %d\n", mintask);
            if (r[mintask] > t)
                t = r[mintask];

            printf("Executing Task %d, Job = %d at t= %f (Arrival = %f)\n", task[mintask], job[task[mintask]], t, r[mintask]);

            if (c[mintask][predict[mintask]] > C[mintask][0] && checknexttask(t + C[mintask][0], nj, r, d, done) == mintask) {

                printf("System's Criticality Level Changed to 2 because of Task =%d,Job %d", task[mintask], job[task[mintask]]);

                t += C[mintask][0];
                printf(" at time t =%f\n", t);

                c[mintask][1] = c[mintask][1] - C[mintask][0];

                level = 2;
            }

            else {

                if (checknexttask(t + c[mintask][0], nj, r, d, done) == mintask) {
                    printf("Finished Executing Task %d, Job  %d at t= %f (Deadline = %f) \n", task[mintask], job[task[mintask]], t + c[mintask][0], r[mintask] + p[mintask]);
                    t += c[mintask][0];
                    job[task[mintask]]++;
                    done[mintask] = true;
                    count++;
                }

                else {
                    int rmin = INT_MAX, dmin = INT_MAX, newtask;

                    for (int i = 0; i < nj; i++) {
                        if (r[i] > t && d[i] < d[mintask] && done[i] == false && d[i] < dmin && r[i] <= rmin) {
                            if (r[i] == rmin) {
                                if (d[i] < dmin) {
                                    dmin = d[i];
                                    newtask = i;
                                }
                            } else {
                                rmin = r[i];
                                dmin = d[i];
                                newtask = i;
                            }
                        }
                    }
                    printf("Preempted In Middle at t = %f \n", r[newtask]);

                    c[mintask][0] = c[mintask][0] - (r[newtask] - t);
                    t = r[newtask];

                    rmin = INT_MAX;
                    dmin = INT_MAX;
                }
            }

            min = INT_MAX;
        }

        if (count == nj) {
            printf("All tasks completed their execution successfully\n");
        }

        else if (level == 2) {
            printf("\n!!Criticality Level 2 Entered, tasks of criticality level 1 dropped\n\n");

            // Step 2: Execute Tasks of Criticality Level 2 in EDF Mode
            while (count != n) {
                for (int i = 0; i < n; i++) {
                    if (d[i] < min && done[i] == false && x[i] == 2) {
                        min = d[i];
                        mintask = i;
                    }
                }

                done[mintask] = true;

                if (r[mintask] > t)
                    t = r[mintask];

                printf("Task %d executed from t = %f (Arrival = %f)\n", mintask + 1, t, r[mintask]);

                printf("Finished  task %d at %f (In Criticality Level 2, Deadline = %f)\n", mintask + 1, t + c[mintask][1], r[mintask] + p[mintask]);
                t += c[mintask][1];

                count++;
                min = INT_MAX;
            }
        }

        else
            printf("Error in program!!");
    }

    else if (work == 2) {
        printf("\t\tCase II \n");

        float lambda = ((float)u21) / (1 - (float)u11);

        printf("Task\tFinal Deadline\n");
        for (int i = 0; i < n; i++) {
            if (x[i] == 2) {
                d[i] = r[i] + p[i] * lambda;
            }
            printf("%d\t%f\n", i + 1, d[i]);
        }

        // Apply EDF to New Deadlines, if system reaches level 2, discard all level 1 jobs amd execute only level 2 jobs with normal unmodified deadlines.

        // Step 1 : Applying EDF to new deadlines

        bool done[n]; // notes whether a task is completed or not

        for (int i = 0; i < n; i++)
            done[i] = false;

        int min = INT_MAX, mintask, count = 0, level = 1;

        float t = 0;

        // t is current system time

        while (count != n && level == 1) {
            for (int i = 0; i < n; i++) {
                if (d[i] < min && done[i] == false) {
                    min = d[i];
                    mintask = i;
                }
            }

            if (r[mintask] > t)
                t = r[mintask];

            if (c[mintask][predict[mintask]] > C[mintask][0]) {
                printf("Executing Task %d at t= %f Arrival=(%f)\n", mintask + 1, t, r[mintask]);

                printf("System's Criticality Level Changed to 2 because of task %d", mintask + 1);

                t += C[mintask][0];
                printf(" at time t =%f\n", t);

                c[mintask][1] = c[mintask][1] - C[mintask][0];

                level = 2;
            }

            else {
                printf("Executing Task %d at t= %f (Arrival = %f)\n", mintask + 1, t, r[mintask]);

                if (checknexttask(t + c[mintask][0], n, r, d, done) == mintask) {
                    printf("Finished Executing Task %d at t= %f (Deadline = %f) \n", mintask + 1, t + c[mintask][0], r[mintask] + p[mintask]);
                    t += c[mintask][0];
                    done[mintask] = true;
                    count++;
                }

                else {
                    int rmin = INT_MAX, dmin = INT_MAX, newtask;

                    for (int i = 0; i < n; i++) {
                        if (r[i] > t && d[i] < d[mintask] && done[i] == false && d[i] < dmin && r[i] <= rmin) {
                            if (r[i] == rmin) {
                                if (d[i] < dmin) {
                                    dmin = d[i];
                                    newtask = i;
                                }
                            } else {
                                rmin = r[i];
                                dmin = d[i];
                                newtask = i;
                            }
                        }
                    }
                    printf("Preempted In Middle at t = %f \n", r[newtask]);

                    c[mintask][0] = c[mintask][0] - (r[newtask] - t);
                    t = r[newtask];

                    rmin = INT_MAX;
                    dmin = INT_MAX;
                }
            }

            min = INT_MAX;
        }

        if (count == n) {
            printf("All tasks completed their execution successfully\n");
        }

        else if (level == 2) {
            printf("\n!!Criticality Level 2 Entered, tasks of criticality level 1 dropped.\nDeadline of all Level 2 Tasks modified back to Original Level \n\n");

            // Step 2: Execute Tasks of Criticality Level 2 in EDF Mode with unmodified deadlines

            printf("RemTask\tFinal Deadline\n");
            for (int i = 0; i < n; i++) {
                if (x[i] == 2 && done[i] == false) {
                    d[i] = r[i] + p[i];

                    printf("%d\t%f\n", i + 1, d[i]);
                }
            }

            while (count != n) {
                for (int i = 0; i < n; i++) {
                    if (d[i] < min && done[i] == false && x[i] == 2) {
                        min = d[i];
                        mintask = i;
                    }
                }

                done[mintask] = true;

                if (r[mintask] > t)
                    t = r[mintask];

                printf("Task %d executed from t = %f (Arrival = %f)\n", mintask + 1, t, r[mintask]);

                printf("Finished  task %d at %f (In Criticality Level 2, Deadline = %f)\n", mintask + 1, t + c[mintask][1], r[mintask] + p[mintask]);
                t += c[mintask][1];

                count++;
                min = INT_MAX;
            }
        }

        else
            printf("Error in program!!");
    }

    return 0;
}
