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
#define M 3100
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N];
int in[N], out[N];
int n, m, cnt;
const int INF_FLOW = 100010;
const int ss = 210;
const int tt = 211;

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
	if (rev&&flow) dis[s]=getmin(dis[s], dis[e[rev].des]+1);
}

int sap_dfs(int s, int mf, int rev) {
	int i, tf, f;
	if (!dis[s]) return mf;
	for (i=ce[s], f=mf; f&&i; i=f||!e[i].cap?e[i].nxt:i) 
		if (e[i].cap && dis[e[i].des]==dis[s]-1) {
			tf=sap_dfs(e[i].des, getmin(e[i].cap, f), e[i].rev);
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
	int i, ms, mt, s, t, di;
	scanf("%d%d", &n, &m);
	memset(in, 0, sizeof(in)); memset(out, 0, sizeof(out));
	memset(hd, 0, sizeof(hd)); memset(way, 0, sizeof(way)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &s, &t, &di); s--; t--;
		out[s]++; in[t]++;
		if (!di) {
			insert(s, t, 1); insert(t, s, 0); 
		}
	}
	for (i=0; i<n; ++i) if ((in[i]+out[i])&1) { printf("impossible\n"); return; }
	for (ms=mt=i=0; i<n; ++i) {
		if (in[i]>out[i]) { insert(i, tt, (in[i]-out[i])/2); insert(tt, i, 0); mt+=in[i]-out[i]; }
		if (out[i]>in[i]) { insert(ss, i, (out[i]-in[i])/2); insert(i, ss, 0); ms+=out[i]-in[i]; }
	}
	if (ms!=mt || ms/2!=sap(ss, tt)) printf("impossible\n");
	else printf("possible\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
