#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<map>
using namespace std;

#define N 510
int f[N][N];
int a[N], b[N];
int n, m;

inline int getmin(int x, int y) { return x<y?x:y; }

int search(int *f, int x) {
	int lst, mst, mid;
	lst=0; mst=m;
	while (lst<mst) {
		mid=(lst+mst)>>1;
		if (f[mid]>=x) mst=mid;
		else lst=mid+1;
	}
	return lst;
}

void conduct() {
	int i, j, k, ans;
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	scanf("%d", &m);
	for (i=0; i<m; ++i) scanf("%d", &b[i]);
	memset(f, 0x7f, sizeof(f));
	for (ans=-1, i=0; i<n; ++i) for (k=-1, j=0; j<m; ++j) {
		if (~k) f[j][k]=getmin(f[j][k], a[i]);
		if (a[i]==b[j]) {
			k=search(f[j], a[i]);
			f[j][k]=a[i];
			if (k>ans) ans=k;
		}
	}
	printf("%d\n", ans+1);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) { 
		conduct();
		if (time) printf("\n");
	}
	return 0;
}
