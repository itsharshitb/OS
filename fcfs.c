// #include<bits/stdc++.h>
#include <stdio.h>
#include<stdlib.h>
#include <conio.h>
struct process_struct
{
	int pid, at, bt, ct, wt, tat, rt, start_time;
} ps[100];
int comparatorAT(const void *a, const void *b)
{
	int x = ((struct process_struct *)a)->at;
	int y = ((struct process_struct *)b)->at;
	if (x < y)	return -1;
	else return 1;
}
int max(int a, int b)
{
	return a > b ? a : b;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n;
	printf("Enter total number of process: \n");
	scanf("%d", &n);
	float sum_tat = 0, sum_wt = 0, sum_rt = 0;
	int length_cycle, total_idle_time = 0;
	float cpu_utilization;

	for (int i = 0; i < n; i++)
	{
		printf("Enter arrival time for process %d", i);
		scanf("%d", &ps[i].at);
		ps[i].pid = i;
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		printf("Enter burst time of process %d", i);
		scanf("%d", &ps[i].bt);
		printf("\n");
	}
	qsort((void *)ps, n, sizeof(struct process_struct), comparatorAT);
	for (int i = 0; i < n; i++)
	{
		ps[i].start_time = (i == 0) ? ps[i].at : max(ps[i].at, ps[i - 1].ct);
		ps[i].ct = ps[i].start_time + ps[i].bt;
		ps[i].tat = ps[i].ct - ps[i].at;
		ps[i].wt = ps[i].tat - ps[i].bt;
		ps[i].rt = ps[i].wt;

		sum_tat += ps[i].tat;
		sum_wt += ps[i].wt;
		sum_rt += ps[i].rt;

		total_idle_time += (i == 0) ? 0 : (ps[i].start_time - ps[i - 1].ct);
	}

	length_cycle = ps[n - 1].ct - ps[0].start_time;

	for (int i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
	}
	printf("\n");
	cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;
	printf("avg tat: %f\n", sum_tat / n);
	printf("avg waiting: %f\n", sum_wt / n);
	printf("avg resonce: %f\n", sum_rt / n);
	printf ("throughput: %f\n", n / (float)length_cycle);
	printf("utilization(percentage) = %f", cpu_utilization * 100);
	printf("\n");
	return 0;
}