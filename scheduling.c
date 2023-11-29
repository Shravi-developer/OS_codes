#include <stdio.h>

void fcfs(int pid[], int at[], int bt[], int pr[], int n)
{

    int ft[15];
    int tt[15];
    int wt[15];

    for (int j = 0; j < n; j++)
    {
        ft[0] = bt[0];
        tt[0] = ft[0] + at[0];
        wt[0] = tt[0] - bt[0];
        for (int i = 1; i < n; i++)
        {
            if (at[i] > at[i + 1])
            {

                int temp;

                temp = pr[i];
                pr[i] = pr[i + 1];
                pr[i + 1] = temp;

                temp = at[i];
                at[i] = at[i + 1];
                at[i + 1] = temp;

                temp = bt[i];
                bt[i] = bt[i + 1];
                bt[i + 1] = temp;

                temp = pid[i];
                pid[i] = pid[i + 1];
                pid[i + 1] = temp;
            }
            else
                pr[i] = pr[i];
        }

        ft[j] = bt[j] + ft[j - 1];
        tt[j] = ft[j] - at[j];
        wt[j] = ft[j] - at[j] - bt[j];
    }

    printf("Process ID     Arrival Time     Burst Time     Priority     Finish Time     TurnAround Time     Waiting Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t", pid[i]);
        printf("%d\t\t", at[i]);
        printf("%d\t\t", bt[i]);
        printf("%d\t\t", pr[i]);

        // calculating and printing finish time of each process
        printf("%d\t\t", ft[i]);

        // calculating and printing turnaround time of each process
        printf("%d\t\t", tt[i]);

        // calculating and printing waiting time of each process
        printf("%d\t\t", wt[i]);

        printf("\n");
    }

    printf("\nGantt Chart:\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("|\tP%d\t|", pid[i]);
    }

    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++)
    {
        printf("\t\t%d", ft[i]);
    }

    printf("\nAverage Waiting Time:");
    float tot_wt = 0;
    for (int i = 0; i < n; i++)
    {
        tot_wt = tot_wt + wt[i];
    }
    printf("%f\n", tot_wt / n);

    printf("\nAverage TurnAround Time:");
    float tot_tt = 0;
    for (int i = 0; i < n; i++)
    {
        tot_tt = tot_tt + tt[i];
    }
    printf("%f\n", tot_tt / n);
}

void priority_preemptive(int pid[], int at[], int bt[], int pr[], int n)
{

    int ft[15];
    int tt[15];
    int wt[15];
    int gid[100];
    int gt[100];
    int rt[15];
    int min, time = 0, index, ex = 0;

    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                int temp;

                temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    int complete = 0, t = 0, minm = 9999;
    int prt = -1;
    int k = 0;

    while (complete < n)
    {
        prt = -1;
        minm = 9999;

        // Find the process with the highest priority among the arrived processes
        for (int i = 0; i < n; i++)
        {
            if ((at[i] <= t) && (pr[i] < minm) && rt[i] > 0)
            {
                minm = pr[i];
                prt = i;
            }
        }

        if (prt == -1)
        {
            t++;
            continue;
        }

        // Decrement the remaining time
        t++;
        rt[prt]--;

        if (rt[prt] == 0)
        {
            ft[prt] = t;

            // Calculate waiting time
            tt[prt] = ft[prt] - at[prt];
            wt[prt] = tt[prt] - bt[prt];

            complete++;
        }

        gid[k] = pid[prt];
        gt[k] = t;
        k++;
    }

printf("Process ID\tArrival Time\tBurst Time\tPriority\tFinish Time\tTurnaround Time\tWaiting Time\n");

for (int i = 0; i < n; i++)
{
    printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], pr[i], ft[i], tt[i], wt[i]);
}

// Display the Gantt chart

printf("\nGantt Chart:\n");
printf("| ");
for (int i = 0; i < k; i++)
{
    printf("P%d | ", gid[i]);
}

// printf("\nGantt Chart:\n\n");
// for (int i = 0; i < n; i++)
// {
//     printf("|\tP%d\t|", pid[i]);
// }

printf("\nGantt Chart:\n");
int current_process = gid[0];
int current_time = gt[0];
printf("|0 ");
for (int i = 0; i < k; i++)
{
    if (current_process != gid[i])
    {
        printf("| %d ", current_time);
        current_process = gid[i];
    }
    printf("P%d ", current_process);
    current_time = gt[i];
}
printf("| %d |\n", current_time);


