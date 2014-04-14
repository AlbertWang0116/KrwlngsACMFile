//Dijkstra + Heap
//If distance is float, change the 2nd line of dijkstra of initialize of dis.
//The vertice id is from 0 to n-1. If different, just modify the 3rd line of dijkstra.
//The parameter to indicate the distance (can change to long long or double) :
//	struct edge - len
//	global parameter - dis
struct edge { int nxt, des, len; };
int hd[N], dis[N], pre[N], hp[N], ph[N];
edge e[M];
int n;

inline void hpset(int x, int v) { hp[x]=v; ph[v]=x; }
void hpdel(int x, int y=0, int e=0) {
	for (e=hp[hp[0]--], x=y=ph[x], y<<=1; y<=hp[0]; y<<=1) {
		if (y<hp[0]&&dis[hp[y+1]]<dis[hp[y]]) y++;
		if (dis[hp[y]]<dis[e]) { hpset(x, hp[y]); x=y; } else break;
	} hpset(x, e);
}
void hpupd(int x, int y=0, int e=0) {
	for (e=x, x=y=ph[x], y>>=1; y; y>>=1)
		if (dis[hp[y]]>dis[e]) { hpset(x, hp[y]); x=y; } else break;
	hpset(x, e);
}

void dijkstra(int s) {
	int i, u, v;
	memset(dis, 0x7f, sizeof(dis)); memset(pre, -1, sizeof(pre)); dis[s]=0;
	for (i=0; i<n; ++i) hpset(i+1, i); hpset(s+1, 0); hpset(1, s); hp[0]=n;
	for (hpdel(u=hp[1]); hp[0]; hpdel(u=hp[1])) 
		for (i=hd[u]; i; i=e[i].nxt) if (dis[v=e[i].des]>dis[u]+e[i].len) {
			dis[v]=dis[u]+e[i].len; pre[v]=u; hpupd(v);
		}
}

//SPFA to get shortest path, without negative cycle detection.
//If distance is float, modify the 2nd line the dis initilization and 4th line comparison.
//No restrict on vertices' id. n is the number of vertices.
//To get longest (no cycle) path, just modify the 2nd line of dis initialization to 0 and 4th line > to <.
//The parameter to indicate the distance (can change to long long or double) :
//	struct edge - len
//	global parameter - dis
struct edge { int nxt, des, len; };
int hd[N], dis[N], pre[N], vst[N], que[N];
edge e[M];

#define next(x, n) ((x)=(x)?(x)-1:(n))
void spfa(int s, int n) {
	int i, u, v, head, tail, cnt;
	memset(dis, 0x7f, sizeof(dis)); memset(pre, -1, sizeof(pre)); memset(vst, 0, sizeof(vst));
	for (head=tail=dis[u=s]=cnt=0; ~cnt--; vst[u=que[next(head, n)]]--)
		for (i=hd[u]; i; i=e[i].nxt) if (dis[v=e[i].des]>dis[u]+e[i].len) {
			dis[v]=dis[u]+e[i].len; pre[v]=u;
			if (!vst[v]) { vst[v]++; cnt++; que[next(tail, n)]=v; }
		}
}

//SPFA to get shortest path, with negative cycle detection (return -1).
//If distance is float, modify the 2nd line the dis initilization and 4th line comparison.
//No restrict on vertices' id. n is the number of vertices.
//To get longest path (or positive cycle detection), just modify the 2nd line of dis initialization to 0 and 4th line > to <.
//The parameter to indicate the distance (can change to long long or double) :
//	struct edge - len
//	global parameter - dis
struct edge { int nxt, des, len; };
int hd[N], dis[N], pc[N], vst[N], que[N];
edge e[M];

#define next(x, n) ((x)=(x)?(x)-1:(n))
int spfa(int s, int n) {
	int i, u, v, head, tail, cnt;
	memset(dis, 0x7f, sizeof(dis)); memset(vst, 0, sizeof(vst));
	for (head=tail=dis[u=s]=pc[s]=cnt=0; ~cnt--; vst[u=que[next(head, n)]]--)
		for (i=hd[u]; i; i=e[i].nxt) if (dis[v=e[i].des]>dis[u]+e[i].len) {
			dis[v]=dis[u]+e[i].len; pc[v]=pc[u]+1; if (pc[v]>=n) return -1;
			if (!vst[v]) { ++vst[v]; ++cnt; que[next(tail, n)]=v; }
		}
	return 0;
}

