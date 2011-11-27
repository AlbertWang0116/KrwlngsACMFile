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
const double eps = 1e-7, inf = 1e5, pi = acos(-1.0);
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
struct line { double a, b, c; };
line bdr1 = { 1.0, 0.0, -inf }, bdr2 = { -1.0, 0.0, -inf }, bdr3 = { 0.0, 1.0, -inf }, bdr4 = { 0.0, -1.0, -inf };
#define N 1010
pnt p[N];
line l[N];
int seq[N];
double ang[N];
int n;

double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }

vec uvec(vec v) {
	double len = sqrt(square(v.x)+square(v.y));
	return v / len;
}

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b); 
	return ret;
}

line getline(const pnt &p1, const pnt &p2) {
	vec v = uvec(p2-p1);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = p1.x * ret.a + p1.y * ret.b; return ret;
}

int hfpcmp(const int &x, const int &y) {
	if (fabs(ang[x]-ang[y])<eps) return l[x].c - l[y].c > eps;
	return ang[x] - ang[y] < -eps;
}

int hfplane(int n, line *l, pnt *p, int *seq, double *ang)
{
	int i, j, top, bot, ret;
	l[n++] = bdr1; l[n++] = bdr2; l[n++] = bdr3; l[n++] = bdr4;
	for (i = 0; i < n; ++i) { ang[i] = atan2(l[i].b, l[i].a); if (fabs(ang[i]-pi)<eps) ang[i] = -pi; }
	for (i = 0; i < n; ++i) seq[i] = i; std::sort(seq, seq+n, hfpcmp);
	for (i = j = 1; i < n; ++i) if (fabs(ang[seq[i]]-ang[seq[j-1]])>eps) seq[j++] = seq[i]; n = j;
	for (i = 1, top = bot = 0; i < n; ++i) {
		while (top - bot && oridis(l[seq[i]], p[top]) < -eps) --top;
		if (ang[seq[i]] > -eps && top == bot) return 0;
		p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		if (ang[seq[i]] > -eps) break;
	} p[bot] = (pnt){ -inf*2, -inf*2 };
	for (++i; i < n; ++i) {
		if (oridis(l[seq[i]], p[bot]) > -eps) continue;
		while (top - bot && oridis(l[seq[i]], p[top]) < -eps) --top;
		if (top == bot) return 0; p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		while (oridis(l[seq[top]], p[bot+1]) < -eps) ++bot; p[bot] = getcrs(l[seq[top]], l[seq[bot]]);
	} for (ret = 0, i = bot; i < top; ++i) if (fabs(p[i].x-p[i+1].x)>eps || fabs(p[i].y-p[i+1].y)>eps) {
		seq[ret] = seq[i]; p[ret] = p[i]; ret++;
	} if (!ret || fabs(p[i].x-p[0].x)>eps || fabs(p[i].y-p[0].y)>eps) {
		seq[ret] = seq[i]; p[ret] = p[i]; ret++;
	} p[ret] = p[0]; return ret;
}

void conduct() {
	int i, ans; double ret; pnt tmp;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y); p[n] = p[0];
	for (ret = i = 0; i < n; ++i) ret += submul(p[i], p[i+1]);
	if (ret < -eps) {
		for (i = 0; i < n/2; ++i) { tmp = p[i]; p[i] = p[n-i-1]; p[n-i-1] = tmp; }
		p[n] = p[0];
	} for (i = 0; i < n; ++i) l[i] = getline(p[i], p[i+1]);
	ans = hfplane(n, l, p, seq, ang); if (ans) printf("YES\n"); else printf("NO\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
