#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<string>
using namespace std;

const double eps = 1e-5;
const double inf = 1e10;
#define SQR(x) ((x)*(x))
struct edge { int nxt, des; double a, b, len; };
struct node {
	int u; double len;
	node(int _u, double _len) { u=_u; len=_len; }
	int operator<(const node &item) const {
		if (fabs(len-item.len)<eps) return u<item.u;
		return len-item.len<-eps;
	}
};
#define N 1100
#define M 2100000
edge e[M];
int vst[N], pre[N], hd[N];
double len[N];
double x[N], y[N], h[N];
int n, m, cnt;

inline double getmax(double x, double y) { return x>y?x:y; }

void insert(int i, int j, double a, double b) {
	++cnt; e[cnt].des=j; e[cnt].a=a; e[cnt].b=b; e[cnt].nxt=hd[i]; hd[i]=cnt;
}

/*int prim(int s, int n) {
	int i, u, v;
	for (i=0; i<n; ++i) len[i]=inf; memset(vst, 0, sizeof(vst)); len[s]=0; pre[s]=s;
	set<node> que; que.clear(); que.insert(node(s, len[s]));
	while (n-- && !que.empty()) {
		u=que.begin()->u; que.erase(que.begin()); vst[u]=1;
		for (i=hd[u]; i; i=e[i].nxt) if (!vst[v=e[i].des] && len[v]-e[i].len>eps) {
			que.erase(node(v, len[v])); len[v]=e[i].len; pre[v]=u; que.insert(node(v, len[v]));
		}
	} return n;
}*/

void prim(int s, int n) {
	int i, j, l;
	double k;
	for (i=0; i<n; ++i) len[i]=inf; memset(vst, 0, sizeof(vst)); len[s]=0.0; pre[s]=s;
	for (i=0; i<n; ++i) {
		for (j=0, k=inf; j<n; ++j) if (!vst[j] && len[j]-k<-eps) { l=j; k=len[j]; }
		vst[l]=1;
		for (j=hd[l]; j; j=e[j].nxt) if (!vst[e[j].des] && len[e[j].des]-e[j].len>eps) {
			len[e[j].des]=e[j].len; pre[e[j].des]=l;
		}
	}
}

void conduct() {
	int i, j;
	double lst, mst, mid, sum;
	for (i=0; i<n; ++i) scanf("%lf%lf%lf", &x[i], &y[i], &h[i]);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) if (i!=j) 
		insert(i, j, fabs(h[i]-h[j]), sqrt(SQR(x[i]-x[j])+SQR(y[i]-y[j])));
	lst=mst=0.0;
	for (i=1; i<=cnt; ++i) lst=getmax(lst, e[i].a/e[i].b); mst=lst+1.0;
	while (mst-lst>eps) {
		mst=mid=lst;
		for (i=1; i<=cnt; ++i) e[i].len=e[i].a-e[i].b*mid;
		prim(0, n);
		for (lst=sum=i=0; i<n; ++i) { lst+=fabs(h[i]-h[pre[i]]); sum+=sqrt(SQR(x[i]-x[pre[i]])+SQR(y[i]-y[pre[i]])); }
		lst/=sum;
	}
	printf("%.3f\n", lst);
}

int main() {
	while (scanf("%d\n", &n)!=EOF && n) conduct();
	return 0;
}
