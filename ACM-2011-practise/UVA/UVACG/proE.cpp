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
const double eps = 1e-8, pi = acos(-1.0);
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
	bool operator<(const pnt &p) const {
		if (fabs(x-p.x)<eps) return y-p.y < -eps;
		return x-p.x < -eps;
	}
};
typedef pnt vec;
struct line { double a, b, c; };
char cmd[100];

double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double getdis(const line &l, const pnt &p) { return fabs(l.a*p.x+l.b*p.y-l.c)/(square(l.a)+square(l.b)); }
double getmin(const double x, const double y) { return x < y ? x : y; }
double getmax(const double x, const double y) { return x > y ? x : y; }

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y)); return v / len;
}

line getlinev(const pnt &p, const vec &v)
{
	vec vv = uvec(v);
	line ret; ret.a = -vv.y; ret.b = vv.x;
	ret.c = ret.a * p.x + ret.b * p.y; 
	return ret;
}
line getline(const pnt &p1, const pnt &p2)
{
	vec v = uvec(p2-p1);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b*l2.c - l2.b*l1.c) / (l1.b*l2.a - l2.b*l1.a);
	ret.y = (l1.a*l2.c - l2.a*l1.c) / (l1.a*l2.b - l2.a*l1.b); return ret;
}

double outcircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen) {
	pnt q1, q2;
	vec v1 = p2-p1, v2 = p3-p2; q1 = p1 + v1/2; q2 = p2 + v2/2;
	v1 = (vec){ -v1.y, v1.x }; v2 = (vec){ -v2.y, v2.x };
	cen = getcrs(getlinev(q1, v1), getlinev(q2, v2)); return getdis(cen, p1);
}

double incircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen) {
	vec v1, v2; line l1, l2;
	v1 = uvec(p2-p1); v2 = uvec(p3-p1); l1 = getlinev(p1, v1+v2);
	v1 = uvec(p3-p2); v2 = uvec(p1-p2); l2 = getlinev(p2, v1+v2);
	cen = getcrs(l1, l2); l1 = getline(p1, p2); return getdis(l1, cen);
}

void input()
{
	pnt p1, p2, p3, p4, cen; double ret, dis1, dis2, dis3, ang1, ang2, ang3, ang4, rad;
	line l1, l2, l3; vec v1, v2, v3;
	if (!strcmp(cmd, "CircumscribedCircle")) {
		scanf("%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
		ret = outcircle(p1, p2, p3, cen); printf("(%.6f,%.6f,%.6f)\n", cen.x+eps, cen.y+eps, ret+eps);
	} else if (!strcmp(cmd, "InscribedCircle")) {
		scanf("%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
		ret = incircle(p1, p2, p3, cen); printf("(%.6f,%.6f,%.6f)\n", cen.x+eps, cen.y+eps, ret+eps);
	} else if (!strcmp(cmd, "TangentLineThroughPoint")) {
		scanf("%lf%lf%lf%lf%lf", &cen.x, &cen.y, &rad, &p1.x, &p1.y);
		printf("["); dis1 = getdis(p1, cen); ang1 = atan2(cen.y-p1.y, cen.x-p1.x);
		if (dis1 - rad > eps) {
			ang2 = asin(rad/dis1);
			ang3 = ang1 + ang2; while (ang3 - pi > -eps) ang3 -= pi; while (ang3 < -eps) ang3 += pi;
			ang4 = ang1 - ang2; while (ang4 - pi > -eps) ang4 -= pi; while (ang4 < -eps) ang4 += pi;
			printf("%.6f,%.6f", getmin(ang3, ang4)/pi*180+eps, getmax(ang3, ang4)/pi*180+eps);
		} else if (fabs(dis1-rad)<eps) {
			ang3 = ang1 + pi/2; while (ang3 - pi > -eps) ang3 -= pi; while (ang3 < -eps) ang3 += pi; printf("%.6f", ang3/pi*180+eps);
		} printf("]\n");
	} else if (!strcmp(cmd, "CircleThroughAPointAndTangentToALineWithRadius")) {
		scanf("%lf%lf%lf%lf%lf%lf%lf", &cen.x, &cen.y, &p1.x, &p1.y, &p2.x, &p2.y, &rad);
		l1 = getline(p1, p2); v1 = (vec){ p2.x-p1.x, p2.y-p1.y }; v1 = uvec(v1); v2 = (vec){ -v1.y, v1.x };
		dis1 = oridis(l1, cen); dis2 = fabs(dis1); printf("["); 
		if (dis2 - 2*rad < -eps && dis2 > eps) {
			dis3 = sqrt(square(rad)-square(rad-dis2));
			p3 = cen + v2 * (rad-dis2)*(dis1/dis2) + v1 * dis3; p4 = cen + v2 * (rad-dis2)/(dis1/dis2) - v1 * dis3;
			if (p3 < p4) printf("(%.6f,%.6f),(%.6f,%.6f)", p3.x+eps, p3.y+eps, p4.x+eps, p4.y+eps); 
			else printf("(%.6f,%.6f),(%.6f,%.6f)", p4.x+eps, p4.y+eps, p3.x+eps, p3.y+eps);
		} else if (fabs(dis1) < eps) {
			p3 = cen + v2 * rad; p4 = cen - v2 * rad;
			if (p3 < p4) printf("(%.6f,%.6f),(%.6f,%.6f)", p3.x+eps, p3.y+eps, p4.x+eps, p4.y+eps); 
			else printf("(%.6f,%.6f),(%.6f,%.6f)", p4.x+eps, p4.y+eps, p3.x+eps, p3.y+eps);
		} else if (fabs(dis2-2*rad) < eps) {
			p3 = cen + v2 * (rad-dis2)*(dis1/dis2); printf("(%.6f,%.6f)", p3.x, p3.y);
		} printf("]\n");
	}

}

int main()
{
	while (scanf("%s", cmd) != EOF) input();
	return 0;
}
