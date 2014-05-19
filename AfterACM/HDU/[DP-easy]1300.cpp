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
int f[N], a[N], b[N];
int n;

inline int getmin(int x, int y) { return x<y?x:y; }

void conduct() {
	int i, j, sum;
	scanf("%d", &n);
	for (i=1; i<=n; ++i) scanf("%d%d", &a[i], &b[i]);
	memset(f, 0x7f, sizeof(f)); f[0]=0;
	for (i=1; i<=n; ++i) 
		for (sum=0, j=i-1; ~j; --j) {
			sum+=a[j+1];
			f[i]=getmin(f[i], f[j]+(sum+10)*b[i]);
		}
	printf("%d\n", f[n]);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
