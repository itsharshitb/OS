#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
struct process_struct
{
	int arrival_time, burst_time, completion_time, waiting_time, turn_around_time, responce_time, start_time, pid;
} ps[100];
int findmax(int a, int b)
{
	return a > b ? a : b;
}
int findmin(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n;
	bool isCompleted[100] = {false}, isFirstProcess = true;
	int currentTime = 0, completed = 0;
	int sum_tat = 0, sum_wt = 0, sum_rt = 0, total_ideal_time = 0, prev = 0, length_cycle;
	float cpu_utilization;
	int max_completion_time, min_arrival_time;
	printf("Enter total number of processes\n");
	scanf("%d", &n);
	printf("Enter all Arrival times\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &ps[i].arrival_time);
		ps[i].pid = i;
	}
	printf("Enter all burst times\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &ps[i].burst_time);
	}
	while (completed != n)
	{
		//find process with minimum burst time in ready queue at current time
		int min_index = -1, minimum = INT_MAX;
		for (int i = 0; i < n; i++)
		{
			if (ps[i].arrival_time <= currentTime && !isCompleted[i])
			{
				if (ps[i].burst_time < minimum)
				{
					minimum = ps[i].burst_time;
					min_index = i;
				}
				if (ps[i].burst_time == minimum)
				{
					if (ps[i].arrival_time < ps[min_index].arrival_time)
					{
						minimum = ps[i].burst_time;
						min_index = i;
					}
				}
			}
		}

		if (min_index == -1)
		{
			currentTime++;
		}
		else
		{
			ps[min_index].start_time = currentTime;
			ps[min_index].completion_time = ps[min_index].start_time + ps[min_index].burst_time;
			ps[min_index].turn_around_time = ps[min_index].completion_time - ps[min_index].arrival_time;
			ps[min_index].waiting_time = ps[min_index].turn_around_time - ps[min_index].burst_time;
			ps[min_index].responce_time = ps[min_index].waiting_time;

			sum_tat += ps[min_index].turn_around_time;
			sum_rt += ps[min_index].responce_time;
			sum_wt += ps[min_index].waiting_time;
			total_ideal_time += (isFirstProcess == true) ? 0 : (ps[min_index].start_time - prev);

			completed++;
			isCompleted[min_index] = true;
			currentTime = ps[min_index].completion_time;
			prev = currentTime;
			isFirstProcess = false;
		}
	}

	max_completion_time = INT_MIN;
	min_arrival_time = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		max_completion_time = findmax(max_completion_time, ps[i].completion_time);
		min_arrival_time = findmin(min_arrival_time, ps[i].arrival_time);
	}
	length_cycle = max_completion_time - min_arrival_time;

	for (int i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].arrival_time, ps[i].burst_time, ps[i].completion_time, ps[i].turn_around_time, ps[i].waiting_time, ps[i].responce_time);
	}
	printf("\n");
	cpu_utilization = (float)(length_cycle - total_ideal_time) / length_cycle;
	printf("\nAverage turn around time: %f", (float)sum_tat / n);
	printf("\nAverage waiting time: %f", (float)sum_wt / n);
	printf("\nResponse time: %f", (float)sum_rt / n);
	printf("\nThroughput: %f", n / (float)length_cycle);
	printf("\nCPU utilization(%): %f", cpu_utilization * 100);
	return 0;
}