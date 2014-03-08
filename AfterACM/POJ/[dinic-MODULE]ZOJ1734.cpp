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

struct edge { int nxt, des, cap, flow, rev; };
#define N 120
#define M 51000
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N];
int n, m, cnt, ns, nt;
const int ss = 110;
const int tt = 111;
const int INF_FLOW = 2000000000;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int z) {
	if (!way[x][y]) {
		way[x][y]=++cnt;
		if (way[y][x]) { e[cnt].rev=way[y][x]; e[way[y][x]].rev=cnt; }
		e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=e[cnt].flow=0; hd[x]=cnt;
	}
	e[way[x][y]].cap+=z;
}

int dinic_dfs(int s, int t, int mf) {
	int i, f, tf;
	if (dis[s]==dis[t]) return s==t?mf:0;
	for (i=ce[s], f=mf; f&&i; i=f||!e[i].cap?e[i].nxt:i)
		if (e[i].cap && dis[e[i].des]==dis[s]+1) {
			tf=dinic_dfs(e[i].des, t, getmin(f, e[i].cap));
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	ce[s]=i; return mf-f;
}

int dinic(int s, int t) {
	int i, f, u, head, tail;
	for (f=0; 1; ) {
		memset(dis, -1, sizeof(dis)); memcpy(ce, hd, sizeof(hd)); dis[s]=0;
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
	int i, s, t, tmp;
	char a, b, c, str[256];
	memset(way, 0, sizeof(way)); memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d%c%d", &a, &s, &b, &t, &c, &tmp);
		insert(s, t, tmp); insert(t, s, 0);
	}
	for (i=0; i<ns; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d", &a, &s, &b, &tmp);
		insert(ss, s, tmp); insert(s, ss, 0);
	}
	for (i=0; i<nt; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d", &a, &t, &b, &tmp);
		insert(t, tt, tmp); insert(tt, t, 0);
	}
	printf("%d\n", dinic(ss, tt));
}

int main() {
	while (scanf("%d%d%d%d", &n, &ns, &nt, &m)!=EOF) conduct();
	return 0;
}
