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
#define N 610
edge e[N];
int way[N][N], hd[N], ce[N], dis[N], que[N];
int n, m, cnt;
const int INF_FLOW = LONG_MAX;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int z) {
	if (!way[x][y]) {
		way[x][y]=++cnt;
		if (way[y][x]) { e[cnt].rev=way[y][x]; e[way[y][x]].rev=cnt; }
		e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=e[cnt].flow=0; hd[x]=cnt;
	}
	e[way[x][y]].cap+=z;
}

void sap_relabel(int x, int rev, int flow) {
	int i;
	for (dis[x]=n, i=ce[x]=hd[x]; i; i=e[i].nxt) 
		if (e[i].cap) dis[x]=getmin(dis[x], dis[e[i].des]+1);
	if (flow&&rev) dis[x]=getmin(dis[x], dis[e[rev].des]+1);
}

int sap_check(int s) {
	memset(que, 0, sizeof(que));
	for (int i=0; i<n; ++i) if (dis[i]>=0) que[dis[i]]++;
	for (int i=0; i<dis[s]; ++i) if (!que[i]) return 0; return 1;
}

int sap_dfs(int s, int mf, int rev) {
	int tf, f, i;
	if (!dis[s]) return mf;
	for (f=mf, i=ce[s]; f&&i; i=f||!e[i].cap?e[i].nxt:i) 
		if (e[i].cap && dis[e[i].des]==dis[s]-1) {
			tf=sap_dfs(e[i].des, getmin(f, e[i].cap), e[i].rev);
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
	}
	if (!i) sap_relabel(s, rev, mf-f); else ce[s]=i;
	return mf-f;
}

int sap(int s, int t) {
	int f, i, u, head, tail;
	memset(dis, -1, sizeof(dis)); dis[t]=0;
	que[0]=t; head=tail=0;
	while (head<=tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt)
			if (e[e[i].rev].cap && dis[e[i].des]<0) dis[que[++tail]=e[i].des] = dis[u]+1;
	}
	for (i=0; i<n; ++i) if (dis[i]<0) dis[i]=n;
	memcpy(ce, hd, sizeof(hd)); f=0;
	while (sap_check(s)) f+=sap_dfs(s, INF_FLOW, 0); return f;
}

void conduct() {
	int i, s, t, tmp;
	memset(hd, 0, sizeof(hd));
	memset(way, 0, sizeof(way));
	cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &s, &t, &tmp); --s, --t;
		insert(s, t, tmp); insert(t, s, 0);
	}
	printf("%d\n", sap(0, n-1));
}

int main() {
	while (scanf("%d%d", &m, &n)!=EOF) conduct();
	return 0;
}
