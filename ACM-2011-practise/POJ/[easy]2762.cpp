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

struct edge { int st, ed; };
struct node { int des, next; };
#define N 1010
#define M 100010
edge e[M];
node way[M];
int seq[N], col[N], pre[N], pst[N], rd[N], ld[N];
bool vst[N], use[M];
int n, m, cnt, rc;


void input()
{
	int i, st, ed;
	scanf("%d %d", &n, &m);
	memset(rd, 0, sizeof(rd)); memset(ld, 0, sizeof(ld)); rc = 0;
	for (i = 1; i <= m; ++i) {
		scanf("%d %d", &st, &ed);
		rc++; way[rc].des = ed; way[rc].next = rd[st]; rd[st] = rc;
		rc++; way[rc].des = st; way[rc].next = ld[ed]; ld[ed] = rc;
		e[i].st = st; e[i].ed = ed;
	}
	memset(use, true, sizeof(use));
}

void dfs(int x)
{
	int i;
	vst[x] = true;
	for (i = rd[x]; i; i = way[i].next) if (!vst[way[i].des]) dfs(way[i].des);
	seq[++cnt] = x;
}

void dfs2(int x, int c)
{
	int i;
	vst[x] = true; col[x] = c;
	for (i = ld[x]; i; i = way[i].next) if (!vst[way[i].des]) dfs2(way[i].des, c);
}

void conduct()
{
	int i, prc, psc;
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 1; i <= n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = n; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
	for (i = 1; i <= m; ++i) if (col[e[i].st] == col[e[i].ed]) use[i] = false;
	else { e[i].st = col[e[i].st]; e[i].ed = col[e[i].ed]; }
	memset(pre, 0, sizeof(pre)); memset(pst, 0, sizeof(pst));
	for (i = 1; i <= m; ++i) if (use[i]) { pre[e[i].ed]++; pst[e[i].st]++; }
	for (prc = psc = 0, i = 1; i <= cnt; ++i) {
		if (!pre[i]) prc++; if (!pst[i]) psc++;
	}
	if (prc == 1 && psc == 1) printf("Yes\n"); else printf("No\n");
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

