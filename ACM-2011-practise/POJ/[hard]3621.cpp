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

struct node { int des, next; double val, hei; };
#define N 1010
#define M 5010
const double inf = 2e6;
const double eps = 1e-3;
int rd[N], v[N];
node way[M];
int seq[N], pos[N], pre[N];
double dis[N];
double mid, lst, mst;
int n, m;


void input()
{
	int i, st, ed, len;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%d", &v[i]);
	memset(rd, 0, sizeof(rd));
	for (i = 1; i <= m; ++i)
	{
		scanf("%d %d %d", &st, &ed, &len);
		way[i].des = ed; way[i].val = v[ed]; way[i].hei = len;
		if (st == ed) continue;
		way[i].next = rd[st]; rd[st] = i;
	}
}

bool spfa()
{
	int i, ele, head, tail, cnt;
	for (i = 1; i <= n; ++i) dis[i] = inf; dis[1] = 0;
	seq[1] = 1; head = 1; tail = 1; cnt = 1; pre[1] = 0;
	memset(pos, 0, sizeof(pos)); pos[1] = 1;
	while (cnt--)
	{
		ele = seq[head]; head++; if (head > n) head = 1; pos[ele] = 0;
		for (i = rd[ele]; i; i = way[i].next) if (dis[way[i].des] > dis[ele] + way[i].hei * mid - way[i].val) {
			if (!pos[way[i].des]) {cnt++; tail++; if (tail > n) tail = 1; pos[way[i].des] = tail; seq[tail] = way[i].des; }
			dis[way[i].des] = dis[ele] + way[i].hei * mid - way[i].val; pre[way[i].des] = pre[ele] + 1;
			if (pre[way[i].des] >= n) return false;
		}
	}
	return true;
}

void conduct()
{
	lst = 0; mst = inf;
	while (mst - lst > eps)
	{
		mid = (lst + mst) / 2;
		if (spfa()) mst = mid; else lst = mid;
	}
	if (inf - mst < eps) printf("0\n");
	else printf("%.2f\n", (lst + mst)/2);
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

