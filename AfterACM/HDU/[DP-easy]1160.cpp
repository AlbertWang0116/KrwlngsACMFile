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
int f[N], a[N], b[N], seq[N], pre[N], ref[N];
int n;

int cmp(const int &i, const int &j) {
	if (a[i]==a[j]) return b[i]<b[j];
	else return a[i]<a[j];
}

int search(int x) {
	int lst, mst, mid;
	lst=0; mst=n;
	while (lst<mst) {
		mid=(lst+mst)>>1;
		if (f[mid]<=x) mst=mid;
		else lst=mid+1;
	}
	return lst;
}

void print(int x) {
	if (~x) print(pre[x]);
	else return;
	printf("%d\n", x+1);
}

void conduct() {
	int i, j;
	for (i=0; i<n; ++i) seq[i]=i; sort(seq, seq+n, cmp);
	memset(f, 0, sizeof(f));
	for (i=0; i<n; ++i) {
		j=search(b[seq[i]]);
		if (!j) pre[seq[i]]=-1; else pre[seq[i]]=ref[j-1];
		f[j]=b[seq[i]]; ref[j]=seq[i];
	}
	for (i=0; i<n; ++i) if (!f[i]) break;
	printf("%d\n", i);
	print(ref[i-1]);
}

int main() {
	n=0;
	while (scanf("%d%d", &a[n], &b[n])!=EOF) n++;
	conduct();
	return 0;
}