printf("\n");

printf("\nAverage Waiting Time: ");
float tot_wt = 0;
for (int i = 0; i < n; i++)
{
    tot_wt = tot_wt + wt[i];
}
printf("%.2f\n", tot_wt / n);

printf("Average Turnaround Time: ");
float tot_tt = 0;
for (int i = 0; i < n; i++)
{
    tot_tt = tot_tt + tt[i];
}
printf("%.2f\n", tot_tt / n);

}

void priority_nonpreemptive(int pid[], int at[], int bt[], int pr[], int n)
{
    int ft[15];
    int tt[15];
    int wt[15];

    for (int j = 0; j < n; j++)
    {
        ft[0] = bt[0];
        tt[0] = ft[0] + at[0];
        wt[0] = tt[0] - bt[0];
        for (int i = 1; i < n; i++)
        {
            if (pr[i] > pr[i + 1])
            {

                int temp;

                temp = pr[i];
                pr[i] = pr[i + 1];
                pr[i + 1] = temp;

                temp = at[i];
                at[i] = at[i + 1];
                at[i + 1] = temp;

                temp = bt[i];
                bt[i] = bt[i + 1];
                bt[i + 1] = temp;

                temp = pid[i];
                pid[i] = pid[i + 1];
                pid[i + 1] = temp;
            }
            else
                pr[i] = pr[i];
        }

        ft[j] = bt[j] + ft[j - 1];
        tt[j] = ft[j] - at[j];
        wt[j] = ft[j] - at[j] - bt[j];
    }

    printf("Process ID     Arrival Time     Burst Time     Priority     Finish Time     TurnAround Time     Waiting Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t", pid[i]);
        printf("%d\t\t", at[i]);
        printf("%d\t\t", bt[i]);
        printf("%d\t\t", pr[i]);

        // calculating and printing finish time of each process
        printf("%d\t\t", ft[i]);

        // calculating and printing turnaround time of each process
        printf("%d\t\t", tt[i]);

        // calculating and printing waiting time of each process
        printf("%d\t\t", wt[i]);

        printf("\n");
    }

    printf("\nGantt Chart:\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("|\tP%d\t|", pid[i]);
    }

    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++)
    {
        printf("\t\t%d", ft[i]);
    }

    printf("\nAverage Waiting Time:");
    float tot_wt = 0;
    for (int i = 0; i < n; i++)
    {
        tot_wt = tot_wt + wt[i];
    }
    printf("%f\n", tot_wt / n);

    printf("\nAverage TurnAround Time:");
    float tot_tt = 0;
    for (int i = 0; i < n; i++)
    {
        tot_tt = tot_tt + tt[i];
    }
    printf("%f\n", tot_tt / n);
}

void sjf_preemptive(int pid[], int at[], int bt[], int pr[], int n)
{

    int ft[15];
    int tt[15];
    int wt[15];
    int gid[100];
    int gt[100];
    int rt[15];

     for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }
    int complete = 0, t = 0, minm = 9999;
    int shortest = -1;

    int k = 0;

    while (complete < n) {
        shortest=-1;
        minm = 9999;
        while(shortest==-1){
        for (int j = 0; j < n; j++) {
             if ((at[j] <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
             }
          }
          if (shortest==-1) {
             t++;
             continue;
          }
          else break;
        }

        rt[shortest]--;

        t++;

        if (rt[shortest] == 0) {
                //seq[complete] = shortest;
                //t++;
                ft[shortest] = t;

                // Calculate waiting time
                tt[shortest]=ft[shortest]-at[shortest];
                wt[shortest]=tt[shortest]-bt[shortest];

                //printf("p[shortest].ft = %d p[shortest].tat=%d p[shortest].wt = %d\n", p[shortest].ft, p[shortest].tat, p[shortest].wt);
                complete++;
             }

             gid[k] = pid[shortest];
             gt[k] = t;
             k++;

       }

printf("Process ID\tArrival Time\tBurst Time\tPriority\tFinish Time\tTurnaround Time\tWaiting Time\n");

for (int i = 0; i < n; i++)
{
    printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], pr[i], ft[i], tt[i], wt[i]);
}

