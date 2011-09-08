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
#define N 10010
#define M 2000010
edge e[M];
node way[M], ati[M];
int rd[N], ld[N], seq[N], col[N];
bool use[M], vst[N], pst[N];
int n, m, cnt;

void input()
{
	int i;
	scanf("%d", &m);
	for (i = 1; i <= m; ++i) scanf("%d %d", &e[i].st, &e[i].ed);
	memset(use, true, sizeof(use));
	memset(rd, 0, sizeof(rd)); memset(ld, 0, sizeof(ld));
	for (i = 1; i <= m; ++i)
	{
		way[i].des = e[i].ed; way[i].next = rd[e[i].st]; rd[e[i].st] = i;
		ati[i].des = e[i].st; ati[i].next = ld[e[i].ed]; ld[e[i].ed] = i;
	}
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
	col[x] = c; vst[x] = true;
	for (i = ld[x]; i; i = ati[i].next) if (!vst[ati[i].des]) dfs2(ati[i].des, c);
}

void conduct()
{
	int i; bool tag = false;
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 1; i <= n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = n; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
	for (i = 1; i <= m; ++i) if (col[e[i].st] == col[e[i].ed]) use[i] = false;
	else { e[i].st = col[e[i].st]; e[i].ed = col[e[i].ed]; }
	memset(pst, true, sizeof(pst));
	for (i = 1; i <= m; ++i) if (use[i]) pst[e[i].st] = false;
	for (i = 1; i <= n; ++i) if (pst[col[i]]) {
		if (tag) printf(" "); else tag = true;
		printf("%d", i); 
	}
	printf("\n");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF && n)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

