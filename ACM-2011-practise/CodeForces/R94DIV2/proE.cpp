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

#define N 1010
long long f[N][N], sum[N];
const long long L = 1000000007LL;
int n, m, k;

void init() {
	int i, j;
	memset(sum, 0, sizeof(sum)); memset(f, 0, sizeof(f));
	for (i = 0; i < N; ++i) f[i][0] = 1;
	for (i = 3; i < N; ++i) {
		for (j = 1; j < N; ++j) sum[j] = (sum[j]+f[i-2][j-1]) % L;
		for (j = 1; j < N; ++j) f[i][j] = (f[i-1][j]+sum[j]) % L;
	}
}
		

int main() {
	init();
	while (scanf("%d%d%d", &n, &m, &k) != EOF) printf("%lld\n", f[n][k]*f[m][k]%L);
	return 0;
}
