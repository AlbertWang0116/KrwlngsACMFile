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

struct node { int des, next; };
#define N 2010
#define M 4000010
node way[M];
int seq[N], col[N], rd[N], cpn[N];
bool vst[N], spc[N];
int n, m, cnt, rc;

void insert(int st, int ed)
{
	++rc; way[rc].des = ed; way[rc].next = rd[st]; rd[st] = rc;
}

void input()
{
	int i, va, vb, val;
	char op[10];
	scanf("%d %d", &n, &m);
	memset(rd, 0, sizeof(rd)); rc = 0;
	memset(spc, false, sizeof(spc));
	for (i = 1; i <= n; ++i) { cpn[2*i-1] = 2*i; cpn[2*i] = 2*i-1; }
	for (i = 0; i < m; ++i)
	{
		scanf("%d%d%d%s", &va, &vb, &val, op); va++; vb++;
		if (!strcmp(op, "AND")) if (val) { spc[2*va-1] = true; spc[2*vb-1] = true; }
		else { insert(vb*2, va*2-1);  insert(va*2, vb*2-1); }
		if (!strcmp(op, "OR")) if (val) { insert(va*2-1, vb*2); insert(vb*2-1, va*2); }
		else { spc[va*2] = true; spc[vb*2] = true; }
		if (!strcmp(op, "XOR")) if (val) {
			insert(va*2-1, vb*2); insert(va*2, vb*2-1);
			insert(vb*2-1, va*2); insert(vb*2, va*2-1);
		}
		else {
			insert(va*2-1, vb*2-1); insert(va*2, vb*2);
			insert(vb*2-1, va*2-1); insert(vb*2, va*2);
		}
	}
}

void dfs(int x)
{
	int i;
	vst[x] = true;
	for (i = rd[x]; i; i = way[i].next) if (!vst[way[i].des]) dfs(way[i].des);
	if (spc[x] && !vst[cpn[x]]) dfs(cpn[x]);
	seq[++cnt] = x;
}

void dfs2(int x, int c)
{
	int i, j;
	vst[x] = true; col[x] = c;
	for (i = rd[cpn[x]]; i; i = way[i].next) {
		j = cpn[way[i].des];
		if (!vst[j]) dfs2(j, c);
	}
	if (spc[cpn[x]] && !vst[cpn[x]]) dfs2(cpn[x], c);
}

void print(int x)
{
	int i;
	printf("%d:", x); for (i = rd[x]; i; i = way[i].next) printf("[%d]", way[i].des); if (spc[x]) printf("[%d]", cpn[x]); printf("\n");
}

void conduct()
{
	int i;
//	for (i = 1; i <= 2*n; ++i) print(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 1; i <= 2*n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 2*n; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
	for (i = 1; i <= n; ++i) if (col[2*i-1] == col[2*i]) break;
	if (i <= n) printf("NO\n");
	else printf("YES\n");
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

