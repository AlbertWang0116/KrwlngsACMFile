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
#define N 250
#define M 21000
edge e[M];
int way[N][N], dist[N][N], hd[N], dis[N], que[N];
int n, m, cnt;
const int ss = 240;
const int tt = 241;
const int INF_FLOW = 1000;

inline int getmin(int x, int y) { return x<y?x:y; }
inline int getmax(int x, int y) { return x>y?x:y; }

void insert(int x, int y, int z) {
	if (!way[x][y]) {
		way[x][y]=++cnt;
		if (way[y][x]) { e[cnt].rev=way[y][x]; e[way[y][x]].rev=cnt; }
		e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=e[cnt].flow=0; hd[x]=cnt;
	}
	e[way[x][y]].cap+=z;
}

int dinic_dfs(int s, int t, int mf) {
	int f, tf, i;
	if (dis[s]==dis[t]) return s==t?mf:0;
	for (i=hd[s], f=mf; f&&i; i=e[i].nxt) 
		if (e[i].cap && dis[e[i].des]==dis[s]+1) {
			tf=dinic_dfs(e[i].des, t, getmin(f, e[i].cap));
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
	}
	return mf-f;
}

int dinic(int s, int t) {
	int i, f, u, head, tail;
	for (f=0; 1; ) {
		memset(dis, -1, sizeof(dis)); dis[s]=0;
		que[0]=s; head=tail=0;
		while (head<=tail) {
			u=que[head++];
			for (i=hd[u]; i; i=e[i].nxt)
				if (e[i].cap && dis[e[i].des]<0) dis[que[++tail]=e[i].des] = dis[u]+1;
		}
		if (dis[t]<0) return f;
		f+=dinic_dfs(s, t, INF_FLOW);
	}
}

void conduct() {
	int lst, mst, mid, tmp, i, j, k;
	scanf("%d%d%d", &n, &m, &tmp);
	n+=m;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) {
		scanf("%d", &dist[i][j]);
		if (!dist[i][j]) dist[i][j]=100000;
	}
	for (k=0; k<n; ++k)
		for (i=0; i<n; ++i) for (j=0; j<n; ++j)
			if (i!=j && i!=k && j!=k) dist[i][j]=getmin(dist[i][j], dist[i][k]+dist[k][j]);
	for (mst=i=0; i<n; ++i) for (j=0; j<i; ++j) mst=getmax(mst, dist[i][j]); lst=0;
	while (lst<mst) {
		mid=(lst+mst)>>1;
		cnt=0;
		memset(hd, 0, sizeof(hd));
		memset(way, 0, sizeof(way));
		for (i=0; i<n-m; ++i) { insert(ss, i, tmp); insert(i, ss, 0); }
		for (i=n-m; i<n; ++i) { insert(i, tt, 1); insert(tt, i, 0); }
		for (i=0; i<n-m; ++i) for (j=n-m; j<n; ++j) if (dist[i][j]<=mid) {
			insert(i, j, 1); insert(j, i, 0);
		}
		if (dinic(ss, tt)==m) mst=mid;
		else lst=mid+1;
	}
	printf("%d\n", lst);
}

int main() {
	conduct();
	return 0;
}
