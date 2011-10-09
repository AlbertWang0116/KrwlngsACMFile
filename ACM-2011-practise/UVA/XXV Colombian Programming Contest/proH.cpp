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
#define N 10010
int seq[N], que[N];
double lft[N], rit[N], val[N];
pnt p[N], q[N];
bool vst[N];
int n;
const double eps = 1e-9, pi = acos(-1.0);

int cmp(const int &x, const int &y) { 
	if (fabs(val[x]-val[y])<eps) return (x%2 == 0);
	return val[x]-val[y] < -eps; 
}

void conduct()
{
	int i, j, ans; double tmp;
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
	for (i = 0; i < n; ++i) {
		lft[i] = atan2(p[i].y, p[i].x); rit[i] = atan2(q[i].y, q[i].x);
		if (lft[i]+pi < eps) lft[i] = pi; if (rit[i]+pi < eps) rit[i] = pi;
		if (lft[i] > rit[i]) { tmp = lft[i]; lft[i] = rit[i]; rit[i] = tmp; }
	} for (i = 0; i < n; ++i) { val[i*2] = lft[i]; val[i*2+1] = rit[i]; }
	for (i = 0; i < 2*n; ++i) seq[i] = i; sort(seq, seq+2*n, cmp);
	memset(vst, 0, sizeof(vst)); que[0] = 0;
	for (ans = i = 0; i < 2*n; ++i)
		if (seq[i] % 2 && !vst[seq[i]/2]) {
			ans++; for (j = 1; j <= que[0]; ++j) vst[que[j]] = 1; que[0] = 0;
		} else que[++que[0]] = seq[i] / 2;
	printf("%d\n", ans);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
