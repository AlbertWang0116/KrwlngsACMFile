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

long long a, b, c, bit[33];
int k;

long long k1, k2;
long long extgcd(long long x, long long y) {
	long long ret, tmp;
	if (!y) { k1 = 1; k2 = 0; return x; }
	ret = extgcd(y, x%y);
	tmp = k1-x/y*k2; k1 = k2; k2 = tmp; return ret;
}

long long extoclean(long long x, long long y, long long z) {
	long long ret = extgcd(x, y); long long ans;
	if (z%ret) return -1;
	ans = ((long long)(z/ret)*k1%(y/ret));
	if (ans < 0) ans += y/ret; return ans;
}

void conduct() {
	long long ans;
	b -= a; if (b < 0) b += bit[k];
	ans = extoclean(c, bit[k], b);
	if (ans < 0) printf("FOREVER\n"); else printf("%lld\n", ans);
}

int main() {
	int i;
	for (i = bit[0] = 1; i < 33; ++i) bit[i] = bit[i-1] * 2;
	while (cin >> a >> b >> c >> k && (a|b|c|k)) conduct();
	return 0;
}
