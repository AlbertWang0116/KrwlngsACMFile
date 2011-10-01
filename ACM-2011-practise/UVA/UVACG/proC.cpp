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
const double eps = 1e-6;
struct pnt {
	double x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const double &c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const double &c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
struct line { double a, b, c; };
pnt p1, p2, p3;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
	return v / len;
}

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b*l2.c-l2.b*l1.c) / (l1.b*l2.a-l2.b*l1.a);
	ret.y = (l1.a*l2.c-l2.a*l1.c) / (l1.a*l2.b-l2.a*l1.b); return ret;
}

line getline(const pnt &p, const vec &v) {
	vec vv = uvec(v);
	line ret; ret.a = -vv.y; ret.b = vv.x;
	ret.c = ret.a * p.x + ret.b * p.y; return ret;
}

double getcircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen) {
	pnt q1, q2; vec tv;
	vec v1 = p2 - p1, v2 = p3 - p2; q1 = p1 + v1 / 2; q2 = p2 + v2 / 2;
	tv.x = -v1.y; tv.y = v1.x; v1 = tv; tv.x = -v2.y; tv.y = v2.x; v2 = tv;
//	qrintf("v1:%.3f,%.3f v2:%.3f,%.3f\n", v1.x, v1.y, v2.x, v2.y);
	cen = getcrs(getline(q1, v1), getline(q2, v2)); return getdis(p1, cen);
}

bool input()
{
	scanf("%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
	if (p1.x<-eps && p2.x<-eps && p3.x<-eps && p1.y<-eps && p2.y<-eps && p3.y<-eps) return false;
	return true;
}

void conduct()
{
	pnt q1, q2, q3, cen; double ret;
	q1 = p1 + (p2-p1) / 2; q2 = p2 + (p3-p2) / 2; q3 = p3 + (p1-p3) / 2;
//	printf("q1:%.3f,%.3f q2:%.3f,%.3f q3:%.3f,%.3f\n", q1.x, q1.y, q2.x, q2.y, q3.x, q3.y);
	ret = getcircle(q1, q2, q3, cen); printf("%.6f %.6f %.6f\n", cen.x, cen.y, ret);
}

int main()
{
	while (input()) conduct();
	return 0;
}
