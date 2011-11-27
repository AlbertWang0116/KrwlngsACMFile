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

struct node { int d, next; };
#define N 10010
node w[N];
int rd[N], dis[N], vst[N], stk[N];
int n, rc, top, tag;

void insert(int st, int ed) {
	rc++; w[rc].d = ed; w[rc].next = rd[st]; rd[st] = rc;
}

void dfs1(int x, int rt) {
	int i, j, k, u;
	vst[x] = 1; stk[top++] = x;
	for (i = rd[x]; !tag && i; i = w[i].next) {
		u = w[i].d;
		if (vst[u] && u != rt) {
			for (j = 0; j < top; ++j) if (stk[j] == u) break;
			for (k = 0; k < j; ++k) dis[stk[k]] = j-k;
			for (k = j; k < top; ++k) dis[stk[k]] = 0; tag = 1;
		} else if (vst[u]) continue;
		else dfs1(u, x);
	} --top;
}

void dfs2(int x, int rt) {
	vst[x] = 1; if (dis[x] == -1) dis[x] = dis[rt] + 1;
	for (int i = rd[x]; i; i = w[i].next) if (!vst[w[i].d]) dfs2(w[i].d, x);
}

void conduct() {
	int i, u, v;
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 1; i <= n; ++i) {
		scanf("%d%d", &u, &v);
		insert(u, v); insert(v, u);
	} memset(vst, 0, sizeof(vst));
	memset(dis, -1, sizeof(dis));
	top = tag = 0; dfs1(1, 0); 
	memset(vst, 0, sizeof(vst)); dfs2(1, 0);
	for (i = 1; i <= n; ++i) printf("%d ", dis[i]); printf("\n");
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
