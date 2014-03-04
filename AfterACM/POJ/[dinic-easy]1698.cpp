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
#define N 210
#define M 6010
edge e[M];
int way[N][N], hd[N], dis[N], que[N];
int seq[N], flag[N], d[N], w[N];
int n, m, cnt;
const int ed = 200;
const int INF_FLOW = 2010;

int getmin(int x, int y) { return x<y?x:y; }
int cmp(const int &i, const int &j) { return w[i]<w[j]; }

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
	for (f=mf, i=hd[s]; f&&i; i=e[i].nxt)
		if (e[i].cap && dis[e[i].des]==dis[s]+1) {
			tf=dinic_dfs(e[i].des, t, getmin(f, e[i].cap));
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	return mf-f;
}

int dinic(int s, int t) {
	int f, i, u, head, tail;
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
	int i, j, k, cur, pre, tag, id;
	scanf("%d", &n); cnt=0;
	memset(hd, 0, sizeof(hd));
	memset(way, 0, sizeof(way));
	for (i=0; i<n; ++i) {
		flag[i]=0;
		for (j=0; j<7; ++j) {
			scanf("%d", &tag);
			if (tag) flag[i]+=(1<<j);
		}
		scanf("%d%d", &d[i], &w[i]);
	}
	for (i=0; i<n; ++i) seq[i]=i; sort(seq, seq+n, cmp);
	for (i=1; i<=n; ++i) { insert(0, i, d[i-1]); insert(i, 0, 0); }
	for (cur=id=i=0; i<n; ++i) {
		if (w[seq[i]]>cur) { 
			pre=cur; cur=w[seq[i]]; ++id; 
			for (j=0; j<7; ++j) { insert(n+(id-1)*7+j+1, ed, cur-pre); insert(ed, n+(id-1)*7+j+1, 0); }
		}
		for (j=0; j<7; ++j) if (flag[seq[i]]&(1<<j))
			for (k=0; k<id; ++k) { insert(seq[i]+1, n+k*7+j+1, d[seq[i]]); insert(n+k*7+j+1, seq[i]+1, 0); }
	}
	for (j=i=0; i<n; ++i) j+=d[i];
	if (j==dinic(0, ed)) printf("Yes\n");
	else printf("No\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
