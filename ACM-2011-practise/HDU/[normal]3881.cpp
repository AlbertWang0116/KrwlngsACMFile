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
#define square(x) (x)*(x)
#define N 100010
const double eps = 1e-7, inf = 1e10, pi = acos(-1.0);
pnt p[N], q[N];
vec v, vv, vct[N];
int seq[N];
int n;

bool equal(const pnt &p1, const pnt &p2) { return (fabs(p1.x-p2.x)<eps && fabs(p1.y-p2.y)<eps); }

double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}
vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; return ret;
}

//int cmp(const int &x, const int &y) {
//	double val1 = nummul(p[x], vv), val2 = nummul(p[y], vv);
//	if (fabs(val1-val2)<eps) return nummul(getvec(p[x], p[y]), v) > eps;
//	return val1 - val2 < -eps;
//}

int cmp(const int &x, const int &y) {
	if (fabs(p[x].x-p[y].x)<eps) return p[x].y-p[y].y < -eps;
	return p[x].x-p[y].x<-eps;
}

void conduct()
{
	int i, j, s, t, ts, tt, lft, rit;
	double val, ang;
	bool none, change;
	vec tv;
	for (i = 1; i <= n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	ang = atan2(v.y, v.x); ang = pi/2 - ang;
	for (i = 1; i <= n; ++i) { q[i].x = p[i].x*cos(ang)-p[i].y*sin(ang); q[i].y = p[i].x*sin(ang)+p[i].y*cos(ang); }
	for (i = 1; i <= n; ++i) p[i] = q[i];
	v.y = 1; v.x = 0; vv.y = 0; vv.x = -1;
//	v = uvec(v); vv.y = -v.x; vv.x = v.y;
	for (i = 1; i <= n; ++i) seq[i] = i; sort(seq+1, seq+n+1, cmp); s = t = n+1;
	for (i = 1; i < n; ++i) vct[i] = uvec(getvec(p[seq[i]], p[seq[i+1]]));
//	for (none = i = 1; i < n; ++i) if (fabs(nummul(p[seq[i]],vv)-nummul(p[seq[i+1]],vv))<eps) {
	for (none = i = 1; i < n; ++i) if (fabs(p[seq[i]].x-p[seq[i+1]].x)<eps) {
		none = 0; change = 0;
//		for (lft = i, rit = i+1; rit < n && fabs(nummul(p[seq[rit]],vv)-nummul(p[seq[rit+1]],vv))<eps; ++rit); i = rit;
		for (lft = i, rit = i+1; rit < n && fabs(p[seq[rit]].x-p[seq[rit+1]].x)<eps; ++rit); i = rit;
		for (j = lft; j < rit; ++j) if (seq[j] < s) { s = seq[j]; change = 1; } if (!change) continue;
		for (t = seq[j = rit]; seq[j] != s; --j) if (seq[j] < t) t = seq[j]; 
	} if (!none) { printf("%d %d\n", s, t); return; }
	for (ang = -1, i = 1; i < n;) {
//		for (lft = i, rit = i+1; rit < n && fabs(submul(vct[lft], vct[rit]))<eps; ++rit);
		for (lft = i, rit = i+1; rit < n && fabs((p[seq[rit+1]].y-p[seq[rit]].y)/(p[seq[rit+1]].x-p[seq[rit]].x)-(p[seq[lft+1]].y-p[seq[lft]].y)/(p[seq[lft+1]].x-p[seq[lft]].x))<eps; ++rit);
//		val = nummul(vct[lft], v);
		val = fabs((p[seq[lft+1]].y-p[seq[lft]].y) / (p[seq[lft+1]].x-p[seq[lft]].x));
//		if (fabs(val)<eps) {
		if (fabs(p[seq[lft]].y-p[seq[rit]].y)<eps) {
			val = 0;
			for (ts = seq[j = lft]; j <= rit; ++j) if (seq[j] < ts) ts = seq[j];
			for (tt = n+1, j = lft; j <= rit; ++j) if (seq[j] < tt && seq[j] != ts) tt = seq[j];
//		} else if (val < -eps) {
		} else if (p[seq[lft]].y-p[seq[rit]].y>eps) {
//			val = -val;
			for (ts = seq[j = rit]; j > lft; --j) if (seq[j] < ts) ts = seq[j];
			for (tt = seq[j = lft]; seq[j] != ts; ++j) if (seq[j] < tt) tt = seq[j];
		} else {
			for (ts = seq[j = lft]; j < rit; ++j) if (seq[j] < ts) ts = seq[j];
			for (tt = seq[j = rit]; seq[j] != ts; --j) if (seq[j] < tt) tt = seq[j];
		} if (val - ang > eps || (fabs(val - ang)<eps && (ts < s || (ts == s && tt < t)))) {
			ang = val; s = ts; t = tt;
		} i = rit;
	} printf("%d %d\n", s, t);
}

int main()
{
	while (scanf("%d%lf%lf", &n, &v.x, &v.y)!= EOF) conduct();
	return 0;
}
