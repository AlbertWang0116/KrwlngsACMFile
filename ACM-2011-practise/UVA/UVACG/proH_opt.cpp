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
struct pnt { double x, y; };
typedef pnt vec;
#define N 200010
#define square(x) (x)*(x)
pnt p[N];
int seq[N], tmp[N];
int n;

double getmin(double x, double y) { return x < y ? x : y; }

vec uvec(vec v) {
	double len = sqrt(square(v.x)+square(v.y));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; return ret;
}
vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

int cmp(const int &x, const int &y) {
	if (fabs(p[x].y-p[y].y) < eps) return p[x].x-p[y].x < -eps;
	return p[x].y - p[y].y < -eps;
}

void conduct()
{
	int i, j, k, l, top, bot; double wi, hi, area, pra; vec v1;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	bot = top = 0; tmp[0] = seq[0];
	for (i = 1; i < n; ++i) {
		while (top > bot && submul(getvec(p[tmp[top-1]], p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < eps) --top;
		tmp[++top] = seq[i];
	} bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && submul(getvec(p[tmp[top-1]], p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < eps) --top;
		tmp[++top] = seq[i];
	} n = top; for (i = 0; i <= n; ++i) seq[i] = tmp[i];
	pra = area = inf; 
	for (v1 = uvec(getvec(p[seq[0]], p[seq[1]])), l = 0; nummul(v1, getvec(p[seq[0]], p[seq[(l+n-1)%n]]))-nummul(v1, getvec(p[seq[0]], p[seq[l]])) < eps; l = (l+n-1)%n);
	for (i = j = k = 0; i < n; ++i) {
		v1 = uvec(getvec(p[seq[i]], p[seq[i+1]]));
		while (submul(v1, getvec(p[seq[i]], p[seq[(j+1)%n]]))-submul(v1, getvec(p[seq[i]], p[seq[j]])) > -eps) j = (j+1)%n;
		while (nummul(v1, getvec(p[seq[i]], p[seq[(k+1)%n]]))-nummul(v1, getvec(p[seq[i]], p[seq[k]])) > -eps) k = (k+1)%n;
		while (nummul(v1, getvec(p[seq[i]], p[seq[(l+1)%n]]))-nummul(v1, getvec(p[seq[i]], p[seq[l]])) <  eps) l = (l+1)%n;
		wi = nummul(v1, getvec(p[seq[l]], p[seq[k]])); hi = submul(v1, getvec(p[seq[i]], p[seq[j]]));
		area = getmin(area, wi*hi); pra = getmin(pra, (wi+hi)*2);
	} printf("%.2f %.2f\n", area, pra);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
