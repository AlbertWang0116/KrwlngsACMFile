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

struct node { int p1, p2, dis; };
struct node2 { int idx, next; };
#define N 110
#define M 10010
#define L 15
#define inf 1e8
char name[N][L];
int head[N], rd[N];
node2 way[M], road[M];
node info[M];
int dis[N], idx[N], col[N], lst[N];
bool use[M], vst[N];
int n, m, dgr, ans;


int getidx(char* str)
{
	int i;
	for (i = 0; i <= n; ++i) if (!strcmp(name[i], str)) return i;
	strcpy(name[++n], str);
	return n;
}

void input()
{
	int i, tmp;
	char name1[L], name2[L];
	n = 0; strcpy(name[0], "Park");
	scanf("%d", &m); info[0].dis = -inf;
	for (i = 1; i <= m; ++i)
	{
		scanf("%s %s %d", name1, name2, &info[i].dis);
		info[i].p1 = getidx(name1); info[i].p2 = getidx(name2);
		if (info[i].p1 > info[i].p2) { tmp = info[i].p1; info[i].p1 = info[i].p2; info[i].p2 = tmp; }
	}
	scanf("%d", &dgr);
	memset(rd, 0, sizeof(rd));
	for (i = 1; i <= m; ++i)
	{
		way[2*i-1].idx = i; way[2*i-1].next = rd[info[i].p1]; rd[info[i].p1] = 2*i-1;
		if (info[i].p1 == 0) continue;
		way[2*i].idx = i; way[2*i].next = rd[info[i].p2]; rd[info[i].p2] = 2*i;
	}
}

void prim(int st, int color)
{
	int j, k, l, des;
	bool find;
	dis[st] = 0; idx[st] = 0; find = true;
	while (find)
	{
		find = false; l = inf;
		for (j = 1; j <= n; ++j) if (!vst[j] && dis[j] < l) { find = true; l = dis[j]; k = j; }
		if (!find) break;
		col[k] = color; use[idx[k]] = true; vst[k] = true; ans += dis[k];
		for (j = rd[k]; j; j = way[j].next)
		{
			if (k == info[way[j].idx].p1) des = info[way[j].idx].p2; else des = info[way[j].idx].p1;
			if (info[way[j].idx].dis < dis[des]) { dis[des] = info[way[j].idx].dis; idx[des] = way[j].idx; }
		}
	}
}

void dfs(int root, int from, int chose)
{
	int i, des; vst[root] = true;
	if (info[from].dis > info[chose].dis) lst[root] = from; else lst[root] = chose;
	for (i = head[root]; i; i = road[i].next)
	{
		if (root == info[road[i].idx].p1) des = info[road[i].idx].p2; else des = info[road[i].idx].p1;
		if (!vst[des]) dfs(des, road[i].idx, lst[root]);
	}
}

void delroad(int pnt, int idx)
{
	int p, q;
	if (road[head[pnt]].idx == idx) head[pnt] = road[head[pnt]].next;
	else for (p = head[pnt], q = road[head[pnt]].next; q; p = road[p].next, q = road[q].next) if (idx == road[q].idx) { road[p].next = road[q].next; return; }
}

bool spread()
{
	int dec, add, del;
	int i, des;
	dec = 0;
	for (i = rd[0]; i; i = way[i].next)
	{
		des = info[way[i].idx].p2;
		if (info[way[i].idx].dis - info[lst[des]].dis < dec)
		{
			dec = info[way[i].idx].dis - info[lst[des]].dis;
			add = way[i].idx;
			del = lst[des];
		}
	}
	if (dec >= 0) return false;
	road[add*2-1].idx = add; road[add*2-1].next = head[0]; head[0] = add*2-1;
	road[add*2].idx = add; road[add*2].next = head[info[add].p2]; head[info[add].p2] = add*2;
	delroad(info[del].p1, del);
	delroad(info[del].p2, del);
	ans += dec;
	memset(vst, false, sizeof(vst)); vst[0] = true;
	dfs(info[add].p2, add, 0);
	return true;
}

void conduct()
{
	int i, j;
	memset(use, false, sizeof(use));
	memset(vst, false, sizeof(vst)); ans = 0;
	for (i = 1; i <= n; ++i) dis[i] = inf;
	for (i = 1, j = 0; i <= n; ++i) if (!vst[i]) prim(i, ++j);
	for (i = 1; i <= j; ++i) lst[i] = inf;
	for (i = rd[0]; i; i = way[i].next) if (info[way[i].idx].dis < lst[col[info[way[i].idx].p2]])
	{
		lst[col[info[way[i].idx].p2]] = info[way[i].idx].dis; idx[col[info[way[i].idx].p2]] = way[i].idx;
	}
	for (i = 1; i <= j; ++i) { use[idx[i]] = true; ans += info[idx[i]].dis; }
	memset(head, 0, sizeof(head));
	for (i = 1; i <= m; ++i) if (use[i])
	{
		road[2*i-1].idx = i; road[2*i-1].next = head[info[i].p1]; head[info[i].p1] = 2*i-1;
		road[2*i].idx = i; road[2*i].next = head[info[i].p2]; head[info[i].p2] = 2*i;
	}
	memset(vst, false, sizeof(vst)); dfs(0, 0, 0);
	while (j < dgr && spread()) ++j;
	printf("Total miles driven: %d\n", ans);
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

