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

#define N 1100000
int f[4][N];
int n, m;

void init() {
	f[0][0]=1; for (int i=1; i<=1000000; ++i) f[0][i]=i+1;
	f[1][0]=2; for (int i=1; i<=1000000; ++i) f[1][i]=i+2;
	f[2][0]=3; for (int i=1; i<=1000000; ++i) f[2][i]=2*i+3;
	f[3][0]=5; for (int i=1; i<=24; ++i) f[3][i]=f[3][i-1]*2+3;	
}

int main() {
	init();
	while (scanf("%d%d", &m, &n)!=EOF) printf("%d\n", f[m][n]);
	return 0;
}
