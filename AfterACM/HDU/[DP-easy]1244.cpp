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

#define N 1100
#define M 110
int f[M][N], a[N], b[M];
int n, m;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j, k;
	scanf("%d", &m);
	for (i=1; i<=m; ++i) scanf("%d", &b[i]);
	for (i=1; i<=n; ++i) scanf("%d", &a[i]); a[0]=0;
	memset(f, 0, sizeof(f));
	for (i=1; i<=m; ++i) {
		for (j=k=0; j<=b[i]; ++j) { k+=a[j]; f[i][j]=LONG_MIN; }
		if (b[i]) f[i][b[i]]=k+f[i-1][0];
		for (; j<=n; ++j) {
			k+=a[j]-a[j-b[i]];
			f[i][j]=getmax(f[i-1][j-b[i]]+k, f[i][j-1]);
		}
	}
	printf("%d\n", f[m][n]);
}

int main() {
	while (scanf("%d", &n)!=EOF && n) conduct();
	return 0;
}
