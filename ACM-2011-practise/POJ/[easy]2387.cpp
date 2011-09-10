#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

#define N 1010
#define MAX 1000000
int seq[N], des[N], dis[N][N], len[N][N], way[N][N];
bool vst[N];
int n, m;

void input()
{
	int i, j;
	int st, ed, len;
	scanf("%d %d", &m, &n);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j) dis[i][j] = MAX;
	for (i = 0; i < m; ++i)
	{
		scanf("%d %d %d", &st, &ed, &len);
		if (dis[st][ed] > len) dis[st][ed] = len;
		if (dis[ed][st] > len) dis[ed][st] = len;
	}
}

void conduct()
{
	int i, j, ele;
	int head, tail, top;
	memset(way, 0, sizeof(way));
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) if (dis[i][j] != MAX)
	{
		++way[i][0]; way[i][way[i][0]] = j; len[i][way[i][0]] = dis[i][j];
	}
	head = 0; tail = 0; seq[0] = 1; top = 1;
	memset(vst, false, sizeof(vst)); vst[1] = true;
	for (i = 1; i <= n; ++i) des[i] = MAX; des[1] = 0;
	for (head = 0; top; head = (head + 1) % n)
	{
		ele = seq[head]; top--; vst[ele] = false;
		for (i = 1; i <= way[ele][0]; ++i) if (des[way[ele][i]] > des[ele] + len[ele][i])
		{
			des[way[ele][i]] = des[ele] + len[ele][i];
			if (!vst[way[ele][i]]) { vst[way[ele][i]] = true; tail = (tail + 1) % n; seq[tail] = way[ele][i]; top++;}
		}
	}
	printf("%d\n", des[n]);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

