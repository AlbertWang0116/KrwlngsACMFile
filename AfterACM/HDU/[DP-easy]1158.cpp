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
int f[N][N], req[N];
int n, a, b, c;

inline int getmin(int x, int y) { return x<y?x:y; }

void conduct() {
	int i, j, k, ans;
	scanf("%d%d%d", &a, &b, &c);
	for (i=1; i<=n; ++i) scanf("%d", &req[i]); req[0]=0;
	memset(f, 0x40, sizeof(f)); f[0][0]=0;
	for (i=0; i<n; ++i) 
		for (j=0; j<=n; ++j) if (req[j]>=req[i]) 
			for (k=0; k<=n; ++k) if (req[k]>=req[i+1]) {
				if (req[j]>req[k]) f[i+1][k]=getmin(f[i+1][k], f[i][j]+(req[j]-req[k])*c+req[k]*b);
				else f[i+1][k]=getmin(f[i+1][k], f[i][j]+(req[k]-req[j])*a+req[k]*b);
			}
	for (ans=f[n][0], i=1; i<=n; ++i) if (req[i]>=req[n]) ans=getmin(f[n][i], ans);
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n)!=EOF && n) conduct();
	return 0;
}
