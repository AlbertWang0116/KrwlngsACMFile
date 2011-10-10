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
const double eps = 1e-7;
const int MIN = LONG_MIN;
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
	} bool operator<(const pnt &p) const {
		if (fabs(x-p.x)<eps) return y-p.y < -eps;
		return x-p.x < -eps;
	}
};
typedef pnt vec;
#define N 1010
pnt p[N], q[N], r[N], tp[N];
char str[N];
int val[N];
int n, m;
map<pnt, int> pset, qset;

double getmax(double x, double y) { return x > y ? x : y; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double dis2(const pnt &p1, const pnt &p2) { return square(p2.x-p1.x)+square(p2.y-p1.y); }

int getrpt(int n, pnt *p, int m, pnt *q) {
	int i, j, k, mst, tv, ret; double d1, d2; vec v;
	map<pnt, int>::iterator pos; d2 = dis2(q[0], q[1]);
	for (mst = MIN, ret = i = 0; i < n; ++i) for (j = 0; j < n; ++j) if (i != j) {
		v = (vec){ submul(q[1], p[j]-p[i])/d2, nummul(q[1], p[j]-p[i])/d2 };
		for (tv = k = 0; k < m; ++k) {
			tp[k] = (pnt){ p[i].x+submul(q[k], v), p[i].y+nummul(q[k], v) };
//			printf("(%.3f,%.3f)->(%.3f,%.3f), pos=%.3f,%.3f tp=%.3f,%.3f\n", p[i].x, p[i].y, p[j].x, p[j].y, q[k].x, q[k].y, tp[k].x, tp[k].y);
			if ((pos = pset.find(tp[k])) == pset.end()) break; tv += pos->second;
		} if (k < m) continue; ret++;
		if (mst < tv) { mst = tv; for (k = 0; k < m; ++k) r[k] = tp[k]; }
	} return ret;
}

int selfrpt() {
	int i, j, k, ret; double d1, d2; pnt tp; vec v;
	for (qset.clear(), i = 0; i < m; ++i)
		if (qset.find(q[i]) == qset.end()) qset.insert(pair<pnt, int>(q[i], 0));
	map<pnt, int>::iterator pos; d2 = dis2(q[0], q[1]);
	for (ret = i = 0; i < m; ++i) for (j = 0; j < m; ++j) if (i != j) {
		v = (vec){ submul(q[1], q[j]-q[i])/d2, nummul(q[1], q[j]-q[i])/d2 };
		for (k = 0; k < m; ++k) {
			tp = (pnt){ q[i].x+submul(q[k], v), q[i].y+nummul(q[k], v) };
			if (qset.find(tp) == qset.end()) break;
		} if (k < m) continue; ret++;
	} return ret;
}

void conduct()
{
	int i, req, ans, mst, base;
	map<pnt, int>::iterator pos;
	for (i = 0; i < n; ++i) scanf("%lf%lf%d", &p[i].x, &p[i].y, &val[i]);
	scanf("%d", &req);
	for (pset.clear(), i = 0; i < n; ++i)
		if ((pos = pset.find(p[i])) == pset.end()) pset.insert(pair<pnt, int>(p[i], val[i]));
		else pos->second = getmax(pos->second, val[i]);
	while (req--) {
		printf("\n"); scanf("%d%s", &m, str);
		for (i = 0; i < m; ++i) scanf("%lf%lf", &q[i].x, &q[i].y);
		for (i = 1; i < m; ++i) { q[i].x -= q[0].x; q[i].y -= q[0].y; } q[0].x = q[0].y = 0;
		if (m > n) ans = 0;
		else if (m == 1) {
			for (mst = MIN, i = 0; i < n; ++i) if (val[i] > mst) { r[0] = p[i]; mst = val[i]; }
			ans = n;
		} else {
			base = selfrpt(); ans = getrpt(n, p, m, q);
//			printf("ans:%d, base:%d\n", ans, base);
			ans /= base;
		} printf("%s occurs %d time(s) in the map.\n", str, ans);
		if (ans) {
			printf("Brightest occurrence:"); sort(r, r+m);
			for (i = 0; i < m; ++i) printf(" (%d,%d)", (int)floor(r[i].x+eps), (int)floor(r[i].y+eps));
			printf("\n");
		}
	} printf("-----\n");
}

int main()
{
	int time = 0;
	while (scanf("%d", &n) != EOF && n) {
		printf("Map #%d\n", ++time);
		conduct();
	} return 0;
}
