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

const double eps = 1e-6;
#define square(x) (x)*(x)
struct pnt {double x, y; };
typedef pnt vec;
struct line { double a, b, c; };

double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x; ret.y = p2.y - p1.y; return ret;
} vec uvec(vec v) {
	double len = sqrt(square(v.x)+square(v.y));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; return ret;
}

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b); return ret;
}

line getline(const pnt &p, vec v) {
	v = uvec(v); line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p.x + ret.b * p.y; return ret;
}

line getexmid(const pnt &p1, const pnt &p2, const pnt &p3) {
	vec v1, v2, v3;
	v1 = getvec(p1, p2); v2 = getvec(p1, p3); v3 = (vec){ v1.y-v2.y, v2.x-v1.x };
	return getline(p1, v3);
}

void conduct()
{
	pnt pa, pb, pc, ans; line l1, l2;
	scanf("%lf%lf%lf%lf%lf%lf", &pa.x, &pa.y, &pb.x, &pb.y, &pc.x, &pc.y);
	if (fabs(submul(getvec(pa, pb), getvec(pa, pc))) < eps) while(1);
	l1 = getexmid(pa, pb, pc); l2 = getexmid(pb, pc, pa); ans = getcrs(l1, l2);
	printf("%.4f %.4f\n", ans.x+eps, ans.y+eps);
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
