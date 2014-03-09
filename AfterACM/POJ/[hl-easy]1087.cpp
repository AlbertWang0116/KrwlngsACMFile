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

struct edge { int nxt, des, cap, flow, rev; };
#define N 220
#define M 51000
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N], cf[N], blk[2*N], pst[N];
int x[N], y[N], rd[2*N][2*N];
char tp[2*N][30];
int n, m, cnt;
const int ss = 210;
const int tt = 211;
const int INF_FLOW = 1000;

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

int hl_relabel(int u, int &v, int &lv, int mx) {
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
	memset(dis, -1, sizeof(dis)); memcpy(ce, hd, sizeof(hd)); dis[t]=0;
	que[0]=t; head=tail=0;
	while (head<=tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt) 
			if (e[e[i].rev].cap && dis[e[i].des]<0) dis[que[++tail]=e[i].des] = dis[u]+1;
	}
	for (i=0; i<N; ++i) if (dis[i]<0) dis[i]=mx+3; dis[s]=mx+2;
	memset(blk, -1, sizeof(blk));
	for (i=0; i<mx; ++i) if (i!=s&&i!=t) { pst[i]=blk[dis[i]]; blk[dis[i]]=i; }
	memset(cf, 0, sizeof(cf)); cf[s]=INF_FLOW;
	for (i=hd[s]; i; i=e[i].nxt) hl_push(s, e[i].des, i, e[i].cap);
	for (lv=mx+3, u=blk[lv], v=-1; lv; v=u, u=~u?pst[u]:blk[--lv]) while (~u&&cf[u]) {
		for (i=ce[u]; i&&cf[u]; i=cf[u]||!e[i].cap?e[i].nxt:i)
			if (e[i].cap && dis[e[i].des]==dis[u]-1) hl_push(u, e[i].des, i, getmin(cf[u], e[i].cap));
		if (cf[u]) hl_relabel(u, v, lv, mx+2); else ce[u]=i;
	}
	return cf[t];
}

void conduct() {
	int i, j, k, p, tmp;
	char str[30];
	scanf("%d", &m); p=0;
	for (i=0; i<m; ++i) {
		scanf("%s", str);
		for (j=0; j<p; ++j) if (!strcmp(tp[j], str)) break;
		if (j==p) strcpy(tp[p++], str); y[i]=j;
	}
	scanf("%d", &n);
	for (i=0; i<n; ++i) {
		scanf("%s", str);
		scanf("%s", str);
		for (j=0; j<p; ++j) if (!strcmp(tp[j], str)) break;
		if (j==p) strcpy(tp[p++], str); x[i]=j;
	}
	scanf("%d", &tmp); memset(rd, 0, sizeof(rd));
	for (i=0; i<p; ++i) rd[i][i]=1;
	while (tmp--) {
		scanf("%s", str);
		for (j=0; j<p; ++j) if (!strcmp(tp[j], str)) break;
		if (j==p) strcpy(tp[p++], str);
		scanf("%s", str);
		for (k=0; k<p; ++k) if (!strcmp(tp[k], str)) break;
		if (k==p) strcpy(tp[p++], str);
		rd[j][k]=1;
	}
	for (k=0; k<p; ++k) for (i=0; i<p; ++i) for (j=0; j<p; ++j)
		if (rd[i][k]&&rd[k][j]) rd[i][j]=1;
	memset(way, 0, sizeof(way)); memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<m; ++j) if (rd[x[i]][y[j]]) {
		insert(i, n+j, 1); insert(n+j, i, 0);
	}
	for (i=0; i<n; ++i) {
		insert(ss, i, 1); insert(i, ss, 0);
	}
	for (i=0; i<m; ++i) {
		insert(n+i, tt, 1); insert(tt, n+i, 0);
	}
	printf("%d\n", n-highest_relabel(ss, tt, n+m));
}

int main() {
	conduct();
	return 0;
}
