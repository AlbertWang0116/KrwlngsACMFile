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
struct pnt {
	double x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	}
	pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	}
	pnt operator*(const double &c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	}
	pnt operator/(const double &c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
struct line { double a, b, c; };
typedef pnt vec;
const double eps = 1e-6;

vec getvec(const pnt &p1, const pnt &p2) { return p2 - p1; }
vec uvec(const vec &v)
{
	double len = sqrt(square(v.x)+square(v.y));
	vec ret; ret.x = v.x/len; ret.y = v.y/len; return ret;
}

line getmidver(const pnt &p1, const pnt &p2) {
		vec v = getvec(p1, p2); v = v/2; pnt mid = p1 + v; v = uvec(v);
			line ret; ret.a = v.x; ret.b = v.y; ret.c = ret.a*mid.x + ret.b*mid.y; return ret;
}

pnt getcrs(const line &l1, const line &l2)
{
	pnt ret; ret.x = (l1.b*l2.c-l2.b*l1.c) / (l1.b*l2.a-l2.b*l1.a);
	ret.y = (l1.a*l2.c-l2.a*l1.c) / (l1.a*l2.b-l2.a*l1.b); return ret;
}

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x) + square(p2.y-p1.y)); }

void getcircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen, double &r)
{
	line l1 = getmidver(p1, p2), l2 = getmidver(p2, p3);
	cen = getcrs(l1, l2); r = getdis(cen, p1);
}

int main()
{
	double d, r;
	pnt cen, a, b, c;
	while (scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) != EOF) {
		getcircle(a, b, c, cen, r);
//		if (fabs(cen.x) < eps) printf("x^2");
//		else { printf("(x "); if (cen.x > eps) printf("- "); else printf("+ "); printf("%.3f)^2", fabs(cen.x)); }
		printf("(x "); if (cen.x > -eps) printf("- "); else printf("+ "); printf("%.3f)^2", fabs(cen.x));
		printf(" + ");
//		if (fabs(cen.y) < eps) printf("y^2");
//		else { printf("(y "); if (cen.y > eps) printf("- "); else printf("+ "); printf("%.3f)^2", fabs(cen.y)); }
		printf("(y "); if (cen.y > -eps) printf("- "); else printf("+ "); printf("%.3f)^2", fabs(cen.y));
		printf(" = %.3f^2\n", r); d = square(r) - square(cen.x) - square(cen.y);
		printf("x^2 + y^2"); if (cen.x > -eps) printf(" - "); else printf(" + "); printf("%.3fx", fabs(cen.x)*2);
		if (cen.y > -eps) printf(" - "); else printf(" + "); printf("%.3fy", fabs(cen.y)*2);
		if (d > -eps) printf(" - "); else printf(" + "); printf("%.3f = 0\n\n", fabs(d));
	}
}
