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
#define getmax(x, y) (x)>(y)?(x):(y)
#define getmin(x, y) (x)<(y)?(x):(y)

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
typedef pnt vec;
struct line { double a, b, c; };
const double eps = 1e-6;
const double pi = acos(-1.0);

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x - p1.x) + square(p2.y - p1.y)); }

vec uvec(const vec &v)
{
	double len = sqrt(square(v.x) + square(v.y));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; return ret;
}

vec getvec(const pnt &p1, const pnt &p2)
{
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

pnt getcrs(const line &l1, const line &l2) 
{
	pnt ret; ret.x = (l1.b*l2.c - l2.b*l1.c) / (l1.b*l2.a - l2.b*l1.a);
	ret.y = (l1.a*l2.c - l2.a*l1.c) / (l1.a*l2.b - l2.a*l1.b); return ret;
}

line getline(const pnt &p, const vec &tv)
{
	vec v = uvec(tv);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p.x + ret.b * p.y; return ret;
}

line getmidver(const pnt &p1, const pnt & p2)
{
	vec hor, ver; pnt mid;
	hor = getvec(p1, p2); ver.x = -hor.y; ver.y = hor.x; hor = hor / 2;
	mid = p1 + hor; return getline(mid, ver);
}

bool lmst(double ang1, double ang2) { return (fabs(ang1 + pi) < eps || fabs(pi - ang2) < eps); }
bool rmst(double ang1, double ang2) { return (ang1 * ang2 < eps); }
bool dmst(double ang1, double ang2) { return ((ang1+pi/2)*(ang2+pi/2) < eps); }
bool umst(double ang1, double ang2) { return ((ang1-pi/2)*(ang2-pi/2) < eps); }

int main()
{
	pnt p1, p2, p3, cen;
	line l1, l2;
	double r, ang1, ang2, ang3, lx, ly, mx, my, tmp;
	int ilx, ily, imx, imy;
	bool tag;
	scanf("%lf%lf", &p1.x, &p1.y); scanf("%lf%lf", &p2.x, &p2.y); scanf("%lf%lf", &p3.x, &p3.y);
	l1 = getmidver(p1, p2); l2 = getmidver(p2, p3); cen = getcrs(l1, l2); r = getdis(cen, p1);
//	printf("d1:%.3f d2:%.3f d3:%.3f\n", getdis(cen, p1), getdis(cen, p2), getdis(cen, p3));
	ang1 = atan2(p1.y-cen.y, p1.x-cen.x); ang2 = atan2(p2.y-cen.y, p2.x-cen.x); ang3 = atan2(p3.y-cen.y, p3.x-cen.x);
	if (ang1 > ang2) { tmp = ang1; ang1 = ang2; ang2 = tmp; }
	if ((ang3-ang1) * (ang3-ang2) > eps) tag = 1; else tag = 0;
//	printf("cen:%.3f,%.3f r:%.3f ang1:%.3f ang2:%.3f ang3:%.3f\n", cen.x, cen.y, r, ang1, ang2, ang3);
	if (tag ^ lmst(ang1, ang2)) lx = cen.x - r; else lx = getmin(cen.x+cos(ang1)*r, cen.x+cos(ang2)*r);
	if (tag ^ rmst(ang1, ang2)) mx = cen.x + r; else mx = getmax(cen.x+cos(ang1)*r, cen.x+cos(ang2)*r);
	if (tag ^ dmst(ang1, ang2)) ly = cen.y - r; else ly = getmin(cen.y+sin(ang1)*r, cen.y+sin(ang2)*r);
	if (tag ^ umst(ang1, ang2)) my = cen.y + r; else my = getmax(cen.y+sin(ang1)*r, cen.y+sin(ang2)*r);
//	printf("lx:%.3f ly:%.3f mx:%.3f my:%.3f\n", lx, ly, mx, my);
	ilx = floor(lx+eps); imx = ceil(mx-eps); 
	ily = floor(ly+eps); imy = ceil(my-eps); 
	printf("%d\n", (imx-ilx)*(imy-ily));
}
