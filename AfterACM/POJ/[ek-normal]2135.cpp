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

struct edge { int nxt, des, flow, cap, cost, rev; };
#define M 51000
#define N 1100
int hd[N], dis[N], que[N], vst[N], pre[N];
edge e[M];
int n, m, cnt;
const int ss = 1010;
const int tt = 1011;
const int INF_FLOW = 10;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int flow, int cost) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=flow; e[cnt].flow=0;
	e[cnt].rev=cnt+1; e[cnt].cost=cost; hd[x]=cnt;
	++cnt; e[cnt].nxt=hd[y]; e[cnt].des=x; e[cnt].cap=e[cnt].flow=0;
	e[cnt].rev=cnt-1; e[cnt].cost=-cost; hd[y]=cnt;
}

#define next(x, n) ((x)=(x)+1==(n)?0:(x)+1)
int mcmf(int s, int t, int &cost, int n) {
	int i, u, v, head, tail, f, tf;
	for (f=cost=0; 1; ) {
		memset(dis, 0x7f, sizeof(dis)); memset(vst, 0, sizeof(vst));
		for (head=tail=cnt=dis[u=s]=pre[s]=pre[t]=0; ~cnt--; vst[u=que[next(head, n)]]--)
			for (i=hd[u]; i; i=e[i].nxt) if (e[i].cap && dis[v=e[i].des]>dis[u]+e[i].cost) {
				dis[v]=dis[u]+e[i].cost; pre[v]=e[i].rev;
				if (!vst[v]) { vst[v]++; cnt++; que[next(tail, n)]=v; }
			}
		if (!pre[t]) return f;
		for (tf=INF_FLOW, i=t; pre[i]; i=e[pre[i]].des) tf=getmin(tf, e[e[pre[i]].rev].cap);
		for (i=t; pre[i]; i=e[pre[i]].des) {
			v=e[pre[i]].rev; e[v].cap-=tf; e[v].flow+=tf; cost+=tf*e[v].cost;
			e[e[v].rev].cap+=tf; e[e[v].rev].flow-=tf;
		} f+=tf;
	}
}

void conduct() {
	int i, j, k, l, ans;
	scanf("%d%d", &n, &m);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &j, &k, &l);
		insert(j, k, 1, l); insert(k, j, 1, l);
	}
	insert(ss, 1, 2, 0); insert(n, tt, 2, 0);
	mcmf(ss, tt, ans, n+2);
	printf("%d\n", ans);
}

int main() {
	conduct();
	return 0;
}
