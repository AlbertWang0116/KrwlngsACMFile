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
	long long x, y; 
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
struct line { long long a, b, c; };
typedef pnt vec;
#define N 100010
pnt p[N];
int pre[N], pro[N], ati[N], pos[N];
bool vst[N]; line ll[N];
int n;

line getline(const pnt &p1, const pnt &p2) {
	pnt p = (p1 + p2) / 2; vec v = p1 - p2;
	line ret; ret.a = v.x; ret.b = v.y;
	ret.c = ret.a * p.x + ret.b * p.y; return ret;
}

long long submul(const vec &v1, const vec &v2) { return v1.x*v2.y - v2.x*v1.y; }
long long oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }
long long dis2(const pnt &p1, const pnt &p2) { return square(p2.y-p1.y)+square(p2.x-p1.x); }

void farestpair(int n, pnt *p, int *ati) {
	int i, j, k, l, st, ed;
	for (i = 0; i < n; ++i) { p[i].x *= 2; p[i].y *= 2; }
	for (i = 0; i < n; ++i) { pre[i] = i-1; pro[i] = i+1; } pre[0] = n-1; pro[n-1] = 0;
	for (i = 0; i < n; ++i) p[i+n] = p[i+2*n] = p[i];
	for (l = st = i = 0; l <= n; i = pro[i], ++l) {
		ll[i] = getline(p[i], p[pro[i]]);
		while ((i != st || l == n) && submul(p[pro[i]]-p[i], p[pos[pre[i]]]-p[i]) >= 0 && oridis(ll[i], p[pos[pre[i]]])+(l!=n-1?0:1) > 0) {	//h-l-1:a?b:c
			if (l == n && i == st) { st = pro[i]; l = n-1; }
			pro[pre[i]] = pro[i]; pre[pro[i]] = pre[i]; i = pre[i];
			ll[i] = getline(p[i], p[pro[i]]);
		} if (i == st && l != n) ed = pro[i]; else ed = pos[pre[i]];
		while (submul(p[pro[i]]-p[i], p[ed]-p[i]) < 0 || oridis(ll[i], p[ed])-(l!=n-1?1:0) < 0) ++ed; pos[i] = ed;				//h-l-1:a?b:c
	} memset(vst, 0, sizeof(vst));
	for (i = st; !vst[i]; i = pro[i]) {
		j = pos[i]; k = pos[pro[i]]; vst[i] = 1; while (k < j) k += n;
		for (l = j; l < k; ++l) ati[l%n] = pro[i];
	}
}

void conduct()
{
	int i, j, k, l, st, ed; long long val;
	for (i = 0; i < n; ++i) scanf("%lld%lld", &p[i].x, &p[i].y);
	farestpair(n, p, ati);
	for (i = 0; i < n; ++i) printf("%d\n", ati[i]+1);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
