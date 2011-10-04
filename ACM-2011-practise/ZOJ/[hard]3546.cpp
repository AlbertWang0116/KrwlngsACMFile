#include<iostream>
#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<climits>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<deque>
#include<set>
#include<map>
using namespace std;

#define square(x) (x)*(x)
struct pnt  { 
	double x, y; 
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
struct line { double a, b, c; };
typedef pnt vec;
#define N 1010
const double eps = 1e-9, pi = acos(-1.0), inf = 1e10;
pnt p[N], q[N], cen;
double ang[N], len[N];
int seq[N], tmp[N];
int n, m;

double getmin(double x, double y) { return x < y ? x : y; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }

int cmp(const int &x, const int &y) {
	if (fabs(p[x].y-p[y].y)<eps) return p[x].x-p[y].x < -eps;
	return p[x].y-p[y].y < -eps;
}

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}
vec uvec(const vec &v)
{
	double len = sqrt(square(v.x)+square(v.y));
	return v / len;
}

pnt rotate(pnt p, double ang) {
	vec v1 = p, v2 = { sin(ang), cos(ang) };
	pnt ret; ret.x = submul(v1, v2); ret.y = nummul(v1, v2); return ret;
}

line getline(const pnt &p1, const pnt &p2) {
	vec v = uvec(getvec(p1, p2));
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}

bool inpolygon(pnt *p, pnt p1) {
	int cnt, i;
	pnt p2 = { -inf, p1.y };
	for (cnt = i = 0; i < n; ++i) {
		if (fabs(submul(getvec(p1, p[i]), getvec(p1, p[i+1])))<eps && nummul(getvec(p1, p[i]), getvec(p1, p[i+1])) < eps) return true;
		if (fabs(submul(getvec(p1, p2), getvec(p[i], p[i+1])))<eps) continue;
		if (fabs(p[i+1].y-p1.y)<eps && (p[i+1].x-p2.x)*(p[i+1].x-p1.x) < eps) { if (p[i+1].y < p[i].y) cnt++; continue; }
		if (fabs(p[i].y-p1.y) < eps && (p[i].x-p2.x) * (p[i].x-p1.x) < eps) { if (p[i].y < p[i+1].y) cnt++; continue; }
		if (submul(getvec(p1, p2), getvec(p1, p[i]))*submul(getvec(p1, p2), getvec(p1, p[i+1])) < -eps &&
		      submul(getvec(p[i], p[i+1]), getvec(p[i], p1))*submul(getvec(p[i], p[i+1]), getvec(p[i], p2)) < -eps) cnt++;
	} return cnt%2;
}

double getpos(double lft, double rit, pnt p1, pnt p2, pnt cen) {
	pnt q1, q2; double mid, mv, lv, rv;
	q1 = rotate(p1, -rit); q2 = rotate(p2, -rit);
	lv = submul(getvec(p1, p2), getvec(p1, cen)); rv = submul(getvec(q1, q2), getvec(q1, cen));
	while (rit - lft > eps) {
		mid = (rit+lft) / 2; q1 = rotate(p1, -mid); q2 = rotate(p2, -mid);
		mv = submul(getvec(q1, q2), getvec(q1, cen));
		if (lv*mv > eps) { lv = mv; lft = mid; } else { rv = mv; rit = mid; }
	} return mid;
}

int linecircle(const line &l, const pnt &cen, double r, pnt *p)
{
	vec v1, v2; double dis, len;
	v1 = (vec){l.a, l.b}; v1 = uvec(v1); v2 = (vec){-v1.y, v1.x };
	dis = oridis(l, cen); if (fabs(dis) - r > eps) return 0;
	if (fabs(fabs(dis)-r)<eps) { p[0] = cen - v1*dis; return 1; }
	len = sqrt(square(r)-square(dis));
	p[0] = cen - v1*dis + v2*len; p[1] = cen - v1*dis - v2*len; return 2;
}

int segcircle(const pnt &p1, const pnt &p2, const pnt &cen, double r, pnt *p)
{
	int cnt, ret, i; pnt crs[2];
	cnt = linecircle(getline(p1, p2), cen, r, crs);
	for (ret = i = 0; i < cnt; ++i) if (nummul(getvec(p1, p2), getvec(crs[i], p1))*nummul(getvec(p1, p2), getvec(crs[i], p2)) < eps) p[ret++] = crs[i];
	return ret;
}

