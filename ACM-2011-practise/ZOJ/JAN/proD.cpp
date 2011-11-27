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

#define square(x) (x)*(x)
const double eps = 1e-9;
struct pnt { double  x, y; };
typedef pnt vec;
#define N 60
#define M 2510
#define L N*M
pnt p[N], q[N];
double dis[N][N], e[N][M], seq[L];
int ref[M], vst[N];
int n, m; double t1, t2, v, val;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

bool check(int x) {
	if (vst[x]) return false; vst[x] = 1;
	for (int i = 1; i <= m; ++i) {
		if (e[x][i]-val>eps) continue;
		if (!ref[i] || check(ref[i])) { ref[i] = x; return true; }
	} return false;
}

bool match() {
	int i, j;
	memset(ref, 0, sizeof(ref));
	for (i = 1; i <= n; ++i) {
		memset(vst, 0, sizeof(vst));
		for (j = 1; j <= m; ++j) {
			if (e[i][j]-val>eps) continue;
			if (!ref[j] || check(ref[j])) { ref[j] = i; break; }
		} if (j > m) return false;
	} return true;
}

void conduct() {
	int i, j, k, lst, mst, mid;
	t1 /= 60.0;
	for (i = 1; i <= n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (i = 1; i <= m; ++i) scanf("%lf%lf", &q[i].x, &q[i].y);
	for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) dis[i][j] = getdis(p[i], q[j])/v;
	for (i = 1; i <= n; ++i) for (j = 0; j < m; ++j) for (k = 0; k < n; ++k) e[i][j*n+k+1] = dis[i][j+1]+t1*(k+1)+t2*k;
	m *= n; for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) seq[(i-1)*m+(j-1)] = e[i][j]; sort(seq, seq+n*m);
	lst = 0; mst = n*m-1;
	while (lst < mst) {
		mid = (lst+mst) / 2; val = seq[mid];
		if (match()) mst = mid; else lst = mid+1;
	} printf("%.6f\n", seq[lst]);
}

int main() {
	while (scanf("%d%d%lf%lf%lf", &m, &n, &t1, &t2, &v) != EOF) conduct();
	return 0;
}
