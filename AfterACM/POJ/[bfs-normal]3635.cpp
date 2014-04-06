#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;

struct edge { int nxt, des, len; };
#define M 51000
#define N 2100
#define C 200
edge e[M];
int dis[N][C], vst[N][C], hd[N];
int seq[M], st[M], ed[M], cost[M], val[N];
int n, m, cnt;

int cmp(const int &i, const int &j) { return cost[i]<cost[j]; }

struct node {
	int v, cap, cost;
	node(int _v, int _cap) { v=_v; cap=_cap; cost=dis[v][cap]; }
	int operator<(const node &item) const {
		if (cost==item.cost)
			if (v==item.v) return cap>item.cap;
			else return v>item.v;
		else return cost>item.cost;
	}
};

void insert(int i, int j, int k) {
	++cnt; e[cnt].des=j; e[cnt].len=k; e[cnt].nxt=hd[i]; hd[i]=cnt; 
}

void dfs(int u1, int u2, int cap, int len, priority_queue<node> &que) {
	if (vst[u1][u2]) return; vst[u1][u2]=1; dis[u1][u2]=len;
	for (int i=hd[u1]; i&&u2>=e[i].len; i=e[i].nxt) dfs(e[i].des, u2-e[i].len, cap, len, que);
	if (u2<cap) { dis[u1][u2+1]=dis[u1][u2]+val[u1]; que.push(node(u1, u2+1)); }
}

int dijkstra(int s, int t, int cap) {
	memset(dis, 0x7f, sizeof(dis)); memset(vst, 0, sizeof(vst)); dis[s][0]=0; 
	priority_queue<node> que; que.push(node(s, 0));
	while (!que.empty()) {
		node it = que.top(); que.pop();
		dfs(it.v, it.cap, cap, dis[it.v][it.cap], que);
		if (vst[t][0]) return 1;
	}
	return 0;
}

void conduct() {
	int i, q, c, s, t;
	scanf("%d%d", &n, &m);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) scanf("%d", &val[i]);
	for (i=0; i<m; ++i) scanf("%d%d%d", &st[i], &ed[i], &cost[i]);
	for (i=0; i<m; ++i) seq[i]=i; sort(seq, seq+m, cmp);
	for (i=m-1; ~i; --i) {
		insert(st[seq[i]], ed[seq[i]], cost[seq[i]]);
		insert(ed[seq[i]], st[seq[i]], cost[seq[i]]);
	}
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d%d", &c, &s, &t);
		if (dijkstra(s, t, c)) printf("%d\n", dis[t][0]);
		else printf("impossible\n");
	}
}

int main() {
	conduct();
	return 0;
}
