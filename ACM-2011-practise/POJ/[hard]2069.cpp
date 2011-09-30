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

struct pnt {
	double x, y, z;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x; ret.z = z + p.z;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x; ret.z = z - p.z;
		ret.y = y - p.y; return ret;
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c; ret.z = z * c;
		ret.y = y * c; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c; ret.z = z / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
#define square(x) (x)*(x)
#define N 1010
#define NUM 2
#define R 100
const double eps = 1e-8, inf = 1e9;
pnt p[N];
int n;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)+square(p2.z-p1.z)); }

void conduct()
{
	int i, j, k, l, vi;
	double ans, val, len, stp;
	pnt vp;
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
	ans = inf;
	for (i = 0; i<= NUM; ++i) for (j = 0; j <= NUM; ++j) for (k = 0; k <= NUM; ++k) {
		vp = (pnt){ R/NUM*i, R/NUM*j, R/NUM*k };
		for (stp = R; stp > eps; stp *= 0.98) {
			for (val = -inf, l = 0; l < n; ++l) if ((len = getdis(vp, p[l])) > val) { val = len; vi = l; }
			if (val < ans) ans = val; vp = vp + (p[vi] - vp) / val * stp;
		}
	} printf("%.5f\n", ans);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
