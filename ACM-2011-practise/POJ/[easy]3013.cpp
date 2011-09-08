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

struct node { int des, next; int len; };
#define N 100010
const long long inf = 100000000000;
int rd[N], heap[N], ati[N];
long long dis[N], val[N];
bool vst[N];
node way[N];
int n, m;

void input()
{
	int i, st, ed;
	int len;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%lld", &val[i]);
	memset(rd, 0, sizeof(rd));
	for (i = 1; i <= m; ++i)
	{
		scanf("%d %d %d", &st, &ed, &len);
		way[i*2-1].des = ed; way[i*2-1].next = rd[st]; rd[st] = i*2-1;
		way[i*2].des = st; way[i*2].next = rd[ed]; rd[ed] = i*2;
		way[i*2-1].len = way[i*2].len = len;
	}
}

int getele()
{
	int i, j, ret, ele;
	ret = heap[1]; ele = heap[heap[0]--];
	for (i = 1, j = (i << 1); j <= heap[0]; i = j, j = (j << 1))
	{
		if (j < heap[0] && dis[heap[j]] > dis[heap[j+1]]) ++j;
		if (dis[ele] > dis[heap[j]]) { heap[i] = heap[j]; ati[heap[i]] = i; } else break;
	}
	heap[i] = ele; ati[ele] = i;
	return ret;
}

void update(int pos)
{
	int i, j, ele;
	ele = heap[pos];
	for (i = pos, j = (pos >> 1); j; i = j, j = (j >> 1)) if (dis[ele] < dis[heap[j]]) { heap[i] = heap[j]; ati[heap[i]] = i; } else break;
	heap[i] = ele; ati[ele] = i;
}

void conduct()
{
	int i, l;
	long long ans;
	memset(vst, false, sizeof(vst));
	memset(ati, 0, sizeof(ati)); heap[0] = 0; for (i = 1; i <= n; ++i) dis[i] = inf;
	ati[1] = 1; heap[++heap[0]] = 1; dis[1] = 0;
	while (heap[0])
	{
		l = getele(); vst[l] = true;
		for (i = rd[l]; i; i = way[i].next) if (!vst[way[i].des] && dis[l] + way[i].len < dis[way[i].des])
		{
			if (!ati[way[i].des]) { heap[++heap[0]] = way[i].des; ati[way[i].des] = heap[0]; }
			dis[way[i].des] = dis[l] + way[i].len; update(ati[way[i].des]);
		}
	}
	for (i = 1; i <= n; ++i) if (!vst[i]) { printf("No Answer\n"); return; }
	for (i = 1, ans = 0; i <= n; ++i) ans += dis[i] * val[i];
	printf("%lld\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
//	printf("%lld\n", inf);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

