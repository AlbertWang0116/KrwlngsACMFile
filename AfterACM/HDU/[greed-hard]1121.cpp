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

#define N 200
int a[N], b[N];
int n, m;

void conduct() {
	int i, j, k;
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	for (i=1; i<n; ++i) {
		b[i]=a[0];
		for (j=0; j<n-i; ++j) a[j]=a[j+1]-a[j];
	}
	for (i=1; i<=m; ++i) a[i]=a[0];
	for (i=1; i<n; ++i) {
		for (k=j=0; j<m+i; ++j)	k+=a[j];
		a[m+i]=0;
		for (j=m+i; ~j; --j) { k-=a[j]; a[j]=b[n-i]+k; } 
	}
	for (i=n; i<m+n; ++i) {
		if (i>n) printf(" ");
		printf("%d", a[i]);
	}
	printf("\n");
}

int main() {
	int time; scanf("%d", &time);
	while(time--) conduct();
	return 0;
}
