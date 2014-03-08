#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<map>
using namespace std;

struct edge { int nxt, des, cap, flow, rev; };
#define N 220
#define M 51000
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N], pst[N], blk[N], cf[N];
double x[N], y[N];
int p[N], q[N];
int n, m, cnt;
const int ss = 210;
const int tt = 211;
const int INF_FLOW = 11000;
const double eps = 1e-6;
#define SQR(x) ((x)*(x))

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
	int i, j, k;
	double d;
	scanf("%d%lf", &n, &d);
	memset(way, 0, sizeof(way)); memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) scanf("%lf%lf%d%d", &x[i], &y[i], &p[i], &q[i]);
	for (k=i=0; i<n; ++i) { insert(ss, i, p[i]); insert(i, ss, 0); k+=p[i]; }
	for (i=0; i<n; ++i) { insert(i, n+i, q[i]); insert(n+i, i, 0); }
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) if (i!=j)
		if (sqrt(SQR(x[i]-x[j])+SQR(y[i]-y[j]))-d<eps) {
			insert(n+i, j, k); insert(j, n+i, 0);
		}
	for (i=j=0; i<n; ++i) {
		insert(i, tt, k); insert(tt, i, 0);
		if (highest_relabel(ss, tt, 2*n)==k) { ++j; printf("%d ", i); }
		for (int l=1; l<=cnt; ++l) { e[l].cap+=e[l].flow; e[l].flow=0; }
		insert(i, tt, -k);
	}
	if (!j) printf("-1\n"); else printf("\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
