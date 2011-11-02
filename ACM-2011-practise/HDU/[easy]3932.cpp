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
struct line { double a, b, c ; };
#define N 1010
pnt p[N];
int seq[N], tmp[N];
int n, X, Y;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double nummul(const vec &v1, const vec &v2) { return v1.x*v2.x + v1.y*v2.y; }

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
	return v / len;
}

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b*l2.c-l2.b*l1.c) / (l1.b*l2.a-l2.b*l1.a);
	ret.y = (l1.a*l2.c-l2.a*l1.c) / (l1.a*l2.b - l2.a*l1.b); return ret;
}

line getmidver(const pnt &p1, const pnt &p2) {
	pnt p = (p1+p2) / 2.0; vec v = uvec(p2-p1);
	line ret = { v.x, v.y, nummul(p, v) }; return ret;
}

double outcircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen) {
	line l1 = getmidver(p1, p2), l2 = getmidver(p2, p3);
	cen = getcrs(l1, l2); return getdis(cen, p1);
}

double enclosng_circle(int n, pnt *p, pnt &cen) {
	int i, j, k, l; double rad;
	for (i = 0; i < n; ++i) seq[i] = i; cen = p[0]; rad = 0.0;
	for (i = 2; i < n; ++i) {
		j = rand()%(n-i) + i; k = seq[j]; seq[j] = seq[i]; seq[i] = k;
		if (getdis(cen, p[seq[i]])-rad < eps) continue;
		tmp[0] = seq[i]; tmp[1] = seq[1]; seq[i] = seq[0];	
		cen = (p[tmp[0]]+p[tmp[1]]) / 2.0; rad = getdis(cen, p[tmp[0]]);
		for (j = 2; j <= i; ++j) {
			if (getdis(cen, p[seq[j]])-rad < eps) { tmp[j] = seq[j]; continue; }
			tmp[j] = tmp[1]; tmp[1] = seq[j]; 
			cen = (p[tmp[0]]+p[tmp[1]]) / 2.0; rad = getdis(cen, p[tmp[0]]);
			for (k = 2; k <= j; ++k) if (getdis(cen, p[tmp[k]])-rad > eps) {
				l = tmp[k]; tmp[k] = tmp[2]; tmp[2] = l;
				rad = outcircle(p[tmp[0]], p[tmp[1]], p[tmp[2]], cen);
			} 
		} for (j = 0; j <= i; ++j) seq[j] = tmp[j];
	} return rad;
}

void conduct()
{
	pnt cen; int i;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	double ans = enclosng_circle(n, p, cen);
	printf("(%.1f,%.1f).\n%.1f\n", cen.x, cen.y, ans);
}


int main()
{
	while (scanf("%d%d%d", &X, &Y, &n) != EOF) conduct();
	return 0;
}
