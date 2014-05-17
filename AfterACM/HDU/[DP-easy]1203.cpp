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

#define N 11000
int a[N], vst[N];
double b[N];
double f[N];
int n, m;
const double eps = 1e-4;

inline double getmin(double x, double y) { return x-y<-eps?x:y; }

void conduct() {
	int i, j; double ans;
	for (i=0; i<n; ++i) scanf("%d%lf", &a[i], &b[i]);
	for (i=0; i<n; ++i) b[i]=1.0-b[i];
	for (i=0; i<=m; ++i) f[i]=1.0;
	memset(vst, 0, sizeof(vst)); vst[0]=1;
	for (i=0; i<n; ++i) for (j=m; ~j; --j) if (vst[j]&&j+a[i]<=m) { f[j+a[i]]=getmin(f[j+a[i]], f[j]*b[i]); vst[j+a[i]]=1; }
	for (ans=1.0, i=0; i<=m; ++i) ans=getmin(ans, f[i]);
	printf("%.1f%%\n", (1.0-ans)*100.0);
}

int main() {
	while (scanf("%d%d", &m, &n)!=EOF && (n||m)) conduct();
	return 0;
}
