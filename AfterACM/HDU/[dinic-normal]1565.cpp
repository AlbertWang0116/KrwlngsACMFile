#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
#include<climits>
using namespace std;

struct edge { int nxt, des, cap, flow, rev; };
#define N 1100
#define M 4100
#define L 30
int hd[N], ce[N], que[N], dis[N];
int a[L][L];
edge e[M];
int n, m, cnt;
const int dr[] = { 0, 0, 1, -1 };
const int dc[] = { 1, -1, 0, 0 };
const int ss = 1000;
const int tt = 1010;
const int INF_FLOW = LONG_MAX;

inline int getmin(int x, int y) { return x<y?x:y; }
int valid(int tr, int tc) { return tr>=0 && tr<n && tc>=0 && tc<n; }

void insert(int x, int y, int z) {
	++cnt; e[cnt].nxt=hd[x]; hd[x]=cnt; e[cnt].des=y;
	e[cnt].cap=z; e[cnt].flow=0; e[cnt].rev=cnt+1;
	++cnt; e[cnt].nxt=hd[y]; hd[y]=cnt; e[cnt].des=x;
	e[cnt].cap=0; e[cnt].flow=0; e[cnt].rev=cnt-1;
}

int dinic_dfs(int x, int t, int mf) {
	int i, f, tf;
	if (dis[x]==dis[t]) return x==t?mf:0;
	for (i=ce[x], f=mf; f&&i; i=f?e[i].nxt:i)
		if (e[i].cap && dis[x]+1==dis[e[i].des]) {
			tf=dinic_dfs(e[i].des, t, getmin(f, e[i].cap));
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	ce[x]=i; return mf-f;
}

int dinic(int s, int t) {
	int head, tail, u, i, f;
	for (f=0; 1; ) {
		memset(dis, -1, sizeof(dis)); memcpy(ce, hd, sizeof(hd));
		for (head=tail=dis[u=s]=0; head<=tail; u=que[head++]) 
			for (i=hd[u]; i; i=e[i].nxt) if (e[i].cap && !~dis[e[i].des]) 
				dis[que[tail++]=e[i].des]=dis[u]+1;
		if (!~dis[t]) return f;
		f+=dinic_dfs(s, t, INF_FLOW);
	}
}

void conduct() {
	int i, j, k, tr, tc;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) scanf("%d", &a[i][j]);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) {
		if ((i+j)&1) insert(i*n+j, tt, a[i][j]);
		else {
			insert(ss, i*n+j, a[i][j]);
			for (k=0; k<4; ++k) {
				tr=i+dr[k]; tc=j+dc[k];
				if (valid(tr, tc)) insert(i*n+j, tr*n+tc, INF_FLOW);
			}
		}
	}
	for (k=i=0; i<n; ++i) for (j=0; j<n; ++j) k+=a[i][j];
	printf("%d\n", k-dinic(ss, tt));
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
