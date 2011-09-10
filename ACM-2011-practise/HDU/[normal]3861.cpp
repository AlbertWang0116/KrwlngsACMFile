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

#define getmax(x, y) (x)>(y)?(x):(y)
struct edge { int st, ed; };
struct node { int d, next; };
#define N 5010
#define M 100010
node w[M*2];
edge e[M];
int rd[N], ld[N], seq[N], pro[N], col[N];
bool use[M], vst[N], lst[N], fst[N], edg[N][N];
int n, m, rc, cnt;

void input()
{
	int i;
	scanf("%d%d", &n, &m);
	memset(rd, 0, sizeof(rd)); memset(ld, 0, sizeof(ld)); rc = 0;
//	printf("input start\n");
	for (i = 1; i <= m; ++i) {
		scanf("%d%d", &e[i].st, &e[i].ed);
		rc++; w[rc].d = e[i].ed; w[rc].next = rd[e[i].st]; rd[e[i].st] = rc;
		rc++; w[rc].d = e[i].st; w[rc].next = ld[e[i].ed]; ld[e[i].ed] = rc;
	}
//	printf("input end\n");
}

void dfs(int x) {
//	printf("x:%d\n", x);
	int i; vst[x] = true;
	for (i = rd[x]; i; i = w[i].next) if (!vst[w[i].d]) dfs(w[i].d);
	seq[++cnt] = x;
}

void dfs2(int x, int c) {
	vst[x] = true; col[x] = c;
	for (int i = ld[x]; i; i = w[i].next) if (!vst[w[i].d]) dfs2(w[i].d, c);
}

bool match(int x) {
	for (int i = rd[x]; i; i = w[i].next) if (!vst[w[i].d]) {
		vst[w[i].d] = true; if (!ld[w[i].d] || match(ld[w[i].d])) { ld[w[i].d] = x; return true; }
	} return false;
}

void conduct()
{
	int i, v, ans, head, tail, tag;
	memset(vst, 0, sizeof(vst)); cnt = 0;
	for (i = 1; i <= n; ++i) if (!vst[i]) dfs(i);
	memset(vst, 0, sizeof(vst)); cnt = 0;
	for (i = n; i >= 1; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
//	printf("tarjan result:\n"); for (i = 1; i <= n; ++i) printf("col[%d]=%d\n", i, col[i]);
	memset(use, 1, sizeof(use));
	memset(edg, 0, sizeof(edg)); for (i = 1; i <= cnt; ++i) edg[i][i] = true;
	for (i = 1; i <= m; ++i) if (edg[col[e[i].st]][col[e[i].ed]]) use[i] = false;
	else { e[i].st = col[e[i].st]; e[i].ed = col[e[i].ed]; edg[e[i].st][e[i].ed] = true;} n = cnt;
	memset(rd, 0, sizeof(rd)); memset(ld, 0, sizeof(ld)); rc = 0;
	for (i = 1; i <= m; ++i) if (use[i]) {
		rc++; w[rc].d = e[i].ed; w[rc].next = rd[e[i].st]; rd[e[i].st] = rc;
	}
	for (ans = 0, i = 1; i <= n; ++i) { 
		memset(vst, 0, sizeof(vst));
		if (match(i)) ans++;
	}
	/*memset(pro, 0, sizeof(pro)); memset(vst, 0, sizeof(vst));
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 1; i <= m; ++i) if (use[i]) {
		rc++; w[rc].d = e[i].ed; w[rc].next = rd[e[i].st]; rd[e[i].st] = rc; pro[e[i].st]++; vst[e[i].ed] = true;
	}
	while (true) { 
//		printf("start->cnt: %d\n", cnt);
		memset(fst, 0, sizeof(fst)); memset(lst, 0, sizeof(lst)); memset(col, 0, sizeof(col));
		for (cnt = 0, tag = i = 1; i <= n; ++i) if (!vst[i]) { 
			if (pro[i] == 1) { seq[++cnt] = seq[tag]; seq[tag++] = i; } else seq[++cnt] = i;
			fst[i] = 1; col[i] = cnt;
		}
		for (head = 1, tail = cnt; head <= tail; ++head) {
//			printf("head:%d pro:%d\n", seq[head], pro[seq[head]]);
			v = seq[head]; if (pro[v] != 1) lst[v] = true; tag = getmax(head+1, tag);
			for (i = rd[v]; i; i = w[i].next) if (!col[w[i].d]) {
				if (lst[v]) { col[w[i].d] = ++cnt; fst[w[i].d] = true; } else col[w[i].d] = col[v]; 
				if (pro[w[i].d] == 1) {seq[++tail] = seq[tag]; seq[tag++] = w[i].d; } else seq[++tail] = w[i].d;
			} else if (pro[v] == 1) lst[v] = true;
		} if (cnt == n) break;
//		printf("topology result:\n"); for (i = 1; i <= n; ++i) printf("col[%d]=%d\n", i, col[i]);
//		printf("fst point:"); for (i = 1; i <= n; ++i) if (fst[i]) printf("%d ", i); printf("\n");
//		printf("lst point:"); for (i = 1; i <= n; ++i) if (lst[i]) printf("%d ", i); printf("\n");
		for (i = 1; i <= m; ++i) if (use[i] && fst[e[i].ed] && lst[e[i].st]) {
//			printf("before[st:%d ed:%d] ", e[i].st, e[i].ed);
			e[i].st = col[e[i].st]; e[i].ed = col[e[i].ed];
//			printf("after[st:%d ed:%d]\n", e[i].st, e[i].ed);
		} else use[i] = false;
		memset(pro, 0, sizeof(pro)); memset(vst, 0, sizeof(vst));
		memset(rd, 0, sizeof(rd)); rc = 0;
		for (i = 1; i <= m; ++i) if (use[i]) {
			rc++; w[rc].d = e[i].ed; w[rc].next = rd[e[i].st]; rd[e[i].st] = rc; pro[e[i].st]++; vst[e[i].ed] = true;
		} n = cnt;
	}*/
	printf("%d\n", n-ans);
}


int main()
{
	int time; scanf("%d", &time);
	while (time--) { input(); conduct(); }
	return 0;
}
