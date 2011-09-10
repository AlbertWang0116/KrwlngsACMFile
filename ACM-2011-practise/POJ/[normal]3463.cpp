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
#define N 1010
#define M 10010
const int inf = 100000000;
node way[M], ati[M];
int fwd[N], bck[N], dis[N], atidis[N], cnt[N], aticnt[N];
bool vst[N];
int n, m, st, ed;

void input()
{
	int i, len;
	scanf("%d %d", &n, &m);
	memset(fwd, 0, sizeof(fwd)); memset(bck, 0, sizeof(bck));
	for (i = 1; i <= m; ++i)
	{
		scanf("%d %d %d", &st, &ed, &len);
		way[i].des = ed; way[i].next = fwd[st]; fwd[st] = i;
		ati[i].des = st; ati[i].next = bck[ed]; bck[ed] = i;
		way[i].len = ati[i].len = len;
	}
	scanf("%d %d", &st, &ed);
}

void conduct()
{
	int i, j, k, l, ans;
	for (i = 1; i <= n; ++i) atidis[i] = inf; memset(vst, false, sizeof(vst)); memset(aticnt, 0, sizeof(aticnt));
	atidis[ed] = 0; aticnt[ed] = 1;
	for (i = 1; i <= n; ++i)
	{
		k = inf;
		for (j = 1; j <= n; ++j) if (!vst[j] && atidis[j] < k) { k = atidis[j]; l = j; }
		vst[l] = true;
		for (j = bck[l]; j; j = ati[j].next) if (!vst[ati[j].des])
			if (atidis[l] + ati[j].len == atidis[ati[j].des]) aticnt[ati[j].des] += aticnt[l];
			else if (atidis[l] + ati[j].len < atidis[ati[j].des]) { atidis[ati[j].des] = atidis[l] + ati[j].len; aticnt[ati[j].des] = aticnt[l]; }
	}
	for (i = 1; i <= n; ++i) dis[i] = inf; memset(vst, false, sizeof(vst)); memset(cnt, 0, sizeof(cnt));
	dis[st] = 0; cnt[st] = 1;
	for (i = 1; i <= n; ++i)
	{
		k = inf;
		for (j = 1; j <= n; ++j) if (!vst[j] && dis[j] < k) { k = dis[j]; l = j; }
		vst[l] = true;
		for (j = fwd[l]; j; j = way[j].next) if (!vst[way[j].des])
			if (dis[l] + way[j].len == dis[way[j].des]) cnt[way[j].des] += cnt[l];
			else if (dis[l] + way[j].len < dis[way[j].des]) { dis[way[j].des] = dis[l] + way[j].len; cnt[way[j].des] = cnt[l]; }
	}
//	for (i = 1; i <= n; ++i) printf("index:%d dis:%d cnt:%d aticnt:%d\n", i, dis[i], cnt[i], aticnt[i]);
	ans = cnt[ed];
	for (i = 1; i <= n; ++i) if (dis[i] + atidis[i] == dis[ed])
		for (j = fwd[i]; j; j = way[j].next) if (dis[i] + way[j].len + atidis[way[j].des] == dis[ed] + 1) ans += cnt[i] * aticnt[way[j].des];
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
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

