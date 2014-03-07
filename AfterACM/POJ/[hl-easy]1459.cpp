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
int way[N][N], hd[N], ce[N], dis[N], que[N], cf[N], blk[2*N], pst[N];
edge e[M];
int n, m, cnt, ns, nt;
const int ss = 110;
const int tt = 111;
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

void hl_push(int u, int v, int i, int flow) {
	cf[u]-=flow; e[i].cap-=flow; e[i].flow+=flow;
	cf[v]+=flow; e[e[i].rev].cap+=flow; e[e[i].rev].flow-=flow;
}

void hl_relabel(int u, int &v, int &lv, int mx) {
	int i, j, k;
	for (i=ce[u]=hd[u], dis[u]=2*N; i; i=e[i].nxt)
		if (e[i].cap) dis[u]=getmin(dis[u], dis[e[i].des]+1);
	if (~v) pst[v]=pst[u]; else blk[lv]=pst[u];
	pst[u]=blk[dis[u]]; blk[dis[u]]=u;
	if (!~blk[lv] && dis[u]<mx)
		for (i=lv+1; i<mx; ++i) for (j=blk[i], k=pst[j]; ~j; blk[i]=j=k, k=~k?pst[k]:0) {
			dis[j]=mx+1; pst[j]=blk[dis[j]]; blk[dis[j]]=j;
		}
	lv=dis[u]; v=-1;
}

int highest_relabel(int s, int t, int mx) {
	int i, u, v, head, tail, lv;
	memset(dis, -1, sizeof(dis)); dis[t]=0;
	que[0]=t; head=tail=0;
	while (head<=tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt)
			if (e[e[i].rev].cap && dis[e[i].des]<0) dis[que[++tail]=e[i].des] = dis[u]+1;
	}
	for (i=0; i<N; ++i) if (dis[i]<0) dis[i]=mx+3; dis[s]=mx+2;
	memcpy(ce, hd, sizeof(hd)); memset(blk, -1, sizeof(blk));
	for (i=0; i<mx; ++i) if (i!=s&&i!=t) { pst[i]=blk[dis[i]]; blk[dis[i]]=i; }
	memset(cf, 0, sizeof(cf)); cf[s]=INF_FLOW;
	for (i=hd[s]; i; i=e[i].nxt) hl_push(s, e[i].des, i, e[i].cap);
	for (lv=mx+3, u=blk[lv], v=-1; lv; v=u, u=~u?pst[u]:blk[--lv]) while (~u&&cf[u]) {
		for (i=ce[u]; cf[u]&&i; i=cf[u]||!e[i].cap?e[i].nxt:i)
			if (e[i].cap && dis[e[i].des]==dis[u]-1) hl_push(u, e[i].des, i, getmin(e[i].cap, cf[u]));
		if (cf[u]) hl_relabel(u, v, lv, mx+2); else ce[u]=i;
	}
	return cf[t];
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
	printf("%d\n", highest_relabel(ss, tt, n));
}

int main() {
	while (scanf("%d%d%d%d", &n, &ns, &nt, &m)!=EOF) conduct();
	return 0;
}
