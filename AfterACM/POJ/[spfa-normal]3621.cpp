#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<map>
using namespace std;

struct edge { int nxt, src, des, len; double dis; };
#define N 1010
#define M 11000
edge e[M];
int hd[N], vst[N], pc[N], que[N], val[N];
double dis[N];
int n, m, cnt;
const double inf = 1e10;
const double eps = 1e-5;

inline double getmax(double x, double y) { return x>y?x:y; }

void insert(int i, int j, int k) {
	++cnt;e[cnt].src=i; e[cnt].des=j; e[cnt].len=k; e[cnt].nxt=hd[i]; hd[i]=cnt;
}

#define next(x, n) ((x)=(x)?(x)-1:(n))
int spfa(int s, int n) {
	int i, head, tail, cnt, u, v;
	for (i=0; i<n; ++i) dis[i]=inf; memset(vst, 0, sizeof(vst));
	for (head=tail=dis[u=s]=pc[s]=cnt=0; ~cnt--; vst[u=que[next(head, n)]]--)
		for (i=hd[u]; i; i=e[i].nxt) if (dis[v=e[i].des]-dis[u]-e[i].dis>eps) {
			dis[v]=dis[u]+e[i].dis; pc[v]=pc[u]+1; if (pc[v]>=n) return -1;
			if (!vst[v]) { ++vst[v]; ++cnt; que[next(tail, n)]=v; }
		}
	return 0;
}

void conduct() {
	int i, j, k, l;
	double lst, mst, mid;
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) scanf("%d", &val[i]);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &j, &k, &l); --j; --k;
		insert(j, k, l);
	}
	lst=mst=0.0;
	for (i=1; i<=cnt; ++i) mst=getmax(mst, (double)val[e[i].src]/e[i].len);
	while (mst-lst>eps) {
		mid=(mst+lst)/2.0;
		for (i=1; i<=cnt; ++i) e[i].dis=(double)e[i].len*mid-(double)val[e[i].src];
		if (spfa(0, n)) lst=mid; else mst=mid;
	}
	printf("%.2f\n", lst);
}

int main() {
	conduct();
	return 0;
}