// Display the Gantt chart

printf("\nGantt Chart:\n");
printf("| ");
for (int i = 0; i < k; i++)
{
    printf("P%d | ", gid[i]);
}

// printf("\nGantt Chart:\n\n");
// for (int i = 0; i < n; i++)
// {
//     printf("|\tP%d\t|", pid[i]);
// }

printf("\nGantt Chart:\n");
int current_process = gid[0];
int current_time = gt[0];
printf("|0 ");
for (int i = 0; i < k; i++)
{
    if (current_process != gid[i])
    {
        printf("| %d ", current_time);
        current_process = gid[i];
    }
    printf("P%d ", current_process);
    current_time = gt[i];
}
printf("| %d |\n", current_time);


printf("\n");

printf("\nAverage Waiting Time: ");
float tot_wt = 0;
for (int i = 0; i < n; i++)
{
    tot_wt = tot_wt + wt[i];
}
printf("%.2f\n", tot_wt / n);

printf("Average Turnaround Time: ");
float tot_tt = 0;
for (int i = 0; i < n; i++)
{
    tot_tt = tot_tt + tt[i];
}
printf("%.2f\n", tot_tt / n);

}


void sjf_nonpreemptive(int pid[], int at[], int bt[], int pr[], int n)
{
    int ft[15];
    int tt[15];
    int wt[15];

    for (int j = 0; j < n; j++)
    {
        ft[0] = bt[0];
        tt[0] = ft[0] + at[0];
        wt[0] = tt[0] - bt[0];
        for (int i = 1; i < n-1; i++)
        {
            if (bt[i] > bt[i + 1])
            {

                int temp;

                temp = pr[i];
                pr[i] = pr[i + 1];
                pr[i + 1] = temp;

                temp = at[i];
                at[i] = at[i + 1];
                at[i + 1] = temp;

                temp = bt[i];
                bt[i] = bt[i + 1];
                bt[i + 1] = temp;

                temp = pid[i];
                pid[i] = pid[i + 1];
                pid[i + 1] = temp;
            }
            else
                pr[i] = pr[i];
        }

        ft[j] = bt[j] + ft[j - 1];
        tt[j] = ft[j] - at[j];
        wt[j] = ft[j] - at[j] - bt[j];
    }

    printf("Process ID     Arrival Time     Burst Time     Priority     Finish Time     TurnAround Time     Waiting Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t", pid[i]);
        printf("%d\t\t", at[i]);
        printf("%d\t\t", bt[i]);
        printf("%d\t\t", pr[i]);

        // calculating and printing finish time of each process
        printf("%d\t\t", ft[i]);

        // calculating and printing turnaround time of each process
        printf("%d\t\t", tt[i]);

        // calculating and printing waiting time of each process
        printf("%d\t\t", wt[i]);

        printf("\n");
    }

    printf("\nGantt Chart:\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("|\tP%d\t|", pid[i]);
    }

    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++)
    {
        printf("\t\t%d", ft[i]);
    }

    printf("\nAverage Waiting Time:");
    float tot_wt = 0;
    for (int i = 0; i < n; i++)
    {
        tot_wt = tot_wt + wt[i];
    }
    printf("%f\n", tot_wt / n);

    printf("\nAverage TurnAround Time:");
    float tot_tt = 0;
    for (int i = 0; i < n; i++)
    {
        tot_tt = tot_tt + tt[i];
    }
    printf("%f\n", tot_tt / n);
}

