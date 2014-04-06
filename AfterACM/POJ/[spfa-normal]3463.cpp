#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;

struct edge { int nxt, len, des; };
#define N 1010
#define M 51000
edge e[M];
int vst[N], ds[N], dt[N], ps[N], pt[N], cs[N], ct[N], hd[N], ahd[N];
int n, m, cnt;
const int MAX = 0x7fffffff;

void insert(int *hd, int i, int j, int k) {
	++cnt; e[cnt].nxt=hd[i]; e[cnt].des=j; e[cnt].len=k; hd[i]=cnt;
}

void dijkstra(int s, int *hd, int *dis, int *pre, int *cnt) {
	int i, j, k, l;
	memset(dis, 0x7f, N*sizeof(int)); memset(vst, 0, sizeof(vst)); dis[s]=0; cnt[s]=1;
	for (i=0; i<n; ++i) {
		for (j=1, k=MAX; j<=n; ++j) if (!vst[j]&&dis[j]<k) { k=dis[j]; l=j; }
		vst[l]=1;
		for (j=hd[l]; j; j=e[j].nxt) {
			if (dis[e[j].des]>dis[l]+e[j].len) { dis[e[j].des]=dis[l]+e[j].len; cnt[e[j].des]=0; }
			if (dis[e[j].des]==dis[l]+e[j].len) cnt[e[j].des]+=cnt[l];
		}
	}
}

void conduct() {
	int i, j, k, l, ans, dis, s, t;
	scanf("%d%d", &n, &m);
	memset(hd, 0, sizeof(hd)); memset(ahd, 0, sizeof(ahd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &j, &k, &l);
		insert(hd, j, k, l); insert(ahd, k, j, l);
	}
	scanf("%d%d", &s, &t);
	dijkstra(s, hd, ds, ps, cs);
	dijkstra(t, ahd, dt, pt, ct);
	ans=cs[t]; dis=ds[t];
	for (i=1; i<=n; ++i) if (ds[i]+dt[i]==dis) 
		for (j=hd[i]; j; j=e[j].nxt) if (ds[i]+e[j].len+dt[e[j].des]==dis+1) ans+=cs[i]*ct[e[j].des];
	printf("%d\n", ans);
}

int main() {
	int time; scanf("%d", &time);
	while(time--) conduct();
	return 0;
}
