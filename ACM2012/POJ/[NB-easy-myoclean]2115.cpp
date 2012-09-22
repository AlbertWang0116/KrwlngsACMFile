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

long long bit[33];
long long a, b, c;
int k;

long long mygcd(long long x, long long y, long long z) {
	long long ret;
	if (!(z%x)) return z/x; if (x == y) return -1;
	ret = mygcd(x-y%x, x, z%x);
	if (ret<0) return -1; return ((long long)y*ret+z) / x;
}

long long myoclean(long long x, long long y, long long z) {
	if (!x) if (!z) return 0; else return -1;
	return mygcd(x, y, z);
}

void conduct() {
	int i; long long ans;
	for (i=bit[0]=1; i <= 32; ++i) bit[i] = bit[i-1] * 2;
	b -= a; if (b < 0) b += bit[k];
	ans = myoclean(c, bit[k], b);
	if (ans == -1) printf("FOREVER\n"); else printf("%lld\n", ans);
}

int main() {
	while (cin >> a >> b >> c >> k && (a|b|c|k)) conduct();
	return 0;
}
