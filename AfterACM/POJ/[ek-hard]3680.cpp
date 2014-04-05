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

struct edge { int nxt, des, cap, flow, cost, rev; };
#define N 420
#define M 2010
int x[N], y[N];
int hd[N], dis[N], que[N], vst[N], pre[N];
int n, m, cnt;
edge e[M];
const int ss = 410;
const int tt = 411;
const int INF_FLOW = 1000;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int flow, int cost) {
	cnt++; e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=flow; e[cnt].flow=0;
	e[cnt].rev=cnt+1; e[cnt].cost=cost; hd[x]=cnt;
	cnt++; e[cnt].nxt=hd[y]; e[cnt].des=x; e[cnt].cap=e[cnt].flow=0;
	e[cnt].rev=cnt-1; e[cnt].cost=-cost; hd[y]=cnt;
}

#define next(x, n) ((x)=(x)==(n)-1?0:(x)+1)
int mcmf(int s, int t, int &cost, int n) {
	int f, tf, i, u, v, head, tail;
	for (f=cost=0; 1; ) {
		memset(dis, -1, sizeof(dis)); memset(vst, 0, sizeof(vst));
		for (head=tail=cnt=dis[u=s]=pre[s]=pre[t]=0; ~cnt--; vst[u=que[next(head, n)]]--) 
			for (i=hd[u]; i; i=e[i].nxt) if (e[i].cap && dis[v=e[i].des]<dis[u]+e[i].cost) {
				dis[v]=dis[u]+e[i].cost; pre[v]=e[i].rev;
				if (!vst[v]) { vst[v]++; cnt++; que[next(tail, n)]=v; } 
			}
		if (!pre[t]) return f;
		for (tf=INF_FLOW, i=t; pre[i]; i=e[pre[i]].des) tf=getmin(tf, e[e[pre[i]].rev].cap);
		for (i=t; pre[i]; i=e[pre[i]].des) {
			u=e[pre[i]].rev; e[u].cap-=tf; e[u].flow+=tf; cost+=tf*e[u].cost;
			e[e[u].rev].cap+=tf; e[e[u].rev].flow-=tf;
		} f+=tf;
	}
}

int cmp(const int &i, const int &j) { return x[i]<x[j]; }

void conduct() {
	int i, j, k, ans;
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) scanf("%d%d%d", &x[2*i], &x[2*i+1], &y[2*i]); n*=2;
	for (i=0; i<n; ++i) que[i]=i; sort(que, que+n, cmp);
	for (i=j=0; i<n; ++j) for (k=x[que[i]]; i<n&&x[que[i]]==k; ++i) x[que[i]]=j;
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<j-1; ++i) insert(i, i+1, m, 0);
	for (i=0; i<n; i+=2) insert(x[i], x[i+1], 1, y[i]);
	insert(ss, 0, m, 0); insert(j-1, tt, m, 0); n=j;
	mcmf(ss, tt, ans, n+2);
	printf("%d\n", ans);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
