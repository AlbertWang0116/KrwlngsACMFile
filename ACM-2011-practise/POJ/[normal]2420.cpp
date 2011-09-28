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
#define N 1010
#define NUM 2
double inf = 1e9, eps = 1e-9;
pnt lp[NUM+1][NUM+1], p[N];
double lst[NUM+1][NUM+1];
int n;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x) + square(p2.y-p1.y)); }

double alldis(const pnt &pp) {
	double ret; int i;
	for (ret = 0, i = 0; i < n; ++i) ret += getdis(pp, p[i]);
	return ret;
}

void conduct()
{
	int i, j, k, l;
	double lft, rit, dn, up, stx, sty, val, tv;
	pnt tp, vp;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	lft = dn = inf; rit = up = -inf;
	for (i = 0; i < n; ++i) {
		if (p[i].x < lft) lft = p[i].x; if (p[i].x > rit) rit = p[i].x;
		if (p[i].y < dn) dn = p[i].y; if (p[i].y > up) up = p[i].y;
	} stx = (rit-lft)/NUM; sty = (up-dn)/NUM;
	for (i = 0; i <= NUM; ++i) for (j = 0; j <= NUM; ++j) {
		lp[i][j] = (pnt){ lft+stx*j, rit+sty*i };
		lst[i][j] = alldis(lp[i][j]);
	} stx /= NUM; sty /= NUM;
	while (stx > eps || sty > eps) {
		for (i = 0; i <= NUM; ++i) for (j = 0; j <= NUM; ++j) {
			for (val = inf, k = -NUM; k <= NUM; ++k) for (l = -NUM; l <= NUM; ++l) {
				tp = (pnt){ lp[i][j].x+stx*l, lp[i][j].y+sty*k }; tv = alldis(tp);
				if (tv < val) { val = tv; vp = tp; }
			} if (val < lst[i][j]) { lst[i][j] = val; lp[i][j] = vp; }
		} stx *= 0.9; sty *= 0.9;
	} for (val = inf, i = 0; i <= NUM; ++i) for (j = 0; j <= NUM; ++j) if (lst[i][j] < val) val = lst[i][j];
	printf("%.0f\n", floor(val+0.5+eps));
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
