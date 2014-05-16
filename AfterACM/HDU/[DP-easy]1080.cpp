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
int a[N], b[N], f[N][N];
const int ref2[] = { -3, -4, -2, -1 };
const int ref[][4] = { { 5, -1, -2, -1 }, { -1, 5, -3, -2 }, { -2, -3, 5, -2 }, { -1, -2, -2, 5 } };
char str[N];
int n, m;

inline int getmax(int x, int y) { return x>y?x:y; }

inline int trans(char x) {
	if (x=='A') return 0;
	else if (x=='C') return 1;
	else if (x=='G') return 2;
	else return 3;
}

void conduct() {
	int i, j;
	scanf("%d%s", &n, str);
	for (i=0; i<n; ++i) a[i]=trans(str[i]);
	scanf("%d%s", &m, str);
	for (i=0; i<m; ++i) b[i]=trans(str[i]);
	memset(f, 0x80, sizeof(f)); f[0][0]=0;
	for (i=0; i<=n; ++i) for (j=0; j<=m; ++j) {
		if (i<n) f[i+1][j]=getmax(f[i+1][j], f[i][j]+ref2[a[i]]);
		if (j<m) f[i][j+1]=getmax(f[i][j+1], f[i][j]+ref2[b[j]]);
		if (i<n && j<m) f[i+1][j+1]=getmax(f[i+1][j+1], f[i][j]+ref[a[i]][b[j]]);
	}
	printf("%d\n", f[n][m]);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
