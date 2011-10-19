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

const double eps = 1e-9, inf = 1e20;
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
#define N 1010
pnt p[N];
int n, m;

double submul(const vec &v1, const vec &v2) { return v1.x*v2.y - v2.x*v1.y; }
double nummul(const vec &v1, const vec &v2) { return v1.x*v2.x + v1.y*v2.y; }

bool pntinpoly(int n, pnt *p, const pnt &p1) {
	int i, cnt; pnt p2 = { -inf, p1.y }; p[n] = p[0];
	for (cnt = i = 0; i < n; ++i) {
		if (fabs(submul(p[i+1]-p1, p[i]-p1))<eps && nummul(p[i+1]-p1, p[i]-p1)<eps) return true;
		if (fabs(p[i+1].y-p[i].y)<eps) continue;
		if (fabs(p[i+1].y-p1.y)<eps && p[i+1].x-p1.x<eps) { if (p[i+1].y-p[i].y<eps) cnt++; continue; }
		if (fabs(p[i].y-p1.y) < eps && p[i].x-p1.x < eps) { if (p[i].y-p[i+1].y<eps) cnt++; continue; }
		if (submul(p2-p1, p[i]-p1)*submul(p2-p1, p[i+1]-p1)<eps &&
			submul(p[i+1]-p[i], p1-p[i])*submul(p[i+1]-p[i], p2-p[i])<eps) cnt++;
	} return cnt % 2;
}

void conduct()
{
	int i; pnt q;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	while (m--) {
		scanf("%lf%lf", &q.x, &q.y);
		if (pntinpoly(n, p, q)) printf("Within\n"); else printf("Outside\n");
	}
}

int main()
{
	int time = 0;
	while (scanf("%d", &n) != EOF && n) {
		if (time) printf("\n");
		scanf("%d", &m); printf("Problem %d:\n", ++time);
		conduct();
	} return 0;
}
