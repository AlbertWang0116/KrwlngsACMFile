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

//SPFA to get shortest path, with negative cycle detection.
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
