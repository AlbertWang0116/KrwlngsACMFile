#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define MAXDIS 1001
#define N 110
int dis[N][N];
int n;

void input()
{
	int i, j;
	int des, len, m;
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j)
			if (i != j) dis[i][j] = MAXDIS;
			else dis[i][j] = 0;
	for (i = 1; i <= n; ++i)
	{
		scanf("%d", &m);
		for (j = 0; j < m; ++j)
		{
			scanf("%d %d", &des, &len);
			if (dis[i][des] > len) dis[i][des] = len;
			//printf("dis[%d][%d]=%d\n", i, des, len);
		}
	}
}

void conduct()
{
	int i, j, k;
	int sht, lng, index;
	for (k = 1; k <= n; ++k)
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j)
				if (dis[i][j] > dis[i][k] + dis[k][j]) dis[i][j] = dis[i][k] + dis[k][j];
	//for (i = 1; i <= n; ++i)
		//for (j = 1; j <= n; ++j)
			//printf("dis[%d][%d] = %d\n", i, j, dis[i][j]);
	sht = MAXDIS;
	for (i = 1; i <= n; ++i)
	{
		lng = 0;
		for (j = 1; j <= n; ++j)
			if (dis[i][j] > lng) lng = dis[i][j];
		if (lng < sht) { index = i; sht = lng;}
	}
	if (sht != MAXDIS)
		cout << index << " " << sht << endl;
	else cout << "disjoint" << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while (cin >> n)
	{
		if (n == 0) break;
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

