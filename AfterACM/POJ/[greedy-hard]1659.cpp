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
int a[N], e[N][N], seq[N];
int n;

int cmp(const int &i, const int &j) { return a[i]>a[j]; }

void conduct() {
	int i, j;
	memset(e, 0, sizeof(e));
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	for (i=0; i<n; ++i) seq[i]=i;
	for (i=0; i<n; ++i) {
		sort(seq+i, seq+n, cmp);
		for (j=i+1; j<n&&a[seq[j]]&&a[seq[i]]; ++j) { e[seq[i]][seq[j]]=e[seq[j]][seq[i]]=1; a[seq[i]]--; a[seq[j]]--; }
		if (a[seq[i]]) { printf("NO\n"); return; }
	}
	printf("YES\n");
	for (i=0; i<n; ++i) {
		for (j=0; j<n; ++j) printf("%d ", e[i][j]);
		printf("\n");
	}
}

int main() {
	int time; scanf("%d", &time);
	while (time--) { conduct(); if (time) printf("\n"); }
	return 0;
}
