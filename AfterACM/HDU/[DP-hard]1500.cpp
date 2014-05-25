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

#define N 5010
#define M 1100
int f[M][N], a[N];
int n, m;

inline int getmin(int x, int y) { return x<y?x:y; }
inline int SQR(int x) { return x*x; }

void conduct() {
	int i, j, ans;
	scanf("%d%d", &m, &n); m+=8;
	for (i=0; i<n; ++i) scanf("%d", &a[i]); 
	memset(f, 0x7f, sizeof(f)); memset(f[0], 0, sizeof(f[0]));
	for (i=1; i<=m; ++i) for (j=n-i*3; ~j; --j) f[i][j]=getmin(f[i][j+1], f[i-1][j+2]+SQR(a[j]-a[j+1]));
	for (ans=LONG_MAX, i=0; i<n; ++i) ans=getmin(ans, f[m][i]);
	printf("%d\n", ans);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
