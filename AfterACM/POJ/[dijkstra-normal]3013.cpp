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

struct edge { int nxt, des; long long len; };
#define M 210000
#define N 211000
long long dis[N];
int pre[N], hd[N], hp[N], ph[N];
edge e[M];
long long w[N];
int n, m, cnt;

void insert(int x, int y, long long z) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; e[cnt].len=z; hd[x]=cnt;
}

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

void dijkstra(int s, int n, int *hd, edge *e) {
	int i, u, v;
	memset(dis, 0x7f, sizeof(dis)); memset(pre, -1, sizeof(pre)); dis[s]=0;
	for (i=0; i<n; ++i) hpset(i+1, i); hpset(s+1, 0); hpset(1, s); hp[0]=n;
	for (hpdel(u=hp[1]); hp[0]; hpdel(u=hp[1])) 
		for (i=hd[u]; i; i=e[i].nxt) if (dis[v=e[i].des]>dis[u]+e[i].len) {
			dis[v]=dis[u]+e[i].len; pre[v]=u; hpupd(v);
		}
}

void conduct() {
	int i, j, k, l;
	long long ans;
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) { scanf("%d", &j); w[i]=j; }
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &j, &k, &l); --j; --k; ans=l;
		insert(j, k, ans); insert(k, j, ans);
	}
	if (n) dijkstra(0, n, hd, e);
	for (i=1; i<n; ++i) if (!~pre[i]) { printf("No Answer\n"); return; }
	for (ans=i=0; i<n; ++i) ans+=dis[i]*w[i];
	cout << ans << endl;	
}

int main() {
	int time; scanf("%d", &time);
	while(time--) conduct();
	return 0;
}
