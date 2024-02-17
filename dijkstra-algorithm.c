#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int path(int cost[10][10], int s, char p[100])
{
    int cnt = 0;
    int adjecent[10] = {0};
    for (int i = 0; i < 10; i++)
    {
        if (cost[s][i] != 10000)
        {
            cnt++;
            adjecent[i] = 1;
        }
    }
    if (cnt == 0 || cnt == 1)
    {
        sprintf(p, "n");
        return 0;
    }
    sprintf(p, "%d,", s);
    int total_min = 10000;
    for (int i = 0; i < 10; i++)
    {
        int total_cost = 0;
        if (adjecent[i] == 1)
        {
            total_cost += cost[s][i];
            int temp[10][10];
            for (int j = 0; j < 10; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    if ((j == s && k == i) || (j == i && k == s))
                    {
                        temp[j][k] = 10000;
                    }
                    else
                    {
                        temp[j][k] = cost[j][k];
                    }
                }
            }
            int visited[10] = {0};
            int prev[10] = {0};
            int dist[10] = {0};
            visited[i] = 1;
            int cur = i;
            for (int j = 0; j < 10; j++)
            {
                if (j == i)
                {
                    dist[j] = 0;
                    prev[j] = -1;
                }
                else
                {
                    dist[j] = 10000;
                }
            }
            for (int j = 0; j < 10; j++)
            {
                int min = 10000;
                int min_index = 0;
                for (int k = 0; k < 10; k++)
                {
                    // check if adjecent
                    if (temp[cur][k] != 10000 && visited[k] == 0)
                    {
                        // update distance and prev
                        if (dist[k] > dist[cur] + temp[cur][k])
                        {
                            dist[k] = dist[cur] + temp[cur][k];
                            prev[k] = cur;
                        }
                    }
                }
                for (int k = 0; k < 10; k++)
                {
                    if (visited[k] == 0 && dist[k] != 10000 && dist[k] < min)
                    {
                        min = dist[k];
                        min_index = k;
                    }
                }
                if (min == 10000)
                {
                    break;
                }
                visited[min_index] = 1;
                cur = min_index;
            }

            // print dist and prev
            for (int j = 0; j < 10; j++)
            {
                printf("%d ", dist[j]);
            }
            printf("\n");
            for (int j = 0; j < 10; j++)
            {
                printf("%d ", prev[j]);
            }
            printf("\n");
            printf("\n");
            if (total_cost + dist[s] < total_min)
            {
                total_min = total_cost + dist[s];
                char temp_p[100];
                int num = 0;
                cur = s;
                while (cur != -1)
                {
                    sprintf(temp_p + num, "%d", cur);
                    cur = prev[cur];
                    num += 1;
                }
                // reverse temp_p
                for (int j = 1; j <= num; j++)
                {
                    if(j == num){
                        sprintf(p + 2 * j, "%d", temp_p[(num - j)] - '0');
                    }
                    else{
                        sprintf(p + 2 * j, "%d,", temp_p[(num - j)]-'0');
                    }
                }
            }
        }
    }

    return 0;
}

int main()
{

    int cost[10][10];
    int n, i, j, s, d;
    char p[100];

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            cost[i][j] = 10000;
        }
    }

    cost[0][1] = 1;
    cost[0][3] = 4;
    cost[1][0] = 1;
    cost[1][2] = 3;
    cost[1][4] = 1;
    cost[2][1] = 3;
    cost[2][4] = 1;
    cost[2][5] = 2;
    cost[3][0] = 4;
    cost[3][4] = 1;
    cost[4][1] = 1;
    cost[4][2] = 1;
    cost[4][3] = 1;
    cost[5][2] = 2;

    printf("Source: ");
    scanf("%d", &s);
    path(cost, s, p);

    if (p[0] == 'n')
    {
        printf("There is no path\n");
    }
    else
    {
        printf("The shortest path is %s\n", p);
    }

    return 0;
}
