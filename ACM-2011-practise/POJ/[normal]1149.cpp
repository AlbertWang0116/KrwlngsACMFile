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

struct node { int d, c, f, r, next; };
#define N 210
#define M 2010
#define L 20010
const int MAX = 1000010;
int e[N][N], rd[N], tr[N], pre[M], val[M], seq[N];
node w[L];
int n, m, rc;

void input()
{
	int i, j, tmp, des;
	memset(rd, 0, sizeof(rd)); rc = 0;
	memset(e, 0, sizeof(e)); memset(pre, -1, sizeof(pre));
	for (i = 1; i <= m; ++i) scanf("%d", &val[i]);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &tmp);
		for (j = 0; j < tmp; ++j) {
			scanf("%d", &des);
			if (pre[des] < 0) e[0][i] += val[des]; else e[pre[des]][i] += MAX;
			pre[des] = i;
		}
		for (j = 0; j < i; ++j) if (e[j][i]) { 
			rc++; w[rc].d = i; w[rc].c = e[j][i]; w[rc].f = 0; w[rc].r = rc+1; w[rc].next = rd[j]; rd[j] = rc;
			rc++; w[rc].d = j; w[rc].c = 0; w[rc].f = 0; w[rc].r = rc-1; w[rc].next = rd[i]; rd[i] = rc;
		}
		scanf("%d", &tmp);
		rc++; w[rc].d = n+1; w[rc].c = tmp; w[rc].f = 0; w[rc].r = rc+1; w[rc].next = rd[i]; rd[i] = rc;
		rc++; w[rc].d = i; w[rc].c = 0; w[rc].f = 0; w[rc].r = rc-1; w[rc].next = rd[n+1]; rd[n+1] = rc;	
	}
//	for (i = 0; i <= n+1; ++i) {
//		printf("line %d: ", i); for (j = 0; j <= n+1; ++j) printf("%2d ", e[i][j]); printf("\n");
//	}
}

bool bfs()
{
	int head, tail, u, v, i;
	memset(pre, 0, sizeof(pre)); pre[0] = 1;
	for (seq[head = tail = 0] = 0; head <= tail; head++) {
		u = seq[head];
		for (i = rd[u]; i; i = w[i].next) if (w[i].c - w[i].f && !pre[w[i].d]) {
			v = w[i].d; pre[v] = pre[u] + 1; seq[++tail] = v; if (v == n+1) return true;
		}
	}
	return false;
}

void conduct()
{
	int u, v, i, j, flow, lst;
	flow = 0;
	while (bfs()) {
		u = 0; seq[seq[0] = 1] = 0; memcpy(tr, rd, sizeof(rd));
		while (tr[0]) {
			v = w[tr[u]].d;
			if (u != n+1 && tr[u] && pre[u] == pre[v]-1 && w[tr[u]].c - w[tr[u]].f) {
				seq[++seq[0]] = v; u = v;
			} else if (u == n+1) {
				lst = MAX;
				for (i = 1; i < seq[0]; ++i) if (lst > w[tr[seq[i]]].c - w[tr[seq[i]]].f) { lst = w[tr[seq[i]]].c - w[tr[seq[i]]].f; j = i; }
				for (i = 1; i < seq[0]; ++i) { w[tr[seq[i]]].f += lst; w[w[tr[seq[i]]].r].f -= lst; } flow += lst; u = seq[seq[0] = j]; 
			} else { if (!tr[u]) u = seq[--seq[0]]; tr[u] = w[tr[u]].next; }
		}
	} printf("%d\n", flow);
}

int main()
{
	while (scanf("%d%d", &m, &n) != EOF) { input(); conduct(); }
}
