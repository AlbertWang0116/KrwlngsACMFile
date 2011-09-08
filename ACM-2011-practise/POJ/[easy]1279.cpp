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
struct pnt { double x, y; };
struct line { double a, b, c; };
typedef pnt vec;
#define N 2010
const double inf = 1e6;
const double eps = 1e-6;
const double pi = acos(-1.0);
pnt p[N];
line l[N], l1 = { -1.0, 0.0, -inf }, l2 = { 1.0, 0.0, -inf }, l3 = { 0.0, 1.0, -inf }, l4 = { 0.0, -1.0, -inf };
int seq[N];
double ang[N];
int n;

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
}

vec uvec(const vec &v)
{
	double len = sqrt(square(v.x) + square(v.y));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; return ret;
}

vec getvec(const pnt &p1, const pnt &p2)
{
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

line getline(const pnt &p1, const pnt &p2)
{
	vec v = getvec(p1, p2); v = uvec(v);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}

pnt getcrs(const line &l1, const line &l2)
{
	pnt ret; ret.x = (l1.b*l2.c - l2.b*l1.c) / (l1.b*l2.a - l2.b*l1.a);
	ret.y = (l1.a*l2.c - l2.a*l1.c) / (l1.a*l2.b - l2.a*l1.b); return ret;
}

double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

int cmp(const int &x, const int &y)
{
	if (fabs(ang[x]-ang[y]) < eps) return l[x].c > l[y].c;
	return ang[x] < ang[y];
}

void conduct()
{
	int i, j, top, bot;
	double ans; pnt tmp;
	p[n] = p[0]; for (ans = i = 0; i < n; ++i) ans += submul(p[i], p[i+1]);
	if (ans < -eps) for (i = 0; i < n / 2; ++i) { tmp = p[i]; p[i] = p[n-i-1]; p[n-i-1] = tmp; }
//	for (i = 0; i < n; ++i) printf("p[%d]:x=%.3f,y=%.3f\n", i, p[i].x, p[i].y);
	for (p[n] = p[i = 0]; i < n; ++i) l[i] = getline(p[i], p[i+1]);
	l[n++] = l1; l[n++] = l2; l[n++] = l3; l[n++] = l4;
//	for (i = 0; i < n; ++i) printf("l[%d]:a=%.3f,b=%.3f,c=%.3f\n", i, l[i].a, l[i].b, l[i].c);
	for (i = 0; i < n; ++i) ang[i] = atan2(l[i].b, l[i].a);
	for (i = 0; i < n; ++i) if (fabs(ang[i]-pi)<eps) ang[i] = -pi;
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
//	for (i = 0; i < n; ++i) printf("seq[%d]=%d\n", i, seq[i]);
	for (i = j = 1; i < n; ++i) if (fabs(ang[seq[i]] - ang[seq[j-1]]) > eps) seq[j++] = seq[i]; n = j;
//	for (i = 0; i < n; ++i) printf("seq[%d]=%d\n", i, seq[i]);
	for (i = 1, top = bot = 0; i < n; ++i) {
//		printf("seq[%d]=%d l:a:%.3f,b:%.3f,c:%.3f p-top:x:%.3f,y:%.3f\n", i, seq[i], l[seq[i]].a, l[seq[i]].b, l[seq[i]].c, p[top].x, p[top].y);
		while (top - bot && oridis(l[seq[i]], p[top]) < -eps) --top;
		p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		if (ang[seq[i]] > eps) break;
	} p[bot] = getcrs(l[seq[top]], l[seq[bot]]);
//	for (j = bot; j <= top; ++j) printf("cvx[%d]=%d\n", j, seq[j]);
	for (++i; i < n; ++i) {
		if (oridis(l[seq[i]], p[bot]) > -eps) continue;
		while (top - bot && oridis(l[seq[i]], p[top]) < -eps) --top;
		if (top == bot) break; p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		while (oridis(l[seq[top]], p[bot+1]) < -eps) ++bot; p[bot] = getcrs(l[seq[top]], l[seq[bot]]);
	}
	if (i < n) { printf("0.00\n"); return; }
	for (ans = 0, i = bot; i < top; ++i) ans += submul(p[i], p[i+1]); ans += submul(p[top], p[bot]);
	printf("%.2f\n", ans/2);
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) { input(); conduct(); }
	return 0;
}
