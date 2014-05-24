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

#define N 21
#define M 410
int f[N][N][M], vst[N][M];
int n;

inline int getmax(int x, int y) { return x>y?x:y; }

void init() {
	int i, j, k;
	memset(f, 0, sizeof(f)); f[1][1][0]=1;
	for (i=2; i<=20; ++i) {
		for (j=1; j<=20; ++j) for (k=0; k<=400; ++k) f[i][1][k+i-1]=getmax(f[i][1][k+i-1], f[i-1][j][k]);
		for (j=2; j<=20; ++j) for (k=0; k<=400; ++k) f[i][j][k+i-j]=getmax(f[i][j][k+i-j], f[i-1][j-1][k]);
	}
	memset(vst, 0, sizeof(vst));
	for (i=1; i<=20; ++i) for (j=1; j<=20; ++j) for (k=0; k<=400; ++k)
		vst[i][k]=getmax(vst[i][k], f[i][j][k]);
}

void conduct() {
	int j=0;
	for (int i=0; i<=400; ++i) if (vst[n][i]) {
		if (j) printf(" "); else j=1;
		printf("%d", i);
	}
	printf("\n");
}

int main() {
	init();
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
