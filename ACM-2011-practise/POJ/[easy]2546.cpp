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
const double eps = 1e-7, pi = acos(-1.0);
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
	}
};
typedef pnt vec;
pnt p1, p2;
double r1, r2;

double getang(double a, double b, double c) { return acos((a*a+b*b-c*c)/(2*a*b)); }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

void conduct() {
	double dis, ang1, ang2, ans;
	vec v1, v2;
	scanf("%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &r1, &p2.x, &p2.y, &r2);
	dis = getdis(p1, p2); if (dis-r1-r2>-eps) { printf("0.000\n"); return; }
	if (r2-r1-dis > -eps) { printf("%.3f\n", pi*r1*r1); return; }
	else if (r1-r2-dis > -eps) { printf("%.3f\n", pi*r2*r2); return; }
	ang1 = getang(r1, dis, r2); ang2 = atan2(p2.y-p1.y, p2.x-p1.x);
	v1 = (vec){ cos(ang2-ang1), sin(ang2-ang1) }; v2 = (vec){ cos(ang2+ang1), sin(ang2+ang1) };
	ans = ang1 * r1 * r1 - submul(v1, v2) * r1 * r1/ 2.0;
	ang1 = getang(r2, dis, r1); ang2 = atan2(p1.y-p2.y, p1.x-p2.x);
	v1 = (vec){ cos(ang2-ang1), sin(ang2-ang1) }; v2 = (vec){ cos(ang2+ang1), sin(ang2+ang1) };
	ans += ang1 * r2 * r2 - submul(v1, v2) * r2 * r2/ 2.0;
	printf("%.3f\n", ans);
}

int main() {
	conduct();
	return 0;
}
