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

#define N 110
long long add, mul, stl, str, edl, edr;
long long blv[N], brv[N], bit[N];
long long ts[N], as[N];
int m;

bool input() {
	scanf("%lld%lld%lld%lld%lld%lld", &add, &mul, &stl, &str, &edl, &edr);
	return mul;
}

void conduct()
{
	int i, j, k, ai; long long ans, lv, rv, tv;
	for (bit[0] = 1, m = i = 0; mul > 1 && stl*bit[i] <= edr; bit[++i] = bit[i-1] * mul) m = i; 
	for (ans = LONG_MAX, i = 0; i <= m; ++i) {
//		printf("i:%d bit:%lld stl*bit:%lld str*bit:%lld\n", i, bit[i], stl*bit[i], str*bit[i]);
		lv = edl-stl*bit[i]; if (lv > 0) lv = (lv-1)/add+1; else lv = 0;
		rv = edr-str*bit[i]; if (rv < 0) break; rv /= add; if (rv < lv) continue; 
		for (j = 0; j < i; ++j) { blv[j] = lv % mul; lv /= mul; } blv[j] = lv;
		for (j = 0; j < i; ++j) { brv[j] = rv % mul; rv /= mul; } brv[j] = rv;
		memset(ts, 0, sizeof(ts));
		for (tv = i, j = i; j >= 0; --j) if (blv[j] == brv[j]) {tv += blv[j]; ts[j] = blv[j]; } else break;
		for (k = j-1; k >= 0; --k) if (blv[k]) break; 
		if (k >= 0) { tv += blv[j]+1; ts[j] = blv[j]+1; } else { tv += blv[j]; ts[j] = blv[j]; }
		if (tv < ans) { ans = tv; ai = i; for (j = 0; j <= i; ++j) as[j] = ts[j]; }
	} if (!ans) printf(" empty\n");
	else if (ans == LONG_MAX) printf(" impossible\n");
	else {
		for (i = ai; i >= 0; --i) {
			if (as[i]) printf(" %lldA", as[i]);
			for (j = 1; i > 0 && !as[i-1]; --i) ++j;
			if (!i) --j; if (j) printf(" %dM", j);
		} printf("\n");
	}
}

int main()
{
	int time = 0;
	while (input()) {
		printf("Case %d:", ++time);
		conduct();
	} return 0;
}
