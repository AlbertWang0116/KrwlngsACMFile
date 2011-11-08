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
const double eps = 1e-6, pi = acos(-1.0);
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
		if (fabs(x-p.x)<eps && fabs(y-p.y)<eps) return false;
		return true;
	}
};
typedef pnt vec;
struct line { double a, b, c; };
#define N 10010
pnt p[N], q[N], cen;
bool evt[N];
double rad;
int n;

double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double oridis(const line &l, const pnt  &p) { return l.a*p.x + l.b*p.y - l.c; }

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
	return v / len;
}

line getline(const pnt &p1, const pnt &p2) {
	vec v = uvec(p2-p1);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}

bool circleincvx(int n, pnt *p, const pnt &cen, double rad) {
	for (int i = 0; i < n; ++i) if (submul(p[i]-cen, p[i+1]-cen)<-eps) return false;
	for (int i = 0; i < n; ++i) if (fabs(oridis(getline(p[i], p[i+1]), cen))-rad<-eps) return false;
	return true;
}

bool incircle(const pnt &p, const pnt &cen, double rad) { return getdis(p, cen)-rad < eps; }

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
	} q[ret] = q[0]; evt[ret] = evt[0]; l = ret; if (!ret) return 0;
	for (ret = i = 0; i < l; ++i) {
		if (!evt[i] || q[i] != q[i+1]) { q[ret] = q[i]; evt[ret] = evt[i]; ret++; }
	} if (!ret) { ret = 1; evt[0] = 0; }
	q[ret] = q[0]; evt[ret] = evt[0]; return ret;
}

void conduct()
{
	int i;
	scanf("%lf%lf%lf", &cen.x, &cen.y, &rad);
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y); p[n] = p[0];
	n = circlexcvx(n, p, cen, rad, q, evt);
	for (i = 0; i <= n; ++i) p[i] = q[i];
	for (i = 0; i < n; ++i) if (evt[i]) printf("arc:(%.3f,%.3f)-->(%.3f,%.3f)\n", p[i].x, p[i].y, p[i+1].x, p[i+1].y);
	else printf("segment:(%.3f,%.3f)-->(%.3f,%.3f)\n", p[i].x, p[i].y, p[i+1].x, p[i+1].y);
}

int main()
{
	int time = 0;
	while (scanf("%d", &n) != EOF) {
		printf("Case %d: \n", ++time);
		conduct();
	} return 0;
}
