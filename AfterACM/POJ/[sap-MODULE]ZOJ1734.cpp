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

struct edge { int nxt, des, cap, flow, rev; };
#define N 120
#define M 51000
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N], blk[N], pst[N], pre[N];
int n, m, cnt, ns, nt, flag;
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

void sap_blk_insert(int s, int lv) { pre[s]=-1; pst[s]=blk[lv]; if (~blk[lv]) pre[blk[lv]]=s; blk[lv]=s; }

void sap_relabel(int s, int rev, int flow) {
	int i, lv=dis[s];
	for (i=ce[s]=hd[s], dis[s]=N-1; i; i=e[i].nxt)
		if (e[i].cap) dis[s]=getmin(dis[s], dis[e[i].des]+1);
	if (flow&&rev) dis[s]=getmin(dis[s], dis[e[rev].des]+1);
	if (~pre[s]) pst[pre[s]]=pst[s]; else blk[lv]=pst[s];
	if (~pst[s]) pre[pst[s]]=pre[s]; 
	sap_blk_insert(s, dis[s]); flag=~blk[lv]?flag:0;
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

int sap(int s, int t) {
	int i, u, f, head, tail;
	memset(dis, -1, sizeof(dis)); memcpy(ce, hd, sizeof(hd)); dis[t]=0;
	que[0]=t; head=tail=0;
	while (head<=tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt)
			if (e[e[i].rev].cap && dis[e[i].des]<0) dis[que[++tail]=e[i].des] = dis[u]+1;
	}
	if (dis[s]<0) return 0;
	for (i=0; i<N; ++i) if (dis[i]<0) dis[i]=N-1;
	memset(blk, -1, sizeof(blk)); f=0; flag=1;
	for (i=0; i<N; ++i) sap_blk_insert(i, dis[i]);
	while (flag) f+=sap_dfs(s, INF_FLOW, 0); return f;
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
	printf("%d\n", sap(ss, tt));
}

int main() {
	while (scanf("%d%d%d%d", &n, &ns, &nt, &m)!=EOF) conduct();
	return 0;
}
