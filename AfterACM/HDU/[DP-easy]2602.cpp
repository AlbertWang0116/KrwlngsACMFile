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

#define N 1100
int f[N], a[N], b[N];
int n, m;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j;
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	for (i=0; i<n; ++i) scanf("%d", &b[i]);
	memset(f, 0, sizeof(f));
	for (i=0; i<n; ++i) for (j=m; j>=b[i]; --j) f[j]=getmax(f[j], f[j-b[i]]+a[i]);
	printf("%d\n", f[m]);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
