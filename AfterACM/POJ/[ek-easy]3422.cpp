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

struct edge { int nxt, des, flow, cap, rev, cost; };
#define M 51000
#define N 5100
#define L 51
int grid[L][L];
int hd[N], dis[N], que[N], pre[N], vst[N];
edge e[M];
int n, m, cnt;
const int ss = 5010;
const int tt = 5011;
const int INF_FLOW = 100;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int flow, int cost) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=flow; e[cnt].flow=0;
	e[cnt].rev=cnt+1; e[cnt].cost=cost; hd[x]=cnt;
	++cnt; e[cnt].nxt=hd[y]; e[cnt].des=x; e[cnt].cap=e[cnt].flow=0;
	e[cnt].rev=cnt-1; e[cnt].cost=-cost; hd[y]=cnt;
}

#define next(x, n) ((x)=(x)?(x)-1:(n))
int mcmf(int s, int t, int &cost, int n) {
	int i, u, v, head, tail, f, tf;
	for (f=cost=0; 1; ) {
		memset(dis, -1, sizeof(dis)); memset(vst, 0, sizeof(vst));
		for (head=tail=cnt=dis[u=s]=pre[s]=pre[t]=0; ~cnt--; vst[u=que[next(head, n)]]--)
			for (i=hd[u]; i; i=e[i].nxt) if (e[i].cap && dis[v=e[i].des]<dis[u]+e[i].cost) {
				dis[v]=dis[u]+e[i].cost; pre[v]=e[i].rev;
				if (!vst[v]) { ++vst[v]; ++cnt; que[next(tail, n)]=v; }
			}
		if (!pre[t]) return f;
		for (tf=INF_FLOW, i=t; pre[i]; i=e[pre[i]].des) tf=getmin(tf, e[e[pre[i]].rev].cap);
		for (f+=tf, i=t; pre[i]; i=e[pre[i]].des) {
			v=e[pre[i]].rev; e[v].cap-=tf; e[v].flow+=tf; cost+=tf*e[v].cost;
			e[e[v].rev].cap+=tf; e[e[v].rev].flow-=tf;
		}
	}
}

void conduct() {
	int i, j, ans;
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) scanf("%d", &grid[i][j]);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<n-1; ++j) insert((n+i)*n+j, i*n+j+1, m, 0);
	for (i=0; i<n-1; ++i) for (j=0; j<n; ++j) insert((n+i)*n+j, (i+1)*n+j, m, 0);
	insert(ss, 0, m, 0); insert(2*n*n-1, tt, m, 0);
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) { insert(i*n+j, (n+i)*n+j, 1, grid[i][j]); insert(i*n+j, (n+i)*n+j, m, 0); }
	mcmf(ss, tt, ans, n*n+2);
	printf("%d\n", ans);
}

int main() {
	conduct();
	return 0;
}
