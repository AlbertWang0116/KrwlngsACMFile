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
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(double c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(double c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
struct line { double a, b, c; };
int tot, dlt1, dlt2;
const double pi = acos(-1.0);
const pnt ori = { 0.0, 0.0 };

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }

pnt rotate(const pnt &p, double ang) {
	vec v = { sin(ang), cos(ang) };
	pnt ret = { submul(p, v), nummul(p, v) }; return ret;
}

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b); return ret;
}

vec uvec(const vec &v) {
	double len = sqrt(nummul(v, v));
	return v / len;
}

line getmidver(const pnt &p1, const pnt &p2) {
	pnt p = (p1+p2) / 2.0; vec v = uvec(p2-p1);
	line ret; ret.a = v.x; ret.b = v.y; ret.c = nummul(p, v); return ret;
}

double outcircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen) {
	line l1 = getmidver(p1, p2), l2 = getmidver(p2, p3);
	cen = getcrs(l1, l2); 
	return getdis(cen, p1);
}

void conduct() {
	pnt p1, p2, p3, cen;
	scanf("%lf%lf", &p1.x, &p1.y);
	scanf("%lf%lf", &p2.x, &p2.y); p2 = rotate(p2, (double)dlt1/(double)tot*2.0*pi*-1.0);
	scanf("%lf%lf", &p3.x, &p3.y); p3 = rotate(p3, (double)(dlt1+dlt2)/(double)tot*2.0*pi*-1.0);
	outcircle(p1, p2, p3, cen); printf("%.0f\n", getdis(cen, ori));
}

int main() {
	while (scanf("%d%d%d", &tot, &dlt1, &dlt2) != EOF && (tot||dlt1||dlt2)) conduct();
	return 0;
}
