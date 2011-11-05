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
const double eps = 1e-9, inf = 1e4, pi = acos(-1.0);
struct pnt {
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
	} bool operator!=(const pnt &p) const {
		return (fabs(x-p.x)>eps || fabs(y-p.y)>eps);
	}
};
typedef pnt vec;
struct line { double a, b, c; };
#define N 10010
pnt p[N], q[N];
double ang[N], rad;
int seq[N]; bool evt[N];
line l[N];
int n, m;

const line bdr1 = { 1, 0, -inf }, bdr2 = { -1, 0, -inf }, bdr3 = { 0, 1, -inf }, bdr4 = { 0, -1, -inf };
const pnt cen = { 0, 0 };

double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
	return v / len;
}

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b); return ret;
}

line getline(const pnt &p1, const pnt &p2) {
	vec v = uvec(p2-p1);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}

int hfpcmp(const int &i, const int &j) {
	if (fabs(ang[i]-ang[j])<eps) return l[i].c-l[j].c > eps;
	return ang[i]-ang[j]<-eps;
}

int hlfplane(int n, line *l, pnt *p, int *seq, double *ang) {
	int i, j, top, bot, ret;
	l[n++] = bdr1; l[n++] = bdr2; l[n++] = bdr3; l[n++] = bdr4;
	for (i = 0; i < n; ++i) { ang[i] = atan2(l[i].b, l[i].a); if (fabs(ang[i]-pi)<eps) ang[i] = -pi; }
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, hfpcmp);
	for (i = j = 1; i < n; ++i) if (fabs(ang[seq[i]]-ang[seq[j-1]])>eps) seq[j++] = seq[i]; n = j;
	for (i = 1, top = bot = 0; i < n; ++i) {
		while (top > bot && oridis(l[seq[i]], p[top])<-eps) --top;
		p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		if (ang[seq[i]] > -eps) break;
	} p[bot] = (pnt){ -inf*2, -inf*2 };
	for (++i; i < n; ++i) {
		if (oridis(l[seq[i]], p[bot])>-eps) continue;
		while (top > bot && oridis(l[seq[i]], p[top]) < -eps) --top;
		if (top == bot) break; p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		while (oridis(l[seq[top]], p[bot+1])<-eps) ++bot; p[bot] = getcrs(l[seq[top]], l[seq[bot]]);
	} if (i < n) return 0;
	for (ret = 0, i = bot; i < top; ++i) if (fabs(p[i].x-p[i+1].x)>eps || fabs(p[i].y-p[i+1].y)>eps) {
		seq[ret] = seq[i]; p[ret] = p[i]; ret++;
	} if (!ret || fabs(p[i].x-p[0].x)>eps || fabs(p[i].y-p[0].y)>eps) {
		seq[ret] = seq[i]; p[ret] = p[i]; ret++;
	} p[ret] = p[0]; return ret;
}

bool incircle(const pnt &p, const pnt &cen, double rad) {
	if (getdis(p, cen) - rad < eps) return 1; return 0;
}

bool circleincvx(int n, pnt *p, const pnt &cen, double rad) {
	for (int i = 0; i < n; ++i) if (submul(p[i]-cen, p[i+1]-cen)<-eps) return false;
	for (int i = 0; i < n; ++i) if (fabs(oridis(getline(p[i], p[i+1]), cen))-rad<-eps) return false;
	return true;
}

void segxcircle(const pnt &p1, const pnt &p2, const pnt &cen, double rad, int &top, pnt *p) {
	vec v1, v2; pnt tp; double ver, hor;
	v1 = uvec(p2-p1); v2 = (vec){ -v1.y, v1.x }; 
	ver = nummul(cen, v2) - nummul(p1, v2); if (fabs(ver)-rad > eps) return;
	hor = sqrt(square(rad)-square(ver));
	tp = cen - v2 * ver - v1 * hor; if (nummul(tp-p1, tp-p2) < eps) p[top++] = tp;
	if (hor > eps) { tp = tp + v1 * hor * 2; if (nummul(tp-p1, tp-p2) < eps) p[top++] = tp; }
}

int circlexcvx(int n, pnt *p, const pnt &cen, double rad, pnt *q, bool *evt) {
	int i, j, k, l, ret; pnt tp[4];
	if (circleincvx(n, p, cen, rad)) { q[0] = q[1] = (pnt){ cen.x + rad, cen.y }; evt[0] = 1; return 1; }
	for (ret = i = 0; i < n; ++i) {
		tp[0] = p[i]; l = 1; segxcircle(p[i], p[i+1], cen, rad, l, tp);
		for (k = j = 1; j < l; ++j) if (tp[j] != p[i] && tp[j] != p[i+1]) tp[k++] = tp[j];
		for (j = 0; j < k; ++j) if (incircle(tp[j], cen, rad)) { evt[ret] = 0; q[ret++] = tp[j]; }
		if (!incircle(p[i+1], cen, rad) && incircle(tp[k-1], cen, rad)) evt[ret-1] = 1;
	} q[ret] = q[0]; evt[ret] = evt[0]; l = ret;
	for (ret = i = 0; i < l; ++i) {
		if (!evt[i] || q[i] != q[i+1]) { q[ret] = q[i]; evt[ret] = evt[i]; ret++; }
	} if (!ret) { ret = 1; evt[0] = 0; }
	q[ret] = q[0]; evt[ret] = evt[0]; return ret;
}

double circlearea(const pnt &p1, const pnt &p2, const pnt &cen, double rad) {
	vec v1, v2; double ang1, ang2;
	v1 = p1 - cen; v2 = p2 - cen; ang1 = atan2(v1.y, v1.x); ang2 = atan2(v2.y, v2.x);
	while (ang2-ang1<eps) ang2 += 2*pi; return rad*rad*(ang2-ang1)/2.0;
}

void conduct()
{
	int i, tag; double ans; pnt pos;
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
	scanf("%lf%lf", &pos.x, &pos.y); 
	for (i = 0; i < n; ++i) if (submul(q[i]-p[i], pos-p[i]) > eps) l[i] = getline(p[i], q[i]);
							else l[i] = getline(q[i], p[i]);
	n = hlfplane(n, l, p, seq, ang);
	for (i = 0; i < n; ++i) q[i] = p[i]; q[n] = q[0];
	n = circlexcvx(n, q, cen, rad, p, evt);
	for (ans = i = 0; i < n; ++i) if (evt[i]) ans += circlearea(p[i], p[i+1], cen, rad);
								  else ans += submul(p[i]-cen, p[i+1]-cen) / 2.0;
	printf("%.5f", (ans+eps)*100.0/(rad*rad*pi)); cout << "%" << endl;
}

int main()
{
	int time; scanf("%d", &time);
	for (int i = 1; i <= time; ++i) {
		scanf("%lf%d", &rad, &n);
		printf("Case %d: ", i);
		conduct();
	} return 0;
}
