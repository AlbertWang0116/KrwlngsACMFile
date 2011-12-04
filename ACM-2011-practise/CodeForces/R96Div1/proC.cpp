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

#define N 210
int f[N][N][2], vst[N][N][2];
char str[N];
int n, m;
const int MIN = LONG_MIN;

int getmax(int x, int y) { return x > y ? x : y; }

int cal(int x) {
	int i, j, k, l;
	for (i = 0; i < n; ++i) for (j = 0; j < n; ++j) for (k = 0; k < 2; ++k) f[i][j][k] = MIN;
	memset(vst, 0, sizeof(vst)); vst[0][0][x] = 1; f[0][0][x] = 0; 	
	for (i = 0; i < n; ++i) for (j = 0; j <= m; ++j)
		for (k = 0; k < 2; ++k) if (vst[i][j][k]) {
			if (str[i] == 'F') {
				for (l = j; l <= m; ++l) 
					if ((l-j)&1) {
						f[i+1][l][1-k] = getmax(f[i+1][l][1-k], f[i][j][k]);
						vst[i+1][l][1-k] = 1;
					} else {
						f[i+1][l][k] = getmax(f[i+1][l][k], f[i][j][k]+(k?1:-1));
						vst[i+1][l][k] = 1;
					}
			} else {
				for (l = j; l <= m; ++l)
					if ((l-j)&1) {
						f[i+1][l][k] = getmax(f[i+1][l][k], f[i][j][k]+(k?1:-1));
						vst[i+1][l][k] = 1;
					} else {
						f[i+1][l][1-k] = getmax(f[i+1][l][1-k], f[i][j][k]);
						vst[i+1][l][1-k] = 1;
					}
			}
		} return getmax(f[n][m][0], f[n][m][1]);
}


void conduct() {
	scanf("%d", &m); n = strlen(str);
	int ret = getmax(cal(0), cal(1));
	printf("%d\n", ret);
}

int main() {
	while (scanf("%s", str) != EOF) conduct();
	return 0;
}
