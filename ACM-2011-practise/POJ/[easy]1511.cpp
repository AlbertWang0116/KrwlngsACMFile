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

struct node { int des, len, next; };
#define N 1000010
#define MAX 1000000000000
node way[N], ati[N];
int fwd[N], bck[N], seq[N];
long long dis1[N], dis2[N];
bool vst[N];
int n, m;

void input()
{
	int i, st, ed, len;
	scanf("%d %d", &n, &m); 
	for (i = 1; i <= n; ++i) { fwd[i] = -1; bck[i] = -1;}
	for (i = 0; i < m; ++i)
	{
		scanf("%d %d %d", &st, &ed, &len);
		way[i].des = ed; way[i].len = len; way[i].next = fwd[st]; fwd[st] = i;
		ati[i].des = st; ati[i].len = len; ati[i].next = bck[ed]; bck[ed] = i;
	}
}

void conduct()
{
	int i, ele, head, tail, top;
	long long ans;
	for (i = 1; i <= n; ++i) { dis1[i] = MAX; dis2[i] = MAX; }  dis1[1] = 0; dis2[1] = 0;
	memset(vst, false, sizeof(vst));
	for (seq[0] = 1, head = 0, tail = 0, top = 1; top; head = (head + 1) % n)
	{
		ele = seq[head]; vst[ele] = false; --top;
		for (i = fwd[ele]; i != -1; i = way[i].next) if (dis1[way[i].des] > dis1[ele] + way[i].len)
		{
			dis1[way[i].des] = dis1[ele] + way[i].len;
			if (!vst[way[i].des]) { vst[way[i].des] = true; tail = (tail+1) % n; seq[tail] = way[i].des; ++top; }
		}
	}
	for (seq[0] = 1, head = 0, tail = 0, top = 1; top; head = (head + 1) % n)
	{
		ele = seq[head]; vst[ele] = false; --top;
		for (i = bck[ele]; i != -1; i = ati[i].next) if (dis2[ati[i].des] > dis2[ele] + ati[i].len)
		{
			dis2[ati[i].des] = dis2[ele] + ati[i].len;
			if (!vst[ati[i].des]) { vst[ati[i].des] = true; tail = (tail + 1) % n; seq[tail] = ati[i].des; ++top; }
		}
	}
	ans = 0;
	for (i = 2; i <= n; ++i) ans += dis1[i] + dis2[i];
	printf("%lld\n", ans);
}

int main()
{
	int time;
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

