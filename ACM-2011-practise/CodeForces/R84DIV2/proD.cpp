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

#define N 10010
long long val[N];
int n, m;
const double eps = 1e-13;

int find(int v) {
	for (int i = 0; ; ++i) if (val[i] > v) return i;
}
int find2(int v) {
	for (int i = 0; ; ++i) if (val[i] >= v) return i;
}

void init()
{
	int i, j;
	val[0] = 0;
	for (i = j = 0; ; ++i) {
		val[++j] = val[i] * 10 + 4; val[++j] = val[i] * 10 + 7;
		if (val[j] > LONG_MAX) break;
	} m = j;
}

int main()
{
	long long vst, ved, ust, ued, cnt, cr, cl; int i, k, ul, ur, vl, vr;
	double ans;
	init();
	cin >> vst >> ved >> ust >> ued >> k;
	i = find(vst); n = find(ved); ul = find2(ust); ur = find2(ued);
	for (ans = 0.0; i <= n; ++i) {
		if (i-k >= ul && i-k <= ur) cl = min(val[i-k], ued)-max(val[i-k-1], ust-1); else continue;
		ans += (double)(min(val[i], ved+1) - max(val[i-1], vst)) * (double)cl / ((double)(ved-vst+1) * (double)(ued-ust+1));
//		printf("i:%d cl:%lld ans:%.6f\n", i, cl, ans);
	} i = find2(vst); n = find2(ved); ul = find(ust); ur = find(ued);
	for (; i <= n; ++i) {
		if (i+k <= ur && i+k >= ul) cr = min(val[i+k], ued+1)-max(val[i+k-1], ust); else continue;
		ans += (double)(min(val[i], ved) - max(val[i-1], vst-1)) * (double)cr / ((double)(ved-vst+1) * (double)(ued-ust+1));
//		printf("i:%d cr:%lld ans:%.6f\n", i, cr, ans);
	} vl = find2(vst); vr = find(ved); ul = find2(ust); ur = find(ued);
	if (k > 1 || ul >= vr || vl >= ur) ; else {
		vl = max(vl, ul); vr = min(vr, ur);
		if (vr-vl > 0) ans -= (double)(vr-vl) / ((double)(ved-vst+1) * (double)(ued-ust+1));
	} printf("%.12f\n", ans);
}
	
