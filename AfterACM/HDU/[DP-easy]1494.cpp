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

#define N 11000
#define M 20
int f[N][M], a[N], b[N];
int n, m;

inline int getmin(int x, int y) { return x<y?x:y; }

void conduct() {
	int i, j, ans;
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	for (i=0; i<n; ++i) scanf("%d", &b[i]);
	for (i=0; i<n*m; ++i) { a[i]=a[i%n]; b[i]=b[i%n]; } n*=m;
	memset(f, 0x7f, sizeof(f)); f[0][0]=0;
	for (i=0; i<n; ++i) for (j=0; j<15; ++j) {
		if (j<14) f[i+1][j+1]=getmin(f[i+1][j+1], f[i][j]+a[i]);
		else f[i+1][j-4]=getmin(f[i+1][j-4], f[i][j]+a[i]);
		if (j>=5) f[i+1][j-5]=getmin(f[i+1][j-5], f[i][j]+b[i]);
	}
	for (ans=LONG_MAX, i=0; i<15; ++i) ans=getmin(ans, f[n][i]);
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF) conduct();
	return 0;
}