void round_robin(int pid[], int at[], int bt[], int pr[], int n)
{
    int tq, p_counter=0;
    int queue[n],timer = 0, maxProccessIndex = 0;
    float avgWait = 0, avgTT = 0;

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int ft[15];
    int tt[15];
    int wt[15];

    int turn[n], temp_burst[n], complete[n];

    for (int i = 0; i < n; i++) {
        complete[i] = 0;
    }

    for (int i = 0; i < n; i++) { // Initializing the queue and complete array
        complete[i] = 0;
        queue[i] = 0;
    }

    while (timer < at[0]) { // Incrementing Timer until the first process arrives
        timer++;
    }
    queue[0] = 1;

    printf("\nGantt Chart:\n");
    while (1) {
        int flag = 1;
        for (int i = 0; i < n; i++) {
            if (temp_burst[i] != 0) {
                flag = 0;
                break;
            }
        }
        if (flag)
            break;

        for (int i = 0; (i < n) && (queue[i] != 0); i++) {
            int ctr = 0;
            while ((ctr < tq) && (temp_burst[queue[0] - 1] > 0)) {
                temp_burst[queue[0] - 1] -= 1;
                timer += 1;
                printf("|%d P%d ", p_counter, queue[0]);
				p_counter++;
                ctr++;

                // Checking and Updating the ready queue until all the processes arrive
                if(timer <= at[n-1]){
	int newArrival = 0;
    int zeroIndex;
	for(int j = (maxProccessIndex+1); j < n; j++){
			if(at[j] <= timer){
			if(maxProccessIndex < j){
				maxProccessIndex = j;
				newArrival = 1;
			}
		}
	}
	//adds the incoming process to the ready queue
	//(if any arrives)
	if(newArrival)
		for(int i = 0; i < n; i++){
		if(queue[i] == 0){
			zeroIndex = i;
			break;
		}
	}
	queue[zeroIndex] = maxProccessIndex + 1;
	}
            }
            // If a process is completed, then store its exit time
            // and mark it as completed
            if ((temp_burst[queue[0] - 1] == 0) && (complete[queue[0] - 1] == 0)) {
                // turn array currently stores the completion time
                turn[queue[0] - 1] = timer;
                complete[queue[0] - 1] = 1;
            }

            // Checks whether or not CPU is idle
            int idle = 1;
            if (queue[n - 1] == 0) {
                for (int i = 0; i < n && queue[i] != 0; i++) {
                    if (complete[queue[i] - 1] == 0) {
                        idle = 0;
                    }
                }
            } else
                idle = 0;

            if (idle) {
                timer++;
                if(timer <= at[n-1]){
	int newArrival = 0;
    int zeroIndex;
	for(int j = (maxProccessIndex+1); j < n; j++){
			if(at[j] <= timer){
			if(maxProccessIndex < j){
				maxProccessIndex = j;
				newArrival = 1;
			}
		}
	}
	//adds the incoming process to the ready queue
	//(if any arrives)
	if(newArrival)
		for(int i = 0; i < n; i++){
		if(queue[i] == 0){
			zeroIndex = i;
			break;
		}
	}
	queue[zeroIndex] = maxProccessIndex + 1;
	}
            }

            // Maintaining the entries of processes
            // after each preemption in the ready Queue
            for(int i = 0; (i < n-1) && (queue[i+1] != 0) ; i++){
		int temp = queue[i];
		queue[i] = queue[i+1];
		queue[i+1] = temp;
	}
        }
    }

    printf("|%d", p_counter);

	printf("\n");
	// printf("\n%d\n", p_counter);


    for (int i = 0; i < n; i++) {
        turn[i] = turn[i] - at[i];
        wt[i] = turn[i] - bt[i];
    }

    printf("\nProgram No.\tArrival Time\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], turn[i]);
        avgWait += wt[i];
        avgTT += turn[i];
    }

    printf("Average wait time: %.2f\n", avgWait / n);
    printf("Average turnaround time: %.2f\n", avgTT / n);

}

int main()
{
    int pid[15];
    int at[15];
    int bt[15];
    int pr[15];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter process id of all the processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pid[i]);
    }

    printf("Enter arrival time of all the processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &at[i]);
    }

    printf("Enter burst time of all the processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    printf("Enter priority of all the processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pr[i]);
    }


    int choice;
    do
    {
        printf("Enter choice :\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("fcfs\n");
            fcfs(pid, at, bt, pr, n);
            break;
        case 2:
            printf("priority_preemptive\n");
            priority_preemptive(pid, at, bt, pr, n);
            break;

        case 3:
            printf("priority_nonpreemptive\n");
            priority_nonpreemptive(pid, at, bt, pr, n);
            break;

        case 4:
            printf("sjf_preemptive\n");
            sjf_preemptive(pid, at, bt, pr, n);
            break;

        case 5:
            printf("sjf_nonpreemptive\n");
            sjf_nonpreemptive(pid, at, bt, pr, n);
            break;  

        case 6:
            printf("Round_Robin\n");
            round_robin(pid, at, bt, pr, n);
            break;

        default:
            printf("Invaid choice\n");
        }

    } while (choice != 7);

    return 0;
}