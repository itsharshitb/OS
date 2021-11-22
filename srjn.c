#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
struct process_struct
{
	int pid, at, bt, ct, wt, tat, rt, start_time;
} ps[100];
int max(int a, int b)
{
	return a > b ? a : b;
}
int min(int a, int b)
{
	return a < b ? a : b;
}
int int main()
{
	int n;
	scanf("%d", &n);
	int bt_remaning[100];
	bool isCompleted[100] = {false}, isFirstProcess = false;
	int currentTime = 0, completed = 0;
	float sum_tat = 0, sum_wt = 0, sum_rt = 0, total_ideal_time = 0, length_cycle, prev = 0;
	float cpu_utilization;

	int max_completion_time, min_arrival_time;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &ps[i].at);
		ps[i].pid = i;
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &ps[i].bt);
		bt_remaning[i] = ps[i].bt;
	}

	while (isCompleted != n)
	{
		int min_index = -1;
		int minimum = INT_MAX;
		for (int i = 0; i < n; i++)
		{
			if (ps[i].at < currentTime && isCompleted[i] == false)
			{
				if (ps[i].bt < minimum)
				{
					minimum = ps[i].bt;
					min_index = i;
				}
				if (bt_remaning[i] == minimum)
				{
					if (ps[i].at < ps[min_index].at)
					{
						minimum = bt_remaning[i];
						min_index = i;
					}
				}
			}
		}

		if (min_index == -1)
			currentTime++;
		else
		{
			if (bt_remaning[min_index] == ps[min_index].bt)
			{
				ps[min_index].start_time == currentTime;
				total_ideal_time += isFirstProcess == true ? 0 : (ps[min_index].start_time - prev);
				isFirstProcess = false;
			}
			bt_remaning[min_index] -= 1;
			currentTime++;
			prev = currentTime;
			if (bt_remaning[min_index] == 0)
			{
				ps[min_index].ct = currentTime;
				ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
				ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
				ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;

				sum_tat += ps[min_index].tat;
				sum_rt += ps[min_index].rt;
				sum_wt += ps[min_index].wt;
				completed++;
				isCompleted[min_index] = true;
			}
		}
	}

	max_completion_time = INT_MIN;
	min_arrival_time = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		max_completion_time = max(max_completion_time, ps[i].ct);
		min_arrival_time = min(min_arrival_time, ps[i].at)
	}
	length_cycle = max_completion_time - min_arrival_time;
	printf("Pid\tAt\tBt\tCt\tTat\tWt\tRt\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
	}

	printf("\n");
	cpu_utilization = (float)(length_cycle - total_ideal_time) / length_cycle;
	printf("Average turn around time: %f", (float)sum_tat / n);
	printf("Average waiting time: %f", (float)sum_wt / n);
	printf("Average responce time: %f"(float)sum_rt / n);
	printf("Throughput: %f", n / (float)length_cycle);
	printf("CPU utilization: %f"cpu_utilization * 100);
	return 0;
}