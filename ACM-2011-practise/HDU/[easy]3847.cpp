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

struct pnt { double x, y; };
typedef pnt vec;
#define square(x) (x)*(x)
#define N 110
const double inf = 1e10, eps = 1e-9;
int seq[N], tmp[N];
pnt p[N];
int n;

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
}

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double getmin(double x, double y) { return x-y<-eps?x:y; }

int cmp(const int &x, const int &y) {
	if (fabs(p[x].y-p[y].y)<eps) return p[x].x-p[y].x < -eps;
	return p[x].y-p[y].y < -eps;
}

void conduct()
{
	int i, j, bot, top;
	double ans, val1, val2, bot1, bot2, top1, top2, t;
	vec hor, ver;
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	for (tmp[top = bot = 0] = seq[0], i = 1; i < n; ++i) {
		while (top > bot && submul(getvec(p[tmp[top-1]], p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < eps) --top;
		tmp[++top] = seq[i];
	} bot = top;
	for (i = n-2; i >= 0; --i)  {
		while (top > bot && submul(getvec(p[tmp[top-1]], p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < eps) --top;
		tmp[++top] = seq[i];
	} n = top;
	for (i = 0; i <= n; ++i) seq[i] = tmp[i]; ans = inf;
	for (i = 0, j = 1; i < n; ++i) {
		hor = getvec(p[seq[i]], p[seq[i+1]]); ver.x = -hor.y; ver.y = hor.x;
		while ((val1 = submul(hor, getvec(p[seq[i]], p[seq[j]]))) - (val2 = submul(hor, getvec(p[seq[i]], p[seq[j+1]]))) < -eps) j = (j+1) % n;
//		printf("i:%d j:%d n:%d\n", i, j, n);
//		bot1 = nummul(hor, p[seq[i]]); bot2 = nummul(hor, p[seq[i+1]]); if (bot1 - bot2 > eps) { t = bot1; bot1 = bot2; bot2 = t; }
//		top1 = nummul(hor, p[seq[j]]); top2 = nummul(hor, p[seq[j+1]]); if (top1 - top2 > eps) { t = top1; top1 = top2; top2 = t; }
//		if (fabs(val1-val2)<eps && (bot1 - top2 > eps || top1 - bot2 > eps))
//			ans = getmin(ans, getmin(getdis(p[seq[i]], p[seq[j]]), getdis(p[seq[i+1]], p[seq[j+1]])));
//		else ans = getmin(ans, val1 / getdis(p[seq[i]], p[seq[i+1]]));
		ans = getmin(ans, val1 / getdis(p[seq[i]], p[seq[i+1]]));
	} printf("%.2f\n", ans+0.005);
}

int main()
{
	int time = 0;
	while (scanf("%d", &n) != EOF && n) { printf("Case %d: ", ++time); input(); conduct(); }
	return 0;
}
