#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define MAX 10000000
#define N 210
double way[N][N], dis[N];
int x[N], y[N];
bool visit[N];
int n, m, test_id;

double my_max(double x, double y)
{
	return (x > y ? x : y);
}

void input()
{
	int i, j;
	for (i = 0; i < n; ++i) scanf("%d %d", &x[i], &y[i]);
	for (i = 0; i < n; ++i)
		for (j = i + 1; j < n; ++j)
		{
			way[i][j] = sqrt((double)(x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
			way[j][i] = way[i][j];
		}
}

void conduct()
{
	int i, j, k;
	double minval;
	for (i = 1; i < n; ++i) dis[i] = way[0][i];
	memset(visit, true, sizeof(visit));
	for (i = 1; i < n; ++i)
	{
		minval = MAX;
		for (j = 1; j < n; ++j)
			if (visit[j] && minval > dis[j]) { minval = dis[j]; k = j;}
		visit[k] = false;
		if (k == 1) break;
		for (j = 1; j < n; ++j)
			if (visit[j] && dis[j] > my_max(dis[k], way[k][j])) dis[j] = my_max(dis[k], way[k][j]);
	}
	cout << "Scenario #" << test_id << endl;
	printf("Frog Distance = %.3f\n\n", dis[1]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	test_id = 0;
	while (cin >> n)
	{
		if (n == 0) break;
		++test_id;
		input();
		conduct();
	}
	fclose(stdin);
	fclose(stdout);
}

