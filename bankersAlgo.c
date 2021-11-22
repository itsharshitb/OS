#include<stdio.h>
int main()
{
    int m, n;
    scanf("%d", &n); //process
    scanf("%d", &m); //resources
    int maxneed[n][m], isCompleted[n];
    for (int i = 0; i < n; i++)
        isCompleted[i] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            scanf("%d", &maxneed[i][j]);
    }
    int allocated[n][m], need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            scanf("%d", &allocated[i][j]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            need[i][j] = maxneed[i][j] - allocated[i][j];
    }
    int ans[n], ind = 0;
    int available[m];
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            flag = 0;
            if (isCompleted[i] == 0)
            {
                for (int j = 0; j < m; j++)
                {
                    if (available[j] < need[i][j])
                    {
                        flag = 1;
                        break;
                    }
                    if (!flag)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            available[j] += allocated[i][j];
                        }
                        isCompleted[i] = 1;
                        ans[ind++] = i;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
        printf("%d\t", ans[i]);
    return 0;
}