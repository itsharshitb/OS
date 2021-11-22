#include<bits/stdc++.h>
using namespace std;
struct process_struct
{
	int pid, at, bt, tat, wt, rt, ct, start_time, bt_remaning;
} ps[100];
bool comparatorAT(struct process_struct a, struct process_struct b)
{
	int x = a.at;
	int y = b.at;
	return x < y;
}
bool comparatorPID(struct process_struct a, struct process_struct b)
{
	int x = a.pid;
	int y = b.pid;
	return x < y;
}
int main()
{
	int n, index;
	int cpu_utilization;
	queue<int> q;
	bool visited[100] = {false}, isFirstProgram = true;
	int currentTime = 0, maxCompletionTime;
	bool completed = 0, tq, total_ideal_time = 0, lengthOfCycle;
	cout << "Enter total number of processes: ";
	cin >> n;
	float sum_tat = 0, sum_wt = 0, sum_rt = 0;
	cout << fixed << setprecision(2);
	for (int i = 0; i < n; i++)
	{
		cout << "\nEnter process " << i << " arrival time ";
		cin >> ps[i].at;
		ps[i].pid = i;
	}
	for (int i = 0; i < n; i++)
	{
		cout << "\nEnter burst time for process " << i;
		cin >> ps[i].bs;
		ps[i].bt_remaning = ps[i].bt;
	}
	cout << "Enter time quanta: ";
	cin >> tq;
	sort(ps, ps + n, comparatorAT);
	q.push(0);
	visited[0] = true;

	while (completed != n)
	{
		int index = q.front();
		q.pop();

		if (ps[index].bt_remaning == ps[index].bt)
		{
			ps[index].start_time = max(currentTime, ps[index].at);
			total_ideal_time = isFirstProgram == 0 ? 0 : max(currentTime, ps[index].at);
			isFirstProgram = false;
			currentTime = ps[index].at;
		}
		if (ps[index].bt_remaning - tq > 0)
		{
			ps[index].bt_remaning -= tq;
			currentTime += tq;
		}
		else {
			currentTime += ps[index].bt_remaning;
			ps[bt_remaning] = 0;
			completed++;

			ps[index].ct = currentTime;
			ps[index].tat = ps[index].ct - ps[index].at;
			ps[index].wt = ps[index].tat - ps[index].bt;
			ps[index].rt = ps[index].start_time - ps[index].at;

			sum_rt += ps[index].rt;
			sum_wt += ps[index].wt;
			sum_tat += ps[index].tat;
		}

		for (int i = 1; i < n; i++)
		{
			if (ps[i].bt_remaning > 0 and ps[i].at <= currentTime and visited[i] == false)
			{
				q.push(i);
				visited[i] = true;
			}
		}
		if (ps[index].bt_remaning > 0)
			q.push(index);

		if (q.empty())
		{
			for (int i = 1; i < n; i++)
			{
				if (ps[i].bt_remaning > 0)
				{
					q.push(i);
					visited[i] = true;
					break;
				}
			}
		}
	}
	maxCompletionTime = INT_MIN;
	for (int i = 0; i < n; i++)
		maxCompletionTime = max(maxCompletionTime, ps[i].ct);

	lengthOfCycle = maxCompletionTime - ps[0].at;
	cpu_utilization = (float)(lengthOfCycle - total_ideal_time) / lengthOfCycle;
	sort(ps, ps + n, comparatorPID);

	cout << "PID\tAt\tBt\tSt\tCt\ttat\twt\trt\n";
	for (int i = 0; i < n; i++)
	{
		cout << i << ps[i].at << ps[i].bt << ps[i].st << ps[i].start_time << ps[i].ct << ps[i].tat << ps[i].wt << ps[i].rt << endl;
	}
	cout << "Average turn around time: " << (float)sum_wt / n << endl;
	cout << "Average waiting time " << (float)sum_wt / n << endl;
	cout << "Average responce time " << (float)sum_rt / n << endl;
	cout << "Throughput " << n / (float)lengthOfCycle << endl;
	cout << "CPU utilization% " << cpu_utilization * 100 << endl;
}