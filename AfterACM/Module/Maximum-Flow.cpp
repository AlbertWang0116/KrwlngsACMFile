//Dinic algorithm to get maximum flow
//The non_recursive format can be get by modify dinic_dfs to the requring format.
//Using Hash or Map to merge multiple capacity edge.
//Flow Parameter (Can be changed to long long):
//	struct edge - cap, flow
//	dinic_dfs - mf, f, tf
//	dinic - f
struct edge { int nxt, des, cap, flow, rev };
edge e[M];
int dis[N], que[N], hd[N];

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
