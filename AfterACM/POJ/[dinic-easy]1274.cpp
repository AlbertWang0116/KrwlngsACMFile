#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

struct edge { int nxt, des, flow, cap, rev; };
#define N 610
#define M 100010
edge e[M];
int hd[N], way[N][N], dis[N], que[N];
int n, m, cnt;
const int INF_FLOW = 1010101;

int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int z) {
	if (!way[x][y]) {
		way[x][y]=++cnt;
		if (way[y][x]) { e[cnt].rev=way[y][x]; e[way[y][x]].rev=cnt; }
		e[cnt].nxt=hd[x]; e[cnt].cap=e[cnt].flow=0; e[cnt].des=y; hd[x]=cnt;
	}
	e[way[x][y]].cap+=z;
}

int dinic_dfs(int s, int t, int mf) {
	int f, tf, i;
	if (dis[s]==dis[t]) return s==t?mf:0;
	for (f=mf, i=hd[s]; f&&i; i=e[i].nxt)
		if (e[i].cap && dis[e[i].des]==dis[s]+1) {
			tf=dinic_dfs(e[i].des, t, getmin(f, e[i].cap));
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	return mf-f;
}

int dinic(int s, int t) {
	int i, u, f, head, tail;
	for (f=0; 1; ) {
		memset(dis, -1, sizeof(dis)); dis[s]=0;
		que[0]=s; head=tail=0;
		while (head<=tail) {
			u=que[head++];
			for (i=hd[u]; i; i=e[i].nxt)
				if (e[i].cap && dis[e[i].des]<0) dis[que[++tail]=e[i].des] = dis[u]+1;
		}
		if (dis[t]<0) return f;
		f += dinic_dfs(s, t, INF_FLOW);
	}
}

void conduct() {
	int i, j, k;
	memset(hd, 0, sizeof(hd));
	memset(way, 0, sizeof(way));
	for (cnt=0, i=1; i<=n; ++i) {
		scanf("%d", &j);
		while (j--) {
			scanf("%d", &k);
			insert(i, n+k, 1); insert(n+k, i, 0);
		}
	}
	for (i=1; i<=n; ++i) { insert(0, i, 1); insert(i, 0, 0); }
	for (i=1; i<=m; ++i) { insert(n+i, n+m+1, 1); insert(n+m+1, n+i, 0); }
	printf("%d\n", dinic(0, n+m+1));
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF) conduct();
	return 0;
}
