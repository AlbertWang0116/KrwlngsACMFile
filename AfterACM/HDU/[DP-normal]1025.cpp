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

#define N 510000
int a[N], b[N], seq[N], val[N];
int n;

int cmp(const int &i, const int &j) { return a[i]<a[j]; }
int search(int x) {
	int lst, mst, mid;
	lst=0; mst=n;
	while (lst<mst) {
		mid=(lst+mst)>>1;
		if (val[mid]>x) mst=mid;
		else lst=mid+1;
	}
	return lst;
}

void conduct() {
	int i;
	for (i=0; i<n; ++i) scanf("%d%d", &a[i], &b[i]);
	for (i=0; i<n; ++i) seq[i]=i; sort(seq, seq+n, cmp);
	memset(val, 0x7f, sizeof(val));
	for (i=0; i<n; ++i) val[search(b[seq[i]])]=b[seq[i]];
	for (i=0; i<n; ++i) if (val[i]>n) break;
	if (i>1) printf("My king, at most %d roads can be built.\n", i);
	else printf("My king, at most %d road can be built.\n", i);
}

int main() {
	int time=0;
	while (scanf("%d", &n)!=EOF) {
		printf("Case %d:\n", ++time);
		conduct();
		printf("\n");
	}
	return 0;
}
