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

const double eps = 1e-12, inf = 1e9;
struct pnt { double x, y, z; };
#define square(x) (x)*(x)
#define N 1010
#define NUM 2
#define R 100
pnt p[N];
int n;

double getmax(double x, double y) { return x > y ? x : y;}
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)+square(p2.z-p1.z)); }

double alldis(const pnt &pp) {
	double ret = -inf;
	for (int i = 0; i < n; ++i) ret = getmax(ret, getdis(pp, p[i]));
	return ret;
}

void conduct()
{
	int i, j, k, ii, jj, kk;
	double ans, val, vt, vtt, stp;
	pnt pv, pt, ptt;
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
	ans = inf;
	for (i = 1; i < NUM; ++i) for (j = 1; j < NUM; ++j) for (k = 1; k < NUM; ++k) {
		for (vt = vtt = stp = ii = 0; ii < n; ++ii) { vt += p[ii].x; vtt += p[ii].y; stp += p[ii].z; }
		pv = (pnt){ vt/n, vtt/n, stp/n }; val = alldis(pv);
		for (stp = vt+vtt+stp; stp > eps; stp *= 0.95) {
			for (pt = pv, vt = val, ii = -NUM; ii <= NUM; ++ii)
				for (jj = -NUM; jj <= NUM; ++jj) for (kk = -NUM; kk <= NUM; ++kk) {
					ptt = (pnt){ pv.x+stp*ii, pv.y+stp*jj, pv.z+stp*kk }; vtt = alldis(ptt);
					if (vtt < vt) { vt = vtt; pt = ptt; }
				} pv = pt; val = vt;
		} if (val < ans) ans = val;
	} printf("%.5f\n", ans+eps);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
