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

#define N 10010
int a[N], seq[N];
int n;

void conduct() {
	int i;
	for (i = 0; i < n; ++i) scanf("%d", &a[i]);
	for (seq[0] = i = 0; i < n; ++i) if (a[i] == seq[0]+1) seq[++seq[0]] = i;
	printf("%d\n", seq[0]); if (!seq[0]) return ;
	for (i = 1; i <= seq[0]; ++i) printf("%d ", 2000+seq[i]+1); printf("\n");
}

int main() {
	while (scanf("%d", &n) != EOF) {
		conduct();
	} return 0;
}
