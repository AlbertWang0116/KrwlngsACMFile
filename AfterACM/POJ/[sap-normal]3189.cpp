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

struct edge { int nxt, des, flow, cap, rev; };
#define N 1100
#define M 51000
#define L 30
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N];
int	v[N][L], w[L];
int n, m, cnt;
const int ss=1090;
const int tt=1091;
const int INF_FLOW=10000;

inline int getmin(int x, int y) { return x<y?x:y; } 

void insert(int x, int y, int z) {
	if (!way[x][y]) {
		way[x][y]=++cnt;
		if (way[y][x]) { e[cnt].rev=way[y][x]; e[way[y][x]].rev=cnt; }
		e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=e[cnt].flow=0; hd[x]=cnt;
	}
	e[way[x][y]].cap+=z;
}

void sap_relabel(int s, int rev, int flow, int i=0) {
	for (i=ce[s]=hd[s], dis[s]=N-1; i; i=e[i].nxt)
		if (e[i].cap) dis[s]=getmin(dis[s], dis[e[i].des]+1);
	if (flow&&rev) dis[s]=getmin(dis[s], dis[e[rev].des]+1);
}

int sap_dfs(int s, int mf, int rev) {
	int i, tf, f;
	if (!dis[s]) return mf;
	for (i=ce[s], f=mf; f&&i; i=f||!e[i].cap?e[i].nxt:i) 
		if (e[i].cap && dis[e[i].des]==dis[s]-1) {
			tf=sap_dfs(e[i].des, getmin(f, e[i].cap), e[i].rev);
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	if (i) ce[s]=i; else sap_relabel(s, rev, mf-f);
	return mf-f;
}

int sap_check(int s, int i=0) {
	memset(que, 0, sizeof(que));
	for (i=0; i<N; ++i) que[dis[i]]++;
	for (i=0; i<dis[s]; ++i) if (!que[i]) return 0; return 1;
}

int sap(int s, int t) {
	int i, f, u, head, tail;
	memset(dis, -1, sizeof(dis)); dis[t]=0;
	que[0]=t; head=tail=0;
	while (head<=tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt)
			if (e[e[i].rev].cap && dis[e[i].des]<0) dis[que[++tail]=e[i].des] = dis[u]+1;
	}
	for (i=0; i<N; ++i) if (dis[i]<0) dis[i]=N-1;
	memcpy(ce, hd, sizeof(hd)); f=0;
	while (sap_check(s)) f+=sap_dfs(s, INF_FLOW, 0); return f;
}

void conduct() {
	int i, j, k, l, ans;
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) for (j=0; j<m; ++j) { scanf("%d", &v[i][j]); --v[i][j]; }
	for (i=0; i<m; ++i) scanf("%d", &w[i]);
	for (ans=m, k=l=0; k<=l && l<m; ) {
		memset(way, 0, sizeof(way)); memset(hd, 0, sizeof(hd)); cnt=0;
		for (i=0; i<n; ++i) { insert(ss, i, 1); insert(i, ss, 0); }
		for (i=0; i<m; ++i) { insert(n+i, tt, w[i]); insert(tt, n+i, 0); }
		for (i=0; i<n; ++i) for (j=k; j<=l; ++j) { insert(i, n+v[i][j], 1); insert(n+v[i][j], i, 0); }
		if (sap(ss, tt)==n) { ans=getmin(ans, l-k+1); ++k; }
		else ++l;
	}
	printf("%d\n", ans);
}

int main() {
	conduct();
	return 0;
}
