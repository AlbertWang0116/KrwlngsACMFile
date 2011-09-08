#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

struct node
{
	int idx, next;
};

#define N 510
#define MAX 1000000
char map[N][N];
int trans[N][N], way[N*N], que[N*N], stp[N*N];
node road[N*N*5];
int cnt, wcnt, n, m;

void road_insert(int st, int ed)
{
	++wcnt;
	road[wcnt].idx = ed;
	road[wcnt].next = way[st];
	way[st] = wcnt;
}

void input()
{
	int i, j, k;
	int idx, tmp, r, c;
	char row[N];
	for (i = 0; i < n; ++i)
	{
		scanf("%s", row);
		for (j = 0; j < m; ++j) map[i][j] = row[j];
	}
	cnt = 0;
	wcnt = 0;
	memset(trans, 0, sizeof(trans));
	memset(way, 0, sizeof(way));
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
			if (map[i][j] != '#')
				trans[i][j] = ++cnt;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
			if (trans[i][j])
			{
				idx = trans[i][j];
				if (i > 0 && trans[i-1][j]) road_insert(idx, trans[i-1][j]);
				if (i < n-1 && trans[i+1][j]) road_insert(idx, trans[i+1][j]);
				if (j > 0 && trans[i][j-1]) road_insert(idx, trans[i][j-1]);
				if (j < m-1 && trans[i][j+1]) road_insert(idx, trans[i][j+1]);
			}
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
		{
			scanf("%d", &tmp);
			for (k = 0; k < tmp; ++k)
			{
				scanf("%d %d", &r, &c);
				road_insert(trans[i][j], trans[r-1][c-1]);
			}
		}
//	for (i = 0; i < n; ++i)
//	{
//		for (j = 0; j < m; ++j) printf(" %d ", trans[i][j]);
//		printf("\n");
//	}
//	for (i = 1; i <= cnt; ++i)
//	{
//		printf("%d: ", i);
//		for (j = way[i]; j != 0; j = road[j].next) printf("%d, ", road[j].idx);
//		printf("\n");
//	}
}

void conduct()
{
	int i, j;
	int head, tail;
	int idx, des, st, ed;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
			if (map[i][j] == 's') st = trans[i][j];
			else if (map[i][j] == 't') ed = trans[i][j];
	que[0] = st;
	tail = 0;
	for (i = 1; i <= cnt; ++i) stp[i] = MAX;
	stp[st] = 0;
	for (head = 0; head <= tail; ++head)
	{
		idx = que[head];
		for (i = way[idx]; i != 0; i = road[i].next)
		{
			des = road[i].idx;
			if (stp[des] > stp[idx]+1)
			{
				que[++tail] = des;
				stp[des] = stp[idx]+1;
			}
		}
	}
	cout << stp[ed] << endl;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d %d", &n, &m) != EOF)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

