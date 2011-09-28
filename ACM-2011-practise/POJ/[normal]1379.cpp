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

#define square(x) (x)*(x)
const double eps = 1e-8, inf = 1e9;
#define N 1010
#define NUM 2
pnt p[N];
double lft, rit, up, dn;
int n;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double getmin(const double x, const double y) { return x < y ? x : y; }

double alldis(const pnt &pp) {
	double ret = inf; int i;
	for (i = 0; i < n; ++i) ret = getmin(ret, getdis(pp, p[i]));
	return ret;
}

bool valid(const pnt &p) {
	if (p.x < -eps || p.x - rit > eps) return false;
	if (p.y < -eps || p.y - up > eps) return false;
	return true;
}

void input()
{
	scanf("%lf%lf%d", &rit, &up, &n); lft = dn = 0;
	for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
}

void conduct()
{
	int i, j, k, l;
	pnt pa, pv, pt, ptt; double ans, val, vt, vtt, stx, sty;
	ans = -inf;
	for (i = 0; i <= NUM; ++i) for (j = 0; j <= NUM; ++j) {
		pv = (pnt){ rit/NUM*i, up/NUM*j }; val = alldis(pv);
		stx = rit/NUM/NUM; sty = up/NUM/NUM;
		while (stx > eps || sty > eps) {
			for (pt = pv, vt = val, k = -NUM; k <= NUM; ++k) for (l = -NUM; l <= NUM; ++l) {
				ptt = (pnt){ pv.x+k*stx, pv.y+l*sty }; vtt = alldis(ptt);
				if (valid(ptt) && vtt > vt) { vt = vtt; pt = ptt; }
			} val = vt; pv = pt; stx *= 0.9; sty *= 0.9;
		} if (val > ans) { ans = val; pa = pv; };
	} printf("The safest point is (%.1f, %.1f).\n", pa.x+eps, pa.y+eps);
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) { input(); conduct(); }
	return 0;
}
