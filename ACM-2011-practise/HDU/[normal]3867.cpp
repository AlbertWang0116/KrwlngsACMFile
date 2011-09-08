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
#define getmin(x, y) (x)<(y)?(x):(y)
struct pnt { double x, y; };
struct line { double a, b, c; };
typedef pnt vec;
#define N 10010
const double eps = 1e-8, pi = acos(-1.0);
const pnt p0 = { 0.0, 0.0 }, v0 = { -1.0, 0.0 };
pnt p[N], q[N];
line l[N];
double ang[2*N];
int seq[2*N], hp[N], ati[N];
bool frt[2*N];
int n;

vec getvec(const pnt &p1, const pnt &p2)
{
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

vec uvec(const vec &v)
{
	double len = sqrt(v.x*v.x+v.y*v.y);
	vec ret; ret.x = v.x/len; ret.y = v.y/len; return ret;
}

pnt getcrs(const line &l1, const line &l2)
{
	pnt ret; ret.x = (l1.b*l2.c-l2.b*l1.c) / (l1.b*l2.a-l2.b*l1.a);
	ret.y = (l1.a*l2.c-l2.a*l1.c) / (l1.a*l2.b-l2.a*l1.b); return ret;
}

line getline(const pnt &p1, const pnt &p2)
{
	vec v = getvec(p1, p2); v = uvec(v);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}
line getline(const pnt &p, double ang)
{
	vec v; v.x = cos(ang); v.y = sin(ang);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p.x + ret.b * p.y; return ret;
}

double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x) + square(p2.y-p1.y)); }

void input()
{
	int i; pnt cen;
	scanf("%lf%lf", &cen.x, &cen.y);
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
	for (i = 0; i < n; ++i) { p[i].x -= cen.x; p[i].y -= cen.y; q[i].x -= cen.x; q[i].y -= cen.y;}
}

int cmp(const int &x, const int &y) { 
	if (fabs(ang[x]-ang[y])<eps) return x%2==0;
	return ang[x] - ang[y] < -eps; 
}

int hcmp(const int &x, const int &y, const line &ll)
{
	double val1, val2;
//	if (fabs(ll.a*l[x].b-l[x].a*ll.b) < eps) printf("x[%d] para\n", x);
//	if (fabs(ll.a*l[y].b-l[y].a*ll.b) < eps) printf("y[%d] para\n", y);
	if (fabs(ll.a*l[x].b-l[x].a*ll.b) < eps) val1 = getmin(getdis(p[x], p0), getdis(q[x], p0));
	else val1 = getdis(getcrs(ll, l[x]), p0);
	if (fabs(ll.a*l[y].b-l[y].a*ll.b) < eps) val2 = getmin(getdis(p[y], p0), getdis(q[y], p0));
	else val2 = getdis(getcrs(ll, l[y]), p0);
	if (val1 - val2 > eps) return 1; else if (val1 - val2 < -eps) return -1; return 0;
}

void erase(int idx, const line &agl)
{
	int i, j, ele;
	ati[hp[idx]] = 0; ele = hp[hp[0]]; hp[0]--; if (!hp[0]) return;
	for (i = idx, j = (i << 1); j <= hp[0]; i = j, j = (i << 1)) {
		if (j < hp[0] && hcmp(hp[j], hp[j+1], agl) > 0) ++j;
		if (hcmp(ele, hp[j], agl) > 0) { hp[i] = hp[j]; ati[hp[i]] = i; } else break;
	} hp[i] = ele; ati[hp[i]] = i;
}

void update(int idx, const line &agl)
{
	int i, j, ele = hp[idx];
	for (i = idx, j = (i >> 1); j; i = j, j = (i >> 1))
		if (hcmp(ele, hp[j], agl) < 0) { hp[i] = hp[j]; ati[hp[i]] = i; } else break;
	hp[i] = ele; ati[hp[i]] = i;
}

void conduct()
{
	int i, ans, tag; double cur, ang1, ang2, tmp; pnt ptmp; line agl;
	memset(ati, 0, sizeof(ati)); hp[0] = 0; agl = getline(p0, -pi);
	for (i = 0; i < n; ++i) {
		ang1 = atan2(p[i].y, p[i].x); ang2 = atan2(q[i].y, q[i].x); l[i] = getline(p[i], q[i]);
		if (ang1 - pi > -eps) ang1 = -pi; if (ang2 - pi > -eps) ang2 = -pi;
		if (ang1 - ang2 > eps) { tmp = ang1; ang1 = ang2; ang2 = tmp; }
		if (ang2 - ang1 - pi > eps) { 
			hp[ati[i] = ++hp[0]] = i; update(ati[i], agl); ang[i*2] = ang2; ang[i*2+1] = ang1; 
		} else { ang[i*2] = ang1; ang[i*2+1] = ang2;}
	}
	for (i = 0; i < 2*n; ++i) seq[i] = i; sort(seq, seq+2*n, cmp);
//	printf("seq: "); for (i = 0; i < 2*n; ++i) printf("%5d ", seq[i]); printf("\n");
//	printf("val: "); for (i = 0; i < 2*n; ++i) printf("%.3f ", ang[seq[i]]); printf("\n");
	memset(frt, 0, sizeof(frt)); /*if (hp[0]) frt[hp[1]] = 1;*/
	for (i = 0; i < 2*n; ) {
		for (tag = seq[i]%2, agl = getline(p0, cur = ang[seq[i]]); i < 2*n && ang[seq[i]]-cur < eps && seq[i]%2 == tag; ++i)
			if (seq[i] % 2) erase(ati[seq[i]/2], agl);
			else { hp[ati[seq[i]/2] = ++hp[0]] = seq[i]/2; update(ati[seq[i]/2], agl); }
		if (hp[0]) frt[hp[1]] = 1;
//		printf("heap: "); for (tag = 1; tag <= hp[0]; ++tag) printf("%d ", hp[tag]); printf("\n");
	}
//	for (i = 0; i < n; ++i) if (frt[i]) printf("%d ", i); printf("\n");
	for (ans = i = 0; i < n; ++i) if (frt[i]) ans++; printf("%d\n", ans);
}
				

int main()
{
	while (scanf("%d", &n) != EOF) { input(); conduct(); }
	return 0;
}
