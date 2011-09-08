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
struct line { double a, b, c; };
struct pnt {
	double x, y;
	pnt operator+(const pnt &p) {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	}
	pnt operator-(const pnt &p) {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	}
	pnt operator*(const double &c) {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	}
	pnt operator/(const double &c) {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
const double eps = 1e-6;
const double pi = acos(-1.0);
pnt c, p, q;
vec dv;
double cr, pr, t;

double getdis(pnt p1, pnt p2) { return sqrt(square(p2.x-p1.x) + square(p2.y-p1.y)); }
double nummul(vec v1, vec v2) { return v1.x*v2.x + v1.y*v2.y; }
vec getvec(pnt p1, pnt p2) { return p2 - p1; }
int cmp(pnt p1, pnt p2)
{
	if (fabs(p2.x-p1.x) < eps && fabs(p2.y-p1.y) < eps) return 0; else return 1;
}

void input()
{
	scanf("%lf%lf%lf", &c.x, &c.y, &cr);
	scanf("%lf%lf%lf", &p.x, &p.y, &pr);
	scanf("%lf%lf%lf", &dv.x, &dv.y, &t);
}

line getline(pnt p1, pnt p2)
{
	vec v = getvec(p1, p2);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y;
	return ret;
}

void getcrs(line l, pnt cir, double r, pnt &p1, pnt &p2)
{
	double a = (-1) * (l.a * cir.x + l.b * cir.y - l.c) / sqrt(square(l.a) + square(l.b));
	double b = sqrt(square(r) - square(a));
	double c = sqrt(square(l.a) + square(l.b));
//	printf("a:%.3f b:%.3f c:%.3f\n", a, b, c);
	vec vt; vt.x = l.a * a / c; vt.y = l.b * a / c;
	vec vp; vp.x = l.b * b / c; vp.y = -l.a * b / c;
//	printf("vt:%.3f %.3f vp:%.3f %.3f\n", vt.x, vt.y, vp.x, vp.y);
	p1 = cir + vt + vp; p2 = cir + vt - vp;
//	printf("cir:%.3f %.3f p1:%.3f %.3f p2:%.3f %.3f\n", cir.x, cir.y, p1.x, p1.y, p2.x, p2.y);
}

line getref(line l0, line l1, pnt p)
{
	vec vp; vp.x = l0.b; vp.y = -l0.a; double len = sqrt(square(vp.x) + square(vp.y));
	double ca = vp.x / len, sa = vp.y / len;
	double a = l1.a * square(ca) - l1.a * square(sa) + 2 * l1.b * ca * sa;
	double b = l1.b * square(sa) - l1.b * square(ca) + 2 * l1.a * ca * sa;
	line ret; ret.a = a; ret.b = b;
	ret.c = l1.c + (a - l1.a) * p.x + (b - l1.b) * p.y;
	return ret;
}

void conduct()
{
	line l0, l1, l2;
	pnt p1, p2, q1, q2;
	double tot, dis, circle, ang1, ang2, delta;
	bool tail;
	long long cnt;
	cr -= pr;  q = p + dv * t;
	l1 = getline(p, q); tot = getdis(p, q);
	getcrs(l1, c, cr, p1, p2);
//	printf("p1:%.1f,%.1f p2:%.1f,%.1f\n", p1.x, p1.y, p2.x, p2.y);
	if (nummul(dv, getvec(p, p1)) > nummul(dv, getvec(p, p2))) p2 = p1; 
	p1 = p; tail = false; circle = 0;
	while (true) 
	{
		if ((dis = getdis(p1, p2)) - tot > -eps) {
			dv = getvec(p1, p2); p = p1 + dv * tot / dis;
			if (fabs(p.x) < eps) p.x = 0; if (fabs(p.y) < eps) p.y = 0;
			printf("%.1f %.1f\n", p.x, p.y); break;
		} else {
			tot -= dis; l0 = getline(c, p2);
			l2 = getref(l0, l1, p2); getcrs(l2, c, cr, q1, q2);
//			printf("l2:%.3f %.3f %.3f\n", l2.a, l2.b, l2.c);
			p1 = p2; if (!cmp(p2, q1)) p2 = q2; else p2 = q1; l1 = l2;
		}
		if (tail) {
			ang1 = atan2(p1.y-c.y, p1.x-c.x); ang2 = atan2(p2.y-c.y, p2.x-c.x);
			delta = ang2 - ang1; if (delta < eps) delta += 2*pi;
			cnt = tot / dis; tot -= cnt * dis; ang1 = ang1 + delta * cnt; ang2 = ang2 + delta * cnt;
//			printf("ang1:%.3f ang2:%.3f\n", ang1, ang2);
			ang1 = ang1 - pi * 2 * (int)(ang1 / (2*pi)); ang2 = ang2 - pi * 2 * (int)(ang2 / (2*pi));
//			printf("ang1:%.3f ang2:%.3f\n", ang1, ang2);
			p1.x = c.x + cos(ang1) * cr; p1.y = c.y + sin(ang1) * cr;
			p2.x = c.x + cos(ang2) * cr; p2.y = c.y + sin(ang2) * cr;
		} else { tail = true; q = p2; }
	}
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) { input(); conduct(); }
	return 0;
}
