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

#define N 210
const long long MAX = 1000000000000000000LL;
long long bit[N], g[N], f[N];
int seq[N];
int n;

void init() {
	bit[0] = bit[1] = 1;
	for (n = 2; n < N; ++n) {
		bit[n] = bit[n-1]+bit[n-2];
		if (bit[n] < 0 || bit[n] > MAX) break;
	}
}

void conduct() {
	int i, cnt; long long tot;
	scanf("%I64d", &tot); seq[0] = 1;
	for (i = 1; i < n; ++i) if (tot < bit[i]) break;
	for (cnt = 0, --i; i > 0; --i) if (tot >= bit[i]) { seq[++cnt] = i; tot -= bit[i]; }
	seq[++cnt] = 1; f[0] = 1; g[0] = 1;
//	for (i = 1; i < cnt; ++i) printf("seq:%d val:%lld\n", seq[i], bit[seq[i]]);
	for (i = 1; i < cnt; ++i) {
		f[i] = (seq[i]-seq[i+1]-1)/2*g[i-1]+f[i-1];
		g[i] = (seq[i]-seq[i+1])/2*g[i-1]+f[i-1];
	} printf("%I64d\n", g[cnt-1]);
}

int main() {
	int time; scanf("%d", &time);
	init(); while (time--) conduct();
	return 0;
}
