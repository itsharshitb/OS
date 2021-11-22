#include<stdio.h>
#include<string.h>
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n, count = 0;
	scanf("%d", &n);	//no of page
	int nof, arr[n];
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);	//page no
	scanf("%d", &nof);	//no of frames at once
	int frame[nof];
	for (int i = 0; i < nof; i++)
		frame[i] = -1;
	int ind = 0;
	for (int i = 0; i < n; i++)
	{
		int available = 0;
		for (int j = 0; j < nof; j++)
		{
			if (frame[j] == arr[i])
				available = 1;
		}
		if (available == 0)
		{
			frame[ind] = arr[i];
			ind = (ind + 1) % nof;
			count++;
			for (int k = 0; k < nof; k++)
			{
				printf("%d\t", frame[k]);
			}
		}
		printf("\n");
	}
	printf("Faults: %d\n", count);
}