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

struct pnt { double x, y; };
struct edge { int nxt, des; };
#define N 110
#define M 11000
edge e[M];
int hd[N], pre[N], vst[N];
pnt p[N], q[N];
int n, m, cnt;
double v, s;
const double eps = 1e-6;
#define SQR(x) ((x)*(x))

double getdis(const pnt &p1, const pnt &p2) { return sqrt(SQR(p2.x-p1.x)+SQR(p2.y-p1.y)); }	

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

int hun_dfs(int x, int i=0, int u=0) {
	for (vst[x]=0, i=hd[x]; i; i=e[i].nxt)
		if (!~(u=pre[e[i].des])||(vst[u]&&hun_dfs(u))) break;
	if (i) pre[e[i].des]=x; return i;
}

int hungarian(int n, int i=0, int ret=0) {
	memset(pre, -1, sizeof(pre));
	for (i=ret=0; i<n; ++i) { memset(vst, -1, sizeof(vst)); hun_dfs(i)?ret++:0; }
	return ret;
}

void conduct() {
	int i, j;
	for (i=0; i<n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (i=0; i<m; ++i) scanf("%lf%lf", &q[i].x, &q[i].y);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<m; ++j) if (getdis(p[i], q[j])/v-s<eps) insert(i, j);
	printf("%d\n", n-hungarian(n));
}

int main() {
	while (scanf("%d%d%lf%lf", &n, &m, &s, &v)!=EOF) conduct();
	return 0;
}
