#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

#define N 110
int f[N], a[N][N];
int n, m;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j, k;
	for (i=0; i<n; ++i) for (j=1; j<=m; ++j) scanf("%d", &a[i][j]);
	memset(f, 0, sizeof(f));
	for (i=0; i<n; ++i) for (j=m; ~j; --j) for (k=0; k<=j; ++k)
		f[j]=getmax(f[j], f[j-k]+a[i][k]);
	for (j=i=0; i<=m; ++i) j=getmax(j, f[i]);
	printf("%d\n", j);
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && (n||m)) conduct();
	return 0;
}
