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

struct pnt { double x, y; };
typedef pnt vec;
const double eps = 1e-10, pi = acos(-1.0), inf = 1e20;
#define N 10010
pnt p[N];
int n;

double getmin(double x, double y) { return x < y ? x : y; }
double getmax(double x, double y) { return x > y ? x : y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }

pnt rotate(const pnt &p, double ang) {
	vec v = { sin(ang), cos(ang) };
	pnt ret = { submul(p, v), nummul(p, v) }; return ret;
}

double valuate(double ang) {
	int i; double up, dn, lft, rit; pnt tp;
	up = rit = -inf; dn = lft = inf;
	for (i = 0; i < n; ++i) {
		tp = rotate(p[i], ang);
		up = getmax(up, tp.y); dn = getmin(dn, tp.y);
		rit = getmax(rit, tp.x); lft = getmin(lft, tp.x);
	} return up - rit - dn + lft;
}

void output(double ang) {
	int i; double up, dn, lft, rit; pnt tp;
	up = rit = -inf; dn = lft = inf;
	for (i = 0; i < n; ++i) {
		tp = rotate(p[i], ang);
		up = getmax(up, tp.y); dn = getmin(dn, tp.y);
		rit = getmax(rit, tp.x); lft = getmin(lft, tp.x);
	} tp = (pnt){ lft, dn }; tp = rotate(tp, -ang); printf("%.8f %.8f\n", tp.x, tp.y);
	tp = (pnt){ rit, dn }; tp = rotate(tp, -ang); printf("%.8f %.8f\n", tp.x, tp.y);
	tp = (pnt){ rit, up }; tp = rotate(tp, -ang); printf("%.8f %.8f\n", tp.x, tp.y);
	tp = (pnt){ lft, up }; tp = rotate(tp, -ang); printf("%.8f %.8f\n", tp.x, tp.y);
}

void conduct()
{
	int i; double lst, mst, mid, lv, mv, tv;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	lst = 0; mst = pi/2; lv = valuate(lst); mv = valuate(mst);
	while (fabs(mv-lv)>eps) {
//		printf("lst:%.12f mst:%.12f lv:%.12f mv:%.12f\n", lst, mst, lv, mv);
		if (fabs(lv)<eps) { output(lst); return; }
		if (fabs(mv)<eps) { output(mst); return; }
		mid = (lst+mst) / 2; tv = valuate(mid);
		if (lv * tv > eps*eps) { lv = tv; lst = mid; } else { mv = tv; mst = mid; }
	} output(lst);
}

int main()
{
	int time = 0;
	while (scanf("%d", &n) != EOF && n) {
		if (time) printf("\n");
		printf("Case %d:\n", ++time);
		conduct();
	} return 0;
}
