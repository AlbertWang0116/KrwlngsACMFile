#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

struct edge { int nxt, des, flow, cap, rev; };
#define N 610
const int INF_FLOW=LONG_MAX;
edge e[N];
int dis[N], way[N][N], hd[N], que[N];
int cnt, n, m;

int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int z) {
	if (!way[x][y]) {
		way[x][y]=++cnt; 
		if (way[y][x]) { e[cnt].rev=way[y][x]; e[way[y][x]].rev=cnt; }
		e[cnt].nxt=hd[x]; e[cnt].flow=e[cnt].cap=0; e[cnt].des=y; hd[x]=cnt;
	}
	e[way[x][y]].cap+=z;
}

int dinic_dfs(int s, int t, int mf) {
	int i, tf, f;
	if (dis[s]==dis[t]) return s==t?mf:0;
	for (f=mf, i=hd[s]; f&&i; i=e[i].nxt) 
		if (e[i].cap && dis[e[i].des]==dis[s]+1) {
			tf=dinic_dfs(e[i].des, t, getmin(f, e[i].cap));
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
	}
	return mf-f;
}

int dinic(int s, int t) {
	int i, head, tail, u, f;
	for (f=0; 1; ) {
		memset(dis, -1, sizeof(dis)); dis[s]=0;
		que[0]=s; head=tail=0;
		while (head<=tail) {
			u=que[head++];
			for (i=hd[u]; i; i=e[i].nxt) 
				if (e[i].cap && dis[e[i].des]<0) dis[que[++tail]=e[i].des] = dis[u]+1;
		}
		if (dis[t]<0) return f;
		f+=dinic_dfs(s, t, INF_FLOW);
	}
}

void conduct() {
	int i, u, v, tmp;
	memset(hd, 0, sizeof(hd));
	memset(way, 0, sizeof(way));
	for (cnt=i=0; i<m; ++i) {
		scanf("%d%d%d", &u, &v, &tmp); --u; --v;
		insert(u, v, tmp); insert(v, u, 0);
	}
	printf("%d\n", dinic(0, n-1));
}

int main() {
	while (scanf("%d%d", &m, &n)!=EOF) conduct();
	return 0;
}
