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

struct edge { int nxt, des, cap, flow, rev, dis; };
#define N 220
#define M 51000
int cm[N], rm[N], ch[N], rh[N];
int hd[N], dis[N], que[N], pre[N], vst[N], pdt[N];
edge e[M];
int n, m, cnt;
const int ss = 210;
const int tt = 211;
const int INF_FLOW = 1100;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int cap, int cost) {
	cnt++; e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=cap; e[cnt].flow=0;
	e[cnt].rev=cnt+1; e[cnt].dis=cost; hd[x]=cnt;
	cnt++; e[cnt].nxt=hd[y]; e[cnt].des=x; e[cnt].cap=e[cnt].flow=0;
	e[cnt].rev=cnt-1; e[cnt].dis=-cost; hd[y]=cnt;
}

#define next(x, y) ((x)=(x)==(y)-1?0:(x)+1)
int spfa(int s, int *hd, edge *e, int n) {
	int i, cnt, head, tail, u, v;
	memset(dis, 0x7f, sizeof(dis)); memset(vst, 0, sizeof(vst)); memset(pre, -1, sizeof(pre));
	for (dis[u=s]=pre[s]=head=tail=cnt=0; ~cnt--&&pre[u]<n; vst[u=que[next(head, n)]]--)
		for (i=hd[u]; i; i=e[i].nxt) if (e[i].cap && dis[v=e[i].des]>dis[u]+e[i].dis) {
			dis[v]=dis[u]+e[i].dis; pre[v]=pre[u]+1; pdt[v]=e[i].rev;
			if (!vst[v]) { vst[v]++; cnt++; que[next(tail, n)]=v; }
		}
	return ~++cnt;
}

int dinic_cost(int s, int t, int mx, int &cost) {
	int f, tf, i, j;
	for (f=cost=0; 1; ) {
		int tmp = spfa(s, hd, e, mx+2);
		if (pre[t]<0) return f;
		for (i=t, tf=INF_FLOW; i!=s; i=e[pdt[i]].des) tf=getmin(tf, e[e[pdt[i]].rev].cap);
		for (i=t; i!=s; i=e[pdt[i]].des) {
			j=e[pdt[i]].rev; e[j].cap-=tf; e[j].flow+=tf; e[e[j].rev].cap+=tf;
			e[e[j].rev].flow-=tf; cost+=tf*e[j].dis;
		}
	}
}

void conduct() {
	int i, j, nm, nh, ans;
	char str[256];
	for (nm=nh=i=0; i<n; ++i) {
		scanf("%s", str);
		for (j=0; j<m; ++j)
			if (str[j]=='m') { rm[nm]=i; cm[nm]=j; nm++; }
			else if (str[j]=='H') { rh[nh]=i; ch[nh]=j; nh++; }
	} n=nm;
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) { insert(ss, i, 1, 0); insert(n+i, tt, 1, 0); }
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) 
		insert(i, n+j, 1, abs(rm[i]-rh[j])+abs(cm[i]-ch[j]));
	dinic_cost(ss, tt, 2*n, ans);
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && (n||m)) conduct();
	return 0;
}
