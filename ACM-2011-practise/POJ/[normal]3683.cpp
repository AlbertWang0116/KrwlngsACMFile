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
#define N 2010
#define M 4000010
edge e[M], info[N];
node way[M];
int seq[N], col[N], rd[N], pre[N], cpn[N];
bool vst[N], chs[N], use[M];
int n, rc, cc, cnt;

bool judge(int x, int y) { return (info[x].ed > info[y].st && info[y].ed > info[x].st); }

void input()
{
	int i, j, sth, stm, edh, edm, itv;
	char tmp1, tmp2;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) { cpn[i*2-1] = i*2; cpn[i*2] = i*2-1; }
	for (i = 1; i <= n; ++i) {
		scanf("%d%c%d %d%c%d %d", &sth, &tmp1, &stm, &edh, &tmp2, &edm, &itv);
		info[i*2-1].st= sth * 60 + stm; info[i*2-1].ed = info[i*2-1].st + itv;
		info[i*2].ed = edh * 60 + edm; info[i*2].st = info[i*2].ed - itv;
	} n *= 2;
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 1; i <= n; ++i) for (j = i+1; j <= n; ++j) if (j != cpn[i] && judge(i, j)) {
		way[++rc].des = i; way[rc].next = rd[cpn[j]]; rd[cpn[j]] = rc;
		e[rc].st = cpn[j]; e[rc].ed = i;
		way[++rc].des = j; way[rc].next = rd[cpn[i]]; rd[cpn[i]] = rc;
		e[rc].st = cpn[i]; e[rc].ed = j;
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
	vst[x] = true; col[x] = c;
	for (i = rd[cpn[x]]; i; i = way[i].next) if (!vst[cpn[way[i].des]]) dfs2(cpn[way[i].des], c);
}

void release(int x)
{
	int i;
	cc+= 2; vst[x] = true; vst[cpn[x]] = true; chs[x] = true; chs[cpn[x]] = false;
	for (i = rd[x]; i; i = way[i].next) pre[way[i].des]--;
}

void conduct()
{
	int i;
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 1; i <= n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = n; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
	for (i = 1; i <= n; ++i) if (col[i] == col[cpn[i]]) { printf("NO\n"); return; }
	printf("YES\n");
	for (i = 1; i <= n; ++i) seq[col[i]] = col[cpn[i]];
	for (i = 1; i <= cnt; ++i) cpn[i] = seq[i];
	memset(use, true, sizeof(use));
	for (i = 1; i <= rc; ++i) if (col[e[i].st] == col[e[i].ed]) use[i] = false;
	else { e[i].st = col[e[i].st]; e[i].ed = col[e[i].ed]; }
	memset(rd, 0, sizeof(rd)); memset(pre, 0, sizeof(pre));
	for (i = 1; i <= rc; ++i) if (use[i]) {
		way[i].des = e[i].ed; way[i].next = rd[e[i].st]; rd[e[i].st] = i; pre[e[i].ed]++;
	} 
	memset(vst, false, sizeof(vst)); cc = 0;
	while (cc < cnt) for (i = 1; i <= cnt; ++i) if (!vst[i] && !pre[i]) release(i);
	for (i = 1; i <= n; ++i) if (chs[col[i]]) {
		if (info[i].st / 60 < 10) printf("0"); printf("%d:", info[i].st / 60); 
		if (info[i].st % 60 < 10) printf("0"); printf("%d ", info[i].st % 60); 
		if (info[i].ed / 60 < 10) printf("0"); printf("%d:", info[i].ed / 60); 
		if (info[i].ed % 60 < 10) printf("0"); printf("%d\n", info[i].ed % 60); 
	}
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

