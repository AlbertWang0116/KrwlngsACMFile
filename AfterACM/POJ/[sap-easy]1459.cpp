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
#define M 21000
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N];
int n, m, cnt, ns, nt;
const int ss=110;
const int tt=111;
const int INF_FLOW=LONG_MAX;

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
	for (dis[s]=N-1, i=ce[s]=hd[s]; i; i=e[i].nxt)
		if (e[i].cap) dis[s]=getmin(dis[s], dis[e[i].des]+1);
	if (flow&&rev) dis[s]=getmin(dis[s], dis[e[rev].des]+1);
}

int sap_dfs(int s, int mf, int rev) {
	int i, f, tf;
	if (!dis[s]) return mf;
	for (f=mf, i=ce[s]; f&&i; i=f||!e[i].cap?e[i].nxt:i)
		if (e[i].cap && dis[e[i].des]==dis[s]-1) {
			tf=sap_dfs(e[i].des, getmin(f, e[i].cap), e[i].rev);
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	if (!i) sap_relabel(s, rev, mf-f); else ce[s]=i;
	return mf-f;
}

int sap_check(int s, int i=0) {
	memset(que, 0, sizeof(que));
	for (i=0; i<N; ++i) que[dis[i]]++;
	for (i=0; i<dis[s]; ++i) if (!dis[i]) return 0; return 1;
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
	for (i=0; i<N; ++i) if (dis[i]<0) dis[i]=N-1;
	memcpy(ce, hd, sizeof(hd)); f=0; 
	while (sap_check(s)) f+=sap_dfs(s, INF_FLOW, 0); return f;
}

void conduct() {
	int s, t, tmp, i;
	char a, b, c;
	char str[256];
	memset(hd, 0, sizeof(hd));
	memset(way, 0, sizeof(way));
	cnt=0;
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