//Prim + Set. Return the number of vertices has no path to root.
//If distance is float, 1st & 2nd line (len comparison) of node::operator<, 2nd line (len init) and 6th line (len comparison) of prim must be modified.
//No restrict on vertices' id. n is the number of vertices.
//The parameter to indicate the distance (can change to long long or double) :
//	struct edge - len
//	global prameter - len
struct edge { int nxt, des, len; };
struct node {
	int u, len;
	node(int _u, int _len) { u=_u; len=_len; }
	int operator<(const node &item) const {
		if (len==item.len) return u<item.u;
		else return len<item.len;
	}
};
edge e[M];
int hd[N], len[N], vst[N], pre[N];

int prim(int s, int n) {
	int i, u, v;
	memset(len, 0x7f, sizeof(len)); memset(vst, 0, sizeof(vst)); len[s]=0; pre[s]=s;
	set<node> que; que.clear(); que.insert(node(s, len[s]));
	while (n-- && !que.empty()) {
		u=que.begin()->u; que.erase(que.begin()); vst[u]=1;
		for (i=hd[u]; i; i=e[i].nxt) if (!vst[v=e[i].des] && len[v]>e[i].len) {
			que.erase(node(v, len[v])); len[v]=e[i].len; pre[v]=u; que.insert(node(v, len[v]));
		}
	} return n;
}

//Kruskal + Union Check Set. Return value indicate whether there is a MST.
//If distance is float, the comparison of cmp will be modified.
//No restrict on vertices' id. n is the number of vertices. 
//Edge id is 0~m-1, modify 2nd line to match other index.
//The parameter to indicate the distance (can change to long long or double) :
//	struct edge - len
struct edge { int src, des, len; };
edge e[M];
int seq[M], use[M], root[N];

int get_root(int x) { if (root[x]==x) return x; else return root[x]=get_root(root[x]); }
int merge_root(int x, int y) { root[get_root(x)]=get_root(y); }

int cmp(const int &i, const int &j) { return e[i].len<e[j].len; }
int kruskal(int n, int m) {
	int i, j, tmp, ret;
	for (i=0; i<m; ++i) seq[i]=i; sort(seq, seq+m, cmp); memset(use, 0, sizeof(use));
	for (i=0; i<N; ++i) root[i]=i;
	for (i=j=0; i<n-1; ++i) {
		for (; j<m; ++j) if (get_root(e[seq[j]].src)!=get_root(e[seq[j]].des)) break;
		if (j<m) { merge_root(e[seq[j]].src, e[seq[j]].des); use[seq[j]]=1; } else return -1;
	} return 0;
}

//Tarjan to get the ancestor and highest ancestor in dfs tree of graph.
//array h is the ancestor, hh is highest ancestor, d stores the id.
//The vertices' id is 0~n-1. If it is different, modify the input and 2nd line for loop of tarjan().
struct edge { int des, nxt; };
edge e[M];
int hd[N], vst[N], stk[N], d[N], h[N], hh[N];
int top, id;

inline void tarjan_up(int x, int y) { h[y]=!vst[x]&&d[x]<d[h[y]]?x:h[y]; }
int tarjan_dfs(int x) {
	int i, p, v;
	vst[x]=0; d[x]=id++; stk[top++]=x; h[x]=x; p=d[x];
	for (i=hd[x]; i; i=e[i].nxt)
		if (!~vst[v=e[i].des]) { p=getmin(p, tarjan_dfs(v)); tarjan_up(h[v], x); }
		else if (vst[v]==1) { p=getmin(p, d[v]); tarjan_up(h[v], x); }
		else tarjan_up(v, x);
	if (x!=h[x] || p!=d[x]) vst[x]=1;
	else do { top--; vst[stk[top]]=2; hh[stk[top]]=x; } while (stk[top]!=x);
	return p;
}

void tarjan(int n) {
	memset(vst, -1, sizeof(vst)); top=id=0;
	for (int i=0; i<n; ++i) if (!~vst[i]) tarjan_dfs(i);
}
