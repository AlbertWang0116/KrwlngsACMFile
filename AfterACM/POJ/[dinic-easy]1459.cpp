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
int way[N][N], hd[N], dis[N], que[N], ce[N];
int n, m, ns, nt, cnt;
const int ts=110;
const int te=111;
const int INF_FLOW=2000000000;

int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y, int z) {
	if (!way[x][y]) {
		way[x][y]=++cnt;
		if (way[y][x]) { e[cnt].rev=way[y][x]; e[way[y][x]].rev=cnt; }
		e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].cap=e[cnt].flow=0; hd[x]=cnt;
	}
	e[way[x][y]].cap+=z;
}

int dinic_dfs(int s, int t, int mf) {
	int tf, f, i;
	if (dis[s]==dis[t]) return s==t?mf:0;
	for (f=mf, i=ce[s]; f&&i; i=f||!e[i].cap?e[i].nxt:i)
		if (e[i].cap && dis[e[i].des]==dis[s]+1) {
			tf=dinic_dfs(e[i].des, t, getmin(f, e[i].cap));
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	ce[s]=i;
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
		memcpy(ce, hd, sizeof(hd));
		f+=dinic_dfs(s, t, INF_FLOW);
	}
}

void conduct() {
	int i, st, ed, tmp;
	char a, b, c;
	char str[110];
	memset(hd, 0, sizeof(hd));
	memset(way, 0, sizeof(way));
	for (cnt=i=0; i<m; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d%c%d", &a, &st, &b, &ed, &c, &tmp);
		insert(st, ed, tmp); insert(ed, st, 0);
	}
	for (i=0; i<ns; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d", &a, &st, &b, &tmp);
		insert(ts, st, tmp); insert(st, ts, 0);
	}
	for (i=0; i<nt; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d", &a, &ed, &b, &tmp);
		insert(ed, te, tmp); insert(te, ed, 0);
	}
	printf("%d\n", dinic(ts, te));
}

int main() {
	while (scanf("%d%d%d%d", &n, &ns, &nt, &m)!=EOF) conduct();
	return 0;
}
