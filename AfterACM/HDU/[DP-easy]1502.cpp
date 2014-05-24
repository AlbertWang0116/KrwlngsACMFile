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

int n;
char f[62][62][62][90];

void print(char *a) {
	for (int i=a[0]; i; --i) printf("%d", a[i]);
	printf("\n\n");
}

void add(char *a, char *b) {
	int i;
	for (i=1; i<=b[0]; ++i) { a[i]+=b[i]; a[i+1]+=a[i]/10; a[i]%=10; }
	for (i=b[0]+1; a[i]>=10; ++i) { a[i+1]+=a[i]/10; a[i]%=10; }
	if (!a[i]) --i; if (i>a[0]) a[0]=i;
}

void init() {
	int i, j, k;
	memset(f, 0, sizeof(f)); f[0][0][0][0]=f[0][0][0][1]=1;
	for (i=0; i<=60; ++i) for (j=0; j<=i; ++j) for (k=0; k<=j; ++k) {
		add(f[i+1][j][k], f[i][j][k]);
		if (i>j) add(f[i][j+1][k], f[i][j][k]);
		if (j>k) add(f[i][j][k+1], f[i][j][k]);
	}
}

int main() {
	init();
	while (scanf("%d", &n)!=EOF) print(f[n][n][n]);
}
