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

double eps = 1e-9, pi = acos(-1.0);
struct pnt {
	double x, y;
	bool operator<(const pnt &p) const {
		if (fabs(y-p.y)<eps) return x-p.x < -eps;
		return y-p.y < -eps;
	}
};
typedef pnt vec;
#define N 50010
int seq[N], tmp[N], fst[N], snd[N];
double evt[N], next[N];
pnt p[N];
int n, m;

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

int cmp(const int &x, const int &y) { return p[x] < p[y]; }

double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double getmin(double x, double y) { return x-y<-eps?x:y; }
double getmax(double x, double y) { return x-y>eps?x:y; }

void conduct()
{
	int i, j, bot, top, lst, mst;
	double ang, ang1, ang2, dlt, ans;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	for (tmp[bot = top = 0] = seq[0], i = 1; i < n; ++i) {
		while (top > bot && submul(getvec(p[tmp[top-1]], p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < -eps) --top;
		tmp[++top] = seq[i];
	} bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && submul(getvec(p[tmp[top-1]], p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < -eps) --top;
		tmp[++top] = seq[i];
	} n = top;
	for (i = 0; i <= n; ++i) seq[i] = tmp[i]; seq[n+1] = seq[1];
	for (i = 0; i < n; ++i) { 
		ang1 = atan2(p[seq[i+1]].y-p[seq[i]].y, p[seq[i+1]].x-p[seq[i]].x);
		ang2 = atan2(p[seq[i+2]].y-p[seq[i+1]].y, p[seq[i+2]].x-p[seq[i+1]].x);
		while (ang2-ang1 < -eps) ang2 += 2*pi; next[i] = ang2 - ang1;
	} for (lst = mst = 0, i = 1; i < n; ++i) {
		if (p[seq[i]] < p[seq[lst]]) lst = i;
		if (p[seq[mst]] < p[seq[i]]) mst = i;
	} ang1 = atan2(p[seq[lst+1]].y-p[seq[lst]].y, p[seq[lst+1]].x-p[seq[lst]].x);
	ang2 = atan2(p[seq[mst]].y-p[seq[mst+1]].y, p[seq[mst]].x-p[seq[mst+1]].x);
	for (ang = i = 0; ang-pi < -eps; ) {
		dlt = getmin(ang1, ang2); ang += dlt;
		++i; evt[i] = ang; fst[i] = lst; snd[i] = mst;
		ang1 -= dlt; if (fabs(ang1)<eps) { ang1 = next[lst]; lst = (lst+1)%n; }
		ang2 -= dlt; if (fabs(ang2)<eps) { ang2 = next[mst]; mst = (mst+1)%n; }
	} ans = 0; m = i;
	for (i = 0; i < n; ++i) for (j = i+1; j < n; ++j) {
		ang = atan2(p[seq[j]].y-p[seq[i]].y, p[seq[j]].x-p[seq[i]].x); 
		if (ang < -eps) ang += pi; lst = 1; mst = m;
		while (mst > lst) { top = (lst+mst)/2; if (ang-evt[top] > eps) lst = top+1; else mst = top; }
		ans = getmax(ans, fabs(submul(getvec(p[seq[i]], p[seq[j]]), getvec(p[seq[i]], p[seq[fst[lst]]]))));
		ans = getmax(ans, fabs(submul(getvec(p[seq[i]], p[seq[j]]), getvec(p[seq[i]], p[seq[snd[mst]]]))));
	} printf("%.2f\n", ans/2);
}

int main()
{
	while (scanf("%d", &n) != EOF && n != -1) conduct();
	return 0;
}
