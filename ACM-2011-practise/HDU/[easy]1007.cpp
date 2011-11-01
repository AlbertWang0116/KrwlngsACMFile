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
const double eps = 1e-9, inf = 1e20;
struct pnt { double x, y; };
#define N 100010
pnt p[N];
int seq[N], que[N];
int n;

double getmin(double x, double y) { return x < y ? x : y; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

int cmpx(const int &i, const int &j) {
	if (fabs(p[i].x-p[j].x)<eps) return p[i].y-p[j].y < -eps;
	return p[i].x-p[j].x < -eps;
}
int cmpy(const int &i, const int &j) {
	if (fabs(p[i].y-p[j].y)<eps) return p[i].x-p[j].x < -eps;
	return p[i].y-p[j].y < -eps;
}

double lstpair(pnt *p, int lft, int rit) {
	int i, j, cnt, mid; double ret;
	if (lft >= rit) return inf;
	mid = (lft+rit) / 2; ret = getmin(lstpair(p, lft, mid), lstpair(p, mid+1, rit));
	for (cnt = 0, i = lft; i <= rit; ++i) if (fabs(p[seq[i]].x-p[seq[mid]].x)-ret<eps) que[cnt++] = seq[i];
	sort(que, que+cnt, cmpy);
	for (i = 0; i < cnt; ++i) for (j = i+1; j < cnt && j < i+8; ++j) ret = getmin(ret, getdis(p[que[i]], p[que[j]]));
	return ret;
}

double nrstpair(int n, pnt *p) {
	for (int i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmpx);
	return lstpair(p, 0, n-1);
}

void conduct()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	printf("%.2f\n", nrstpair(n, p)/2.0);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
