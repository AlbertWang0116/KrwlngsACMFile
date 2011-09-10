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
#define N 1000
#define M 10100
edge e[M];
node way[M];
int rd[N], cpn[N], seq[N], col[N], pre[N];
bool vst[N], chs[N], use[M];
int n, m, cnt, cc, rc;

void input()
{
	int i, id1, id2;
	char tag1, tag2;
	for (i = 0; i < n; ++i) { cpn[2*i] = 2*i+1; cpn[2*i+1] = 2*i; } rc = 0;
	memset(rd, 0, sizeof(rd));
	for (i = 0; i < m; ++i)
	{
		scanf("%d%c%d%c", &id1, &tag1, &id2, &tag2);
		if (tag1 == 'h') id1 = id1 * 2; else id1 = id1 * 2 + 1;
		if (tag2 == 'h') id2 = id2 * 2; else id2 = id2 * 2 + 1;
		way[++rc].des = cpn[id1]; way[rc].next = rd[id2]; rd[id2] = rc;
		e[rc].st = id2; e[rc].ed = cpn[id1]; 
		way[++rc].des = cpn[id2]; way[rc].next = rd[id1]; rd[id1] = rc;
		e[rc].st = id1; e[rc].ed = cpn[id2];
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
	int i, j;
	vst[x] = true; col[x] = c;
	for (i = rd[cpn[x]]; i; i = way[i].next)
	{
		j = cpn[way[i].des];
		if (!vst[j]) dfs2(j, c);
	}
}

bool prejudge()
{
	int i;
	memset(vst, false, sizeof(vst)); cnt = 0; dfs(0);
	for (i = 0; i < n; ++i) if (vst[i*2] && vst[i*2+1]) return false;
	return true;
}

void release(int x)
{
	int i, j;
	cc+=2; chs[x] = true; chs[cpn[x]] = false; vst[x] = vst[cpn[x]] = true;
	for (i = rd[x]; i; i = way[i].next) pre[way[i].des]--;
}

void conduct()
{
	int i, j;
	if (!prejudge()) { printf("bad luck\n"); return; }
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 0; i < 2*n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 2*n; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
//	for (i = 0; i < 2*n; ++i) col[i] = i+1; cnt = 2*n;
	for (i = 0; i < n; ++i) if (col[i*2] == col[i*2+1]) break;
	if (i < n) { printf("bad luck\n"); return; }
	for (i = 1; i <= rc; ++i) if (col[e[i].st] == col[e[i].ed]) use[i] = false;
	else { e[i].st = col[e[i].st]; e[i].ed = col[e[i].ed]; }
	for (i = 0; i < 2*n; ++i) seq[col[i]] = col[cpn[i]];
	for (i = 1; i <= cnt; ++i) cpn[i] = seq[i];
	memset(rd, 0, sizeof(rd)); memset(pre, 0, sizeof(pre));
	for (i = 1; i <= rc; ++i) if (use[i]) { 
		way[i].des = e[i].st; way[i].next = rd[e[i].ed]; rd[e[i].ed] = i; pre[e[i].st]++;
	}
	memset(vst, false, sizeof(vst)); vst[col[1]] = true; memset(chs, false, sizeof(chs)); cc = 0;
	for (j = 1; j <= cnt / 2; ++j) for (i = 1; i <= cnt; ++i) if (!pre[i] && !vst[i]) release(i);
	for (i = 2; i < 2*n; ++i) if (!chs[col[i]])
		if (i % 2) printf("%dw ", i / 2); else printf("%dh ", i / 2);	
	printf("\n");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d%d", &n, &m) != EOF && n+m)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

