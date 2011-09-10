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
#define N 200010
const double eps = 1e-6, inf = 1e10;
pnt p[N];
int seq[N], ss[N];
int n, m;

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
}

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

int cmpx(const int &x, const int &y) { return p[x].x-p[y].x < -eps; }

int cmpy(const int &x, const int &y) { return p[x].y-p[y].y < -eps; }

double getmin(double x, double y) { return x - y < -eps ? x : y; }

double tradis(int lft, int rit) {
	int mid, i, j, k, l, cnt; double ret, bd;
//	printf("lft:%d rit:%d, m:%d\n", lft, rit, ++m);
	if (rit-lft+1 < 3) return inf;
	mid = (lft+rit) / 2; ret = getmin(tradis(lft, mid), tradis(mid+1, rit)); bd = ret / 2;
//	printf("lft:%d rit:%d\n", lft, rit);
	for (cnt = 0, i = lft; i <= rit; ++i) if (fabs(p[seq[i]].x-p[seq[mid]].x) - bd < eps) ss[cnt++] = seq[i];
	sort(ss, ss+cnt, cmpy);
//	printf("ss:"); for (i = 0; i < cnt; ++i) printf("%d ", ss[i]); printf("\n");
	for (i = j = 0; i < cnt; ++i) {
		for (; j < cnt; ++j) if (p[ss[j]].y-p[ss[i]].y-bd>eps) break; j--;
		for (k = i+1; k <= j; ++k) for (l = k+1; l <= j; ++l) {
//			printf("i:%d j:%d k:%d l:%d\n", i, j, k, l);
			ret = getmin(ret, getdis(p[ss[i]], p[ss[k]])+getdis(p[ss[l]], p[ss[k]])+getdis(p[ss[l]], p[ss[i]]));
		}
	} return ret;
}

void conduct()
{
	int i;
	m = 0;
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmpx);
	printf("%.3f\n", tradis(0, n-1));
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) { input(); conduct(); }
	return 0;
}
