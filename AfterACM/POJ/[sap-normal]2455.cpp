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
#define N 210
#define M 50010
edge e[M];
int way[N][N], hd[N], ce[N], dis[N], que[N];
int u[M], v[M], len[M], seq[M];
int n, m, cnt;
const int INF_FLOW = 100010;

inline int getmin(int x, int y) { return x<y?x:y; }
int cmp(const int &i, const int &j) { return len[i]<len[j]; }

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
	int i, f, tf;
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
	int i, lf, lst, mst, mid;
	scanf("%d%d%d", &n, &m, &lf);
	for (i=0; i<m; ++i) scanf("%d%d%d", &u[i], &v[i], &len[i]);
	for (i=0; i<m; ++i) seq[i]=i; sort(seq, seq+m, cmp);
	lst=0; mst=m-1;
	while (lst<mst) {
		mid=(lst+mst)>>1;
		memset(hd, 0, sizeof(hd)); memset(way, 0, sizeof(way)); cnt=0;
		for (i=0; i<=mid; ++i) { insert(u[seq[i]], v[seq[i]], 1); insert(v[seq[i]], u[seq[i]], 1); }
		if (sap(1, n)>=lf) mst=mid; else lst=mid+1;
	}
	printf("%d\n", len[seq[lst]]);
}

int main() {
	conduct();
	return 0;
}
