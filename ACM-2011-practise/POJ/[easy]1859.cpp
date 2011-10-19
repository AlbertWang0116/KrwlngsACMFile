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

const double eps = 1e-9;
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
	} bool operator<(const pnt &p) const {
		if (fabs(x-p.x)<eps) return y-p.y < -eps;
		return x-p.x < -eps;
	}
};
typedef pnt vec;
#define N 20010
pnt p[N];
int seq[N], tmp[N];
int n;
map<pnt, int> gd;

double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

int cmp(const int &i, const int &j) { return p[i] < p[j]; }

pnt barycenter(int n) {
	double tot = 0, tx = 0, ty = 0, area; int i;
	for (i = 0; i < n; ++i) {
		area = submul(p[seq[i]], p[seq[i+1]]);
		tx += (p[seq[i]].x+p[seq[i+1]].x) / 3 * area;
		ty += (p[seq[i]].y+p[seq[i+1]].y) / 3 * area;
		tot += area;
	} pnt ret = { tx, ty }; return ret / tot;
}

void conduct()
{
	int i, top, bot, m; pnt cen, tp;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	if (n % 2) cen = p[seq[n/2]]; else cen = (p[seq[n/2-1]]+p[seq[n/2]]) / 2;
	for (i = 0; i < n/2; ++i) {
		tp = (p[seq[i]] + p[seq[n-i-1]]) / 2;
		if (fabs(tp.x-cen.x) > eps || fabs(tp.y-cen.y) > eps) break;
	} if (i < n/2) printf("This is a dangerous situation!\n");
	else printf("V.I.P. should stay at (%.1f,%.1f).\n", cen.x, cen.y);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
