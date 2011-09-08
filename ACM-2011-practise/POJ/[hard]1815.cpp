#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;

struct node { int d, c, r, next; };
#define N 1010
#define M 40010
const int MAX = 10010;
int f[M], col[M], rd[N], tr[N], seq[N], pre[N], key[N], e[N][N]; 
bool vst[N], done[N], chs[N];
node w[M];
int n, rc, cnt, flow, s, t;

void insert(int s, int t, int cap)
{
	rc++; w[rc].d = s; w[rc].c = 0; w[rc].r = rc+1; w[rc].next = rd[t]; rd[t] = rc;
	rc++; w[rc].d = t; w[rc].c = cap; w[rc].r = rc-1; w[rc].next = rd[s]; rd[s] = rc;
}

void input()
{
	int i, j;
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) scanf("%d", &e[i][j]);
//	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) e[i][j] = (e[i][j] || e[j][i]);
//	for (i = 1; i <= n; ++i) { e[i][s] = 0; e[t][i] = 0; }
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 1; i <= n; ++i) {
		insert(i*2-1, i*2, 1); key[i] = rc;
		for (j = 1; j <= n; ++j) if (i != j && e[i][j]) insert(i*2, j*2-1, MAX);
	}
}

bool bfs(int s, int t)
{
	int i, u, v, head, tail;
	memset(pre, 0, sizeof(pre)); pre[s] = 1;
	for (seq[head = tail = 0] = s; head <= tail; ++head) {
		u = seq[head];
		for (i = rd[u]; i; i = w[i].next) if (!pre[w[i].d] && w[i].c - f[i]) {
			v = w[i].d; pre[v] = pre[u] + 1; seq[++tail] = v; if (v == t) return true;
		}
	}
	return false;
}

void dinic(int s, int t)
{
	int i, j, u, v, lst;
	memset(f, 0, sizeof(f)); flow = 0;
	while (bfs(s, t)) {
		u = s; seq[seq[0] = 1] = s; memcpy(tr, rd, sizeof(rd));
		while (tr[s]) {
			v = w[tr[u]].d;
			if (u != t && tr[u] && pre[u] == pre[v] - 1 && w[tr[u]].c - f[tr[u]]) {
				seq[++seq[0]] = v; u = v;
			} else if (u == t) {
				for (lst = MAX, i = 1; i < seq[0]; ++i) 
					if (lst > w[tr[seq[i]]].c - f[tr[seq[i]]]) { lst = w[tr[seq[i]]].c - f[tr[seq[i]]]; j = i; }
				for (i = 1; i < seq[0]; ++i) { f[tr[seq[i]]] += lst; f[w[tr[seq[i]]].r] -= lst; } flow += lst; u = seq[seq[0] = j];
			} else { if (!tr[u]) u = seq[--seq[0]]; tr[u] = w[tr[u]].next; }
		}
	}
}

void dfs(int r, int c)
{
	col[r] = c; int u = w[r].d;
	for (int i = rd[u]; i; i = w[i].next) if (f[i] > 0) dfs(i, c);
}

int getcap(int r, int cut)
{
	if (col[r] == col[cut]) return w[r].c - f[r] + 1;
	if (col[w[r].r] == col[cut]) return w[r].c - f[r] - 1;
	return w[r].c - f[r];
}

bool bfs2(int s, int t, int r, int c)
{
	int u, v, i, head, tail;
	memset(vst, 0, sizeof(vst)); vst[s] = true; w[r].c = 0;
	for (seq[head = tail = 0] = s; head <= tail; ++head) {
		u = seq[head];
		for (i = rd[u]; i; i = w[i].next) if (!vst[w[i].d] && getcap(i, r)) {
			v = w[i].d; vst[v] = true; seq[++tail] = v; if (v == t) { w[r].c = 1; return true; }
		}
	} return false;
}

void dfs2(int p, int c)
{
	for (int i = rd[p]; i; i = w[i].next) if (col[i] == c) { f[i]--; f[w[i].r]++; dfs2(w[i].d, c); }
}

void conduct()
{
	int i, j;
	if (e[s][t]) { printf("NO ANSWER!\n"); return; }
	dinic(s*2, t*2-1); cnt = 0;
	memset(col, 0, sizeof(col));
	for (i = rd[s*2]; i; i = w[i].next) if (f[i] > 0) dfs(i, ++cnt);
//	for (i = 1; i <= rc; ++i) printf("%d: d:%d col:%d\n", i, w[i].d, col[i]);
	memset(chs, 0, sizeof(chs)); memset(done, 0, sizeof(done)); done[0] = true;
	for (i = 1; i <= n; ++i) if (!done[col[key[i]]] && !bfs2(s*2, t*2-1, key[i], col[key[i]])) { chs[i] = true; done[col[key[i]]] = true; dfs2(s*2, col[key[i]]);}
	printf("%d\n", flow);
	if (flow) {
		for (i = 1; i <= n; ++i) if (chs[i]) printf("%d ", i);
		printf("\n");
	}
}

int main()
{
	while (scanf("%d%d%d", &n, &s, &t) != EOF) { input(); conduct(); }
	return 0;
}
