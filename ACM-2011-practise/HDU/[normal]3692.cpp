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

double eps = 1e-9, inf = 1e10;
struct pnt {
	double x, y, z;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x; ret.z = z + p.z;
		ret.y = y + p.y; return ret;
	}
	pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x; ret.z = z - p.z;
		ret.y = y - p.y; return ret;
	}
	pnt operator*(const double &c) const {
		pnt ret; ret.x = x * c; ret.z = z * c;
		ret.y = y * c; return ret;
	}
	pnt operator/(const double &c) const {
		pnt ret; ret.x = x / c; ret.z = z / c;
		ret.y = y / c; return ret;
	}
	bool operator<(const pnt &p) const {
		if (fabs(z-p.z)<eps && fabs(y-p.y)<eps) return x-p.x < -eps;
		if (fabs(z-p.z)<eps) return y-p.y < -eps;
		return z-p.z < -eps;
	}
};
typedef pnt vec;
#define getvec(x, y) ((y)-(x))
#define N 1010
pnt p[N], q[N], ori;
vec ver;
int seq[N], s2[N];
double d;
int n;

vec submul(const vec &v1, const vec &v2) {
	vec ret; ret.x = v1.y*v2.z - v2.y*v1.z; ret.y = v1.z*v2.x - v2.z*v1.x;
	ret.z = v1.x*v2.y - v2.x*v1.y; return ret;
}
double nummul(const vec &v1, const vec &v2) { return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z; }

int cmp(const int &x, const int &y) { return q[x] < q[y]; }

bool input()
{
	int i, tmp;
	scanf("%lf%lf%lf%lf", &ver.x, &ver.y, &ver.z, &d);
	if (fabs(ver.x)<eps && fabs(ver.y)<eps && fabs(ver.z)<eps && fabs(d)<eps) return false;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
	scanf("%lf%lf%lf", &ori.x, &ori.y, &ori.z);
	if (nummul(ori, ver) - d < -eps) { ver.x = -ver.x; ver.y = -ver.y; ver.z = -ver.z; d = -d; }
	tmp = sqrt(nummul(ver, ver)); ver = ver / tmp; d /= tmp; 
	return true;
}

void conduct()
{
	double h1, h2, h3, tmp, ans;
	vec tv;
	int i, top, bot;
	h1 = nummul(ver, ori) - d; h2 = inf; h3 = -inf;
	for (i = 0; i < n; ++i) {
		tmp = nummul(p[i], ver) - d;
		if (h2 > tmp) h2 = tmp; if (h3 < tmp) h3 = tmp;
	} 
	if (!n || h1 - h2 < eps) { printf("0.00\n"); return; }
	if (h1 - h3 < eps) { printf("Infi\n"); return; }
	for (i = 0; i < n; ++i) {
		tv = getvec(ori, p[i]); q[i] = ori + tv * ((d - nummul(ori, ver)) / nummul(tv, ver));
	} for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	s2[0] = seq[0];
	for (top = bot = 0, i = 1; i < n; ++i) {
		while (top > bot && nummul(ver, submul(getvec(q[s2[top-1]], q[s2[top]]), getvec(q[s2[top]], q[seq[i]]))) < eps) --top;
		s2[++top] = seq[i];
	} bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && nummul(ver, submul(getvec(q[s2[top-1]], q[s2[top]]), getvec(q[s2[top]], q[seq[i]]))) < eps) --top;
		s2[++top] = seq[i];
	} for (n = top, i = 0; i <= n; ++i) seq[i] = s2[i];
	for (ans = i = 0; i < n; ++i) ans += nummul(ver, submul(getvec(q[0], q[seq[i]]), getvec(q[0], q[seq[i+1]])));
	printf("%.2f\n", ans/2/sqrt(nummul(ver, ver))+eps);
}

int main()
{
	while (input()) conduct();
	return 0;
}
