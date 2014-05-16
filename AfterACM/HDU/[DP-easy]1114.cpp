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
int f[N], a[N], b[N];
int n, m;
const int MAX = 0x6fffffff;

inline int getmin(int x, int y) { return x<y?x:y; }

void conduct() {
	int i, j;
	scanf("%d%d", &i, &j); m=j-i;
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%d%d", &a[i], &b[i]);
	memset(f, 0x7f, sizeof(f)); f[0]=0;
	for (i=0; i<n; ++i) for (j=0; j<m; ++j) 
		if (f[j]<=MAX && j+b[i]<=m) f[j+b[i]]=getmin(f[j+b[i]], f[j]+a[i]);
	if (f[m]<=MAX) printf("The minimum amount of money in the piggy-bank is %d.\n", f[m]);
	else printf("This is impossible.\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
