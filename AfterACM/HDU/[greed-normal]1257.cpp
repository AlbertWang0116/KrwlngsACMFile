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

#define N 1100000
int a[N], f[N];
int n;

int search(int x) {
	int lst, mst, mid;
	lst=0; mst=n;
	while (lst<mst) {
		mid=(lst+mst)>>1;
		if (f[mid]<x) lst=mid+1; else mst=mid;
	}
	return lst;
}

void conduct() {
	int i, j;
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	memset(f, 0x7f, sizeof(f));
	for (i=0; i<n; ++i) {
		j=search(a[i]);
		f[j]=a[i];
	}
	for (i=0; i<n; ++i) if (f[i]>=100000) break;
	printf("%d\n", i);
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
