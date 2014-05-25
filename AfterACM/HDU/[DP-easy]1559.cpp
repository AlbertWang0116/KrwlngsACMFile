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

#define N 1010
int a[N][N], b[N][N], c[N][N];
int n, m, x, y;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j, sum;
	scanf("%d%d%d%d", &n, &m, &x, &y);
	for (i=0; i<n; ++i) for (j=0; j<m; ++j) scanf("%d", &a[i][j]);
	for (i=0; i<n; ++i) {
		for (sum=j=0; j<y-1; ++j) sum+=a[i][j];
		for (j=0; j<m-y+1; ++j) { sum+=a[i][j+y-1]; b[i][j]=sum; sum-=a[i][j]; }
	}
	for (j=0; j<m-y+1; ++j) {
		for (sum=i=0; i<x-1; ++i) sum+=b[i][j];
		for (i=0; i<n-x+1; ++i) { sum+=b[i+x-1][j]; c[i][j]=sum; sum-=b[i][j]; }
	}
	for (sum=i=0; i<n-x+1; ++i) for (j=0; j<m-y+1; ++j) sum=getmax(sum, c[i][j]);
	printf("%d\n", sum);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
