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
struct pnt { double x, y; };
const double eps = 1e-6, inf = 1e20;
#define N 10010
pnt p[N], des;
int n;
double vb, vp;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p1.x-p2.x)+square(p1.y-p2.y)); }

void conduct()
{
	int i, rp; double tt, ret;
	for (i = 0; i < n; ++i) scanf("%lf", &p[i].x);
	for (i = 0; i < n; ++i) p[i].y = 0.0; scanf("%lf%lf", &des.x, &des.y);
	for (ret = inf, i = 1; i < n; ++i) {
		tt = getdis(p[i], des) / vp + p[i].x / vb;
		if (tt-ret < eps) { ret = tt; rp = i; }
	} printf("%d\n", rp+1);
}

int main()
{
//	while (scanf("%d%lf%lf", &n, &vb, &vp) != EOF) conduct();
	scanf("%d%lf%lf", &n, &vb, &vp); conduct();
	return 0;
}
