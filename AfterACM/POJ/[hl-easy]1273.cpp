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
#define N 210
#define M 610
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N], cf[N], blk[2*N], pst[N];
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

void hl_push(int u, int v, int i, int tf) {
	cf[u]-=tf; e[i].cap-=tf; e[i].flow+=tf;
	cf[v]+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf;
}

void hl_relabel(int u, int &v, int &lv, int ml) {
	int i, j, k;
	for (i=ce[u]=hd[u], dis[u]=2*N; i; i=e[i].nxt)
		if (e[i].cap) dis[u]=getmin(dis[u], dis[e[i].des]+1);
	if (~v) pst[v]=pst[u]; else blk[lv]=pst[u];
	pst[u]=blk[dis[u]]; blk[dis[u]]=u;
	if (!blk[lv] && dis[u]<ml)
		for (i=lv+1; i<ml; ++i) for (j=blk[i], k=pst[j]; j; blk[i]=j=k, k=pst[k]) {
			dis[j]=ml+1; pst[j]=blk[dis[j]]; blk[dis[j]]=j;
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
			if (e[i].cap && dis[e[i].des]==dis[u]-1) hl_push(u, e[i].des, i, getmin(cf[u], e[i].cap));
		if (!cf[u]) ce[u]=i; else hl_relabel(u, v, lv, mx+2);
	}
	return cf[t];
}

void conduct() {
	int i, s, t, tmp;
	memset(way, 0, sizeof(way)); memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &s, &t, &tmp);
		insert(s, t, tmp); insert(t, s, 0);
	}
	printf("%d\n", highest_relabel(1, n, n));
}

int main() {
	while (scanf("%d%d", &m, &n)!=EOF) conduct();
	return 0;
}