double corefunc(pnt *p, pnt cen) {
	double lb, rb, ang1, ang2, area, pra, ret, pos, dr;
	int i, j, k, stp, t, top, bot, cnt;
	pnt p1, p2, q1, q2, r1, r2, tp, tc, crs[2];
	bool find;
	for (lb = inf, rb = -inf, i = 0; i < n; ++i) {
		if (p[i].x > rb) rb = p[i].x;
		if (p[i].x < lb) lb = p[i].x;
	} if (cen.x - lb < -eps) return inf; p[n] = p[0];
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	top = bot = 0; tmp[0] = seq[0];
	for (i = 1; i < n; ++i) {
		while (top > bot && submul(getvec(p[tmp[top-1]],p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < eps) --top;
		tmp[++top] = seq[i];
	} bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && submul(getvec(p[tmp[top-1]],p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < eps) --top;
		tmp[++top] = seq[i];
	} m = top;
	for (stp = -1, i = 0; i < m; ++i) if (fabs(p[tmp[i]].y)<eps && (stp == -1 || p[tmp[i]].x > p[tmp[stp]].x)) stp = i;
	for (i = 0; i < m; ++i) q[i] = p[tmp[(stp+i)%m]]; q[m] = q[0]; q[m+1] = q[1];
	ang[0] = atan2(q[1].y-q[0].y, q[1].x-q[0].x); if (ang[0]+pi<eps) ang[0] = pi; len[0] = q[0].x;
	for (i = 1; i <= m; ++i) {
		ang1 = atan2(q[i].y-q[i-1].y, q[i].x-q[i-1].x);
		ang2 = atan2(q[i+1].y-q[i].y, q[i+1].x-q[i].x);
		while (ang2-ang1 < -eps) ang2 += 2*pi; ang[i] = ang2-ang1; len[i] = getdis(q[i], q[i-1]);
	} ret = inf;
//	printf("q-->"); for (i = 0; i < m; ++i) printf("(%.3f,%.3f)", q[i].x, q[i].y);
//	printf("ang-->"); for (i = 0; i <= m; ++i) printf("%.3f ", ang[i]); printf("\n");
	for (pra = 0, i = 1; i <= m; ++i) pra += len[i]; for (t = 0; cen.x-pra-rb > -eps; ++t) cen.x -= pra;
	tc = cen; if (inpolygon(p, tc)) return t * 2 * pi;
	for (i = 0; i < n; ++i) {
		tc = cen; p1 = p[i]; p2 = p[i+1]; pra = 0; find = false;
		for (j = 0; j <= m; ++j) {
			p1.x -= len[j]; p2.x -= len[j]; tc.x -= len[j]; q1 = rotate(p1, -ang[j]); q2 = rotate(p2, -ang[j]);
			r1 = (pnt){ 0, 0}; dr = getdis(r1, tc); ang1 = atan2(tc.y, tc.x); if (ang1+pi<eps) ang1 = pi;
			cnt = segcircle(p1, p2, r1, dr, crs);
//			printf("i:%d j:%d p1:%.3f,%.3f, p2:%.3f,%.3f cen:%.3f,%.3f cnt:%d crs1:%.3f,%.3f crs2:%.3f,%.3f\n", i, j, p1.x, p1.y, p2.x, p2.y, tc.x, tc.y, cnt, crs[0].x, crs[0].y, crs[1].x, crs[1].y);
			for (k = 0; k < cnt; ++k) { 
				ang2 = atan2(crs[k].y, crs[k].x); if (ang2 + pi < eps) ang2 = pi;
				if (ang2 - ang1 > -eps && ang2 - ang1 - ang[j] < eps) { find = 1; if (pra+ang2-ang1 < ret) ret = pra+ang2-ang1; }
			} if (find) break; p1 = q1; p2 = q2; pra += ang[j];
		}
	} return ret + 2 * pi * t;
}

void conduct()
{
	double ans; int i;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	scanf("%lf%lf", &cen.x, &cen.y);
	if (n == 1) { if (fabs(getdis(p[0], cen))<eps) printf("0.00\n"); else printf("Impossible\n"); return; }
	ans = corefunc(p, cen);
	for (i = 0; i < n; ++i) p[i].x = -p[i].x; cen.x = -cen.x;
	ans = getmin(ans, corefunc(p, cen));
	if (ans-inf > -eps) printf("Impossible\n"); else printf("%.2f\n", ans/pi*180+eps);
}

int main()
{
	int time = 0;
	while (scanf("%d", &n) != EOF) {
		printf("Case %d: ", ++time);
		conduct();
	} return 0;
}
