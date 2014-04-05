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

struct edge { int src, des, dis, nxt; };
#define M 500010
#define N 21000
int seq[M], a[M], dis[N], pre[N], pre2[N], vst[N], hd[N], ahd[N];
edge e[M];
int n, m, cnt;

struct node {
	int src, dis, eid, tot;
	node(int _src, int _eid, int _dis) {
		src=_src; eid=_eid; dis=_dis; tot=dis+e[eid].dis;
	}
	int operator<(const node &x) const {
		if (tot==x.tot)
			if (src==x.src) return eid<x.eid;
			else return src<x.src;
		else return tot<x.tot;
	}
};

int cmp(const int &i, const int j) { return a[i]<a[j]; }

void insert(int *hd, int i, int j, int k) {
	cnt++; e[cnt].src=i; e[cnt].des=j; e[cnt].dis=k; e[cnt].nxt=hd[i]; hd[i]=cnt;
}

#define next(x, n) ((x)=(x)?(x)-1:(n))
void spfa(int s, int n) {
	int i, head, tail, cnt, u, v;
	memset(dis, 0x7f, sizeof(dis)); memset(pre, -1, sizeof(pre)); memset(vst, 0, sizeof(vst));
	for (head=tail=cnt=dis[u=s]=0; ~cnt--; vst[u=seq[next(head, n)]]--)
		for (i=ahd[u]; i; i=e[i].nxt) if (dis[v=e[i].des]>dis[u]+e[i].dis) {
			dis[v]=dis[u]+e[i].dis; pre[v]=u; pre2[v]=i;
			if (!vst[v]) { vst[v]++; cnt++; seq[next(tail, n)]=v; }
		}
}

void cut(map<node, int> &que, map<node, int>::iterator it) {
	if (!--(it->second)) que.erase(it); cnt--;
}
void add(map<node, int> &que, node item, int k) {
	map<node, int>::iterator it = que.find(item);
	if (it!=que.end()) ++(it->second); else que.insert(pair<node, int>(item, 1));
	if (++cnt > k) cut(que, --(it=que.end()));
}

void conduct() {
	int i, j, k, l, s, t;
	int v, ve, vd, ans;
	scanf("%d%d", &n, &m);
	memset(hd, 0, sizeof(hd)); memset(ahd, 0, sizeof(ahd)); memset(pre2, 0, sizeof(pre2));
	for (cnt=i=0; i<m; ++i) {
		scanf("%d%d%d", &j, &k, &l);
		insert(ahd, k, j, l);
	}
	scanf("%d%d%d", &s, &t, &k);
	memset(seq, 0, sizeof(seq)); if (s==t) k++;
	spfa(t, n);
	for (i=1; i<=m; ++i) { a[i]=dis[e[i].src]+e[i].dis; seq[i]=i; } sort(seq+1, seq+m+1, cmp);
	for (i=m; i; --i) if (pre2[e[seq[i]].des]!=seq[i] && (~pre[e[seq[i]].src] || e[seq[i]].src==t)) 
		insert(hd, e[seq[i]].des, e[seq[i]].src, a[seq[i]]);
	dis[n+1]=dis[s]; insert(hd, n+1, s, dis[s]);
	for (i=1; i<=n; ++i) {
		for (j=hd[i]; j&&e[j].nxt; j=e[j].nxt) {
			if (e[j].dis>e[e[j].nxt].dis) while(1) printf("!\n");
		}
	}
	map<node, int> que;
	que.clear(); cnt=0;
	if (~pre[s] || s==t) add(que, node(n+1, hd[n+1], 0), k);
	for (i=0; i<k && !que.empty(); ++i) {
		map<node, int>::iterator it = que.begin();
		v=(it->first).src; vd=(it->first).dis; ve=(it->first).eid; ans=(it->first).tot;
		cut(que, it);
		if (e[ve].nxt) add(que, node(v, e[ve].nxt, vd), k);
		v=e[ve].des; vd+=e[ve].dis-dis[v]; ve=hd[v];
		if (ve) add(que, node(v, ve, vd), k);
		while (pre[v]!=-1) {
			vd+=dis[v]-dis[pre[v]]; v=pre[v]; ve=hd[v];
			if (ve) add(que, node(v, ve, vd), k);
		}
	}
	if (i<k) printf("-1\n");
	else printf("%d\n", ans);
}

int main() {
//	while (scanf("%d%d", &n, &m)!=EOF) conduct();
	conduct();
	return 0;
}
