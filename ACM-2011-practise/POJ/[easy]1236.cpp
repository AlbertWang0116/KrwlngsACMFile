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
struct edge2 { int des, next; };
#define N 110
#define M 10010
edge e[M];
edge2 ati[M], way[M];
int rd[N], ld[N], seq[N], col[N], pre[N], pst[N];
bool use[M], vst[N];
int n, m, cnt;

int getmax(int x, int y) { return x > y ? x : y; }

void input()
{
	int i, ed;
	scanf("%d", &n); m = 0;
	for (i = 1; i <= n; ++i) while (scanf("%d", &ed) != EOF && ed) { ++m; e[m].st = i; e[m].ed = ed; }
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
	for (i = ld[x]; i; i = ati[i].next) if (!vst[ati[i].des]) dfs2(ati[i].des, c);
}

void conduct()
{
	int i, head, tail;
	memset(rd, 0, sizeof(rd)); memset(ld, 0, sizeof(ld));
	for (i = 1; i <= m; ++i) { way[i].des = e[i].ed; way[i].next = rd[e[i].st]; rd[e[i].st] = i; }
	for (i = 1; i <= m; ++i) { ati[i].des = e[i].st; ati[i].next = ld[e[i].ed]; ld[e[i].ed] = i; }
	cnt = 0; memset(vst, false, sizeof(vst));
	for (i = 1; i <= n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = n; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
	for (i = 1; i <= m; ++i)
		if (col[e[i].st] == col[e[i].ed]) use[i] = false;
		else { e[i].st = col[e[i].st]; e[i].ed = col[e[i].ed]; }
	memset(pre, 0, sizeof(pre)); memset(pst, 0, sizeof(pst));
	for (i = 1; i <= m; ++i) if (use[i]) { pre[e[i].ed]++; pst[e[i].st]++; }
	head = tail = 0;
	for (i = 1; i <= cnt; ++i)
	{
		if (!pre[i]) head++;
		if (!pst[i]) tail++;
	}
	printf("%d\n", head);
	if (cnt == 1) printf("0\n");
	else printf("%d\n", getmax(head, tail));
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

