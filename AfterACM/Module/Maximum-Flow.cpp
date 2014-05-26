//Dinic algorithm to get maximum flow. O(MN^2)
//The non_recursive format can be get by modify dinic_dfs to the requring format.
//Using Hash or Map to merge multiple capacity edge.
//Flow Parameter (Can be changed to long long):
//	struct edge - cap, flow
//	dinic_dfs - mf, f, tf, return value
//	dinic - f, return value
struct edge { int nxt, des, cap, flow, rev };
edge e[M];
int dis[N], que[N], hd[N], ce[N];

int dinic_dfs(int s, int t, int mf) {
	int i, f, tf;
	if (dis[s]==dis[t]) return s==t?mf:0;
	for (i=ce[s], f=mf; f&&i; i=f?e[i].nxt:i)
		if (e[i].cap && dis[e[i].des]==dis[s]+1) {
			tf=dinic_dfs(e[i].des, t, getmin(f, e[i].cap));
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	ce[s]=i; return mf-f;
}

int dinic(int s, int t) {
	int i, f, u, head, tail;
	for (f=0; 1; ) {
		memset(dis, -1, sizeof(dis)); memcpy(ce, hd, sizeof(hd));
		for (head=tail=dis[u=s]=0; head<=tail; u=que[++head]) 
			for (i=hd[u]; i; i=e[i].nxt) if (e[i].cap && dis[e[i].des]<0) 
				dis[que[++tail]=e[i].des] = dis[u]+1;
		if (dis[t]<0) return f;
		f+=dinic_dfs(s, t, INF_FLOW);
	}
}


//SAP algorithm to get maximum flow. O(MN^2)
//The non_recursive format can be get by modify sap_dfs to the requring format.
//Using Hash or Map to merge multiple capacity edge.
//Flow Parameter (Can be changed to long long):
//	struct edge - cap, flow
//	sap_relabel - flow
//	sap_dfs - mf, f, tf, return value
//	sap - f, return value
//Note of parameter
//	N - the maximum number of the vertices in graph
struct edge { int nxt, des, cap, flow, rev; };
int hd[N], ce[N], dis[N], que[N], blk[N], pst[N], pre[N];
edge e[M];
int flag;

void sap_blk_insert(int s, int lv) { pre[s]=-1; pst[s]=blk[lv]; if (~blk[lv]) pre[blk[lv]]=s; blk[lv]=s; }
void sap_relabel(int s, int rev, int flow) {
	int i, lv=dis[s];
	for (i=ce[s]=hd[s], dis[s]=N-1; i; i=e[i].nxt)
		if (e[i].cap) dis[s]=getmin(dis[s], dis[e[i].des]+1);
	if (flow&&rev) dis[s]=getmin(dis[s], dis[e[rev].des]+1);
	if (~pre[s]) pst[pre[s]]=pst[s]; else blk[lv]=pst[s];
	if (~pst[s]) pre[pst[s]]=pre[s]; 
	sap_blk_insert(s, dis[s]); flag=~blk[lv]?flag:0;
}

int sap_dfs(int s, int mf, int rev) {
	int i, tf, f;
	if (!dis[s]) return mf;
	for (i=ce[s], f=mf; f&&i; i=f||!e[i].cap?e[i].nxt:i)
		if (e[i].cap && dis[e[i].des]==dis[s]-1) {
			tf=sap_dfs(e[i].des, getmin(f, e[i].cap), e[i].rev);
			e[i].cap-=tf; e[i].flow+=tf; e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf; f-=tf;
		}
	if (i) ce[s]=i; else sap_relabel(s, rev, mf-f);
	return mf-f;
}

int sap(int s, int t) {
	int i, u, f, head, tail;
	memset(dis, -1, sizeof(dis)); memcpy(ce, hd, sizeof(hd));
	for (head=tail=dis[u=t]=0; head<=tail; u=que[++head]) 
		for (i=hd[u]; i; i=e[i].nxt) if (e[e[i].rev].cap && dis[e[i].des]<0) 
			dis[que[++tail]=e[i].des] = dis[u]+1;
	if (dis[s]<0) return 0;
	for (i=0; i<N; ++i) if (dis[i]<0) dis[i]=N-1;
	memset(blk, -1, sizeof(blk)); f=0; flag=1;
	for (i=0; i<N; ++i) sap_blk_insert(i, dis[i]);
	while (flag) f+=sap_dfs(s, INF_FLOW, 0); return f;
}


//highest-relabel algorithm to get maximum flow. O(N^3)
//The algorithm is non-recursive
//Using Hash or Map to merge multiple capacity edge.
//Flow Parameter (Can be changed to long long):
//	struct edge - cap, flow
//	global array - cf
//	hl_push - flow
//	highest_relabel - return value
//Note of parameter
//	N - the maximum number of vertices in graph
//	highest_relabel :: mx - the smallest integer that bigger than the vertices index except source and sink.
struct edge { int nxt, des, cap, flow, rev; };
edge e[M];
int hd[N], ce[N], dis[N], que[N], cf[N], blk[2*N], pst[N];

void hl_push(int u, int v, int i, int flow) {
	cf[u]-=flow; e[i].cap-=flow; e[i].flow+=flow;
	cf[v]+=flow; e[e[i].rev].cap+=flow; e[e[i].rev].flow-=flow;
}

void hl_relabel(int u, int &v, int &lv, int mx) {
	int i, j, k;
	for (i=ce[u]=hd[u], dis[u]=2*N; i; i=e[i].nxt)
		if (e[i].cap) dis[u]=getmin(dis[u], dis[e[i].des]+1);
	if (~v) pst[v]=pst[u]; else blk[lv]=pst[u];
	pst[u]=blk[dis[u]]; blk[dis[u]]=u;
	if (!~blk[lv] && dis[u]<mx)
		for (i=lv+1; i<mx; ++i) for (j=blk[i], k=pst[j]; ~j; blk[i]=j=k, k=~k?pst[k]:0) {
			dis[j]=mx+1; pst[j]=blk[dis[j]]; blk[dis[j]]=j;
		}
	lv=dis[u]; v=-1;
}

int highest_relabel(int s, int t, int mx) {
	int i, u, v, head, tail, lv;
	memset(dis, -1, sizeof(dis)); memcpy(ce, hd, sizeof(hd));
	for (head=tail=dis[u=t]=0; head<=tail; u=que[++head]) 
		for (i=hd[u]; i; i=e[i].nxt) if (e[e[i].rev].cap && dis[e[i].des]<0) 
			dis[que[++tail]=e[i].des] = dis[u]+1;
	for (i=0; i<N; ++i) if (dis[i]<0) dis[i]=mx+3; dis[s]=mx+2;
	memset(blk, -1, sizeof(blk));
	for (i=0; i<mx; ++i) if (i!=s&&i!=t) { pst[i]=blk[dis[i]]; blk[dis[i]]=i; }
	memset(cf, 0, sizeof(cf)); cf[s]=INF_FLOW;
	for (i=hd[s]; i; i=e[i].nxt) hl_push(s, e[i].des, i, e[i].cap);
	for (lv=mx+3, u=blk[lv], v=-1; lv; v=u, u=~u?pst[u]:blk[--lv]) while (~u&&cf[u]) {
		for (i=ce[u]; cf[u]&&i; i=cf[u]||!e[i].cap?e[i].nxt:i)
			if (e[i].cap && dis[e[i].des]==dis[u]-1) hl_push(u, e[i].des, i, getmin(e[i].cap, cf[u]));
		if (cf[u]) hl_relabel(u, v, lv, mx+2); else ce[u]=i;
	}
	return cf[t];
}

//Hungarian algorithm to get maximum match in binary chart. O(NM)
//The non_recursive format can be get by modify hun_dfs. But BFS is recommended.
//Note of parameter
//	hungarian :: n - the number of the vertices in left side graph.

struct edge { int nxt, des; };
edge e[M];
int hd[N], vst[N], pre[N];

int hun_dfs(int x, int i=0, int u=0) {
	for (vst[x]=0, i=hd[x]; i; i=e[i].nxt)
		if (!~(u=pre[e[i].des])||(vst[u]&&hun_dfs(u))) break;
	if (i) pre[e[i].des]=x; return i;
}

int hungarian(int n, int i=0, int ret=0) {
	memset(pre, -1, sizeof(pre));
	for (i=0; i<n; ++i) { memset(vst, -1, sizeof(vst)); hun_dfs(i)?++ret:0; }
	return ret;
}

//KM algorithm to get maximum valued match in binary chart. O(N^3)
//Use BFS Hungarian to decrease the complexity of code.
//Value Parameter (Can be changed to long long):
//	global array - tx, ty, lst
//	km_update - w
//	km - return value, ret
//Note of parameter
//	km :: n - the number of the vertices in left side graph (and, the right side should also has this number, make up if not)
//	km :: inf - the maximum total value of the match

int w[N][N], pre[N], vst[N], que[N];
int tx[N], ty[N], lst[N];
int head, tail;

inline void km_update(int i, int j, int &k, int w) { lst[j]=w; vst[j]=i; if (!w) { que[++tail]=j; k=!~pre[j]?j:k; } }
int km(int n) {
	int i, j, k, u, v, m=n;
	int ret;
	memset(pre, -1, sizeof(pre)); memset(ty, 0, sizeof(ty));
	for (i=0; i<n; ++i) for (tx[i]=w[i][0], j=1; j<m; ++j) tx[i]=getmax(tx[i], w[i][j]);
	for (i=0; i<n; ++i) {
		memset(vst, -1, sizeof(vst)); head=0; tail=k=-1;
		for (j=0; j<m; ++j) km_update(-1, j, k, tx[i]+ty[j]-w[i][j]);
		while (!~k) {
			while (head<=tail && !~k) {
				v=que[head++]; u=pre[v]; 
				for (j=0; j<m; ++j) if (tx[u]+ty[j]-w[u][j]<lst[j]) km_update(v, j, k, tx[u]+ty[j]-w[u][j]);
			} if (~k) break;
			for (ret=inf, j=0; j<m; ++j) if(lst[j]) ret=getmin(ret, lst[j]);
			for (j=0; j<=tail; ++j) { ty[que[j]]+=ret; tx[pre[que[j]]]-=ret; } tx[i]-=ret;
			for (j=0; j<m; ++j) if (lst[j]) km_update(vst[j], j, k, lst[j]-ret);
		}
		while (~vst[k]) { pre[k]=pre[vst[k]]; k=vst[k]; } pre[k]=i;
	}
	for (ret=i=0; i<n; ++i) ret+=tx[i]; for (j=0; j<m; ++j) ret+=ty[j]; return ret;
}

//EK algorithm to get minimum cost maximum flow. O(NM^2)
//If the graph is the DAG, or don't have positive-loop, the algorithm can also get the maximum cost maximum flow.
//To get maximum cost maximum flow, change dis memset to -1, and spfa inequality ">" to "<". The rest is the same.
//Flow & Cost Parameter (Can be changed to long long):
//	struct edge - cap, flow, cos
//  mcmf - return value, cost
//Note of parameter
// mcmf :: n - The number of vertices in flow graph.
struct edge { int nxt, des, cap, flow, rev, cos; };
edge e[M];
int hd[N], dis[N], que[N], vst[N], pre[N];

#define next(x, n) ((x)=(x)?(x)-1:(n))
int mcmf(int s, int t, int &cost, int n) {
	int f, tf, u, v, i, head, tail;
	for (f=cost=0; 1; ) {
		memset(dis, 0x7f, sizeof(dis)); memset(vst, 0, sizeof(vst));
		for (head=tail=cnt=dis[u=s]=pre[s]=pre[t]=0; ~cnt--; vst[u=que[next(head, n)]]--)
			for (i=hd[u]; i; i=e[i].nxt) if (e[i].cap && dis[v=e[i].des]>dis[u]+e[i].cos) {
				dis[v]=dis[u]+e[i].cos; pre[v]=e[i].rev;
				if (!vst[v]) { ++vst[v]; ++cnt; que[next(tail, n)]=v; }
			}
		if (!pre[t]) return f;
		for (tf=INF_FLOW, v=t; pre[v]; v=e[pre[v]].des) tf=getmin(tf, e[e[pre[v]].rev].cap);
		for (f+=tf, v=t; pre[v]; v=e[pre[v]].des) {
			i=e[pre[v]].rev; e[i].cap-=tf; e[i].flow+=tf; cost+=tf*e[i].cos;
			e[e[i].rev].cap+=tf; e[e[i].rev].flow-=tf;
		}
	}
}
