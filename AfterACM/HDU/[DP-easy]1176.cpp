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

#define N 100010
#define L 12
int val[N][L], f[N][L];
int n;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j, k, ans;
	memset(val, 0, sizeof(val));
	memset(f, 0x80, sizeof(f)); f[0][5]=0;
	for (i=0; i<n; ++i) {
		scanf("%d%d", &j, &k);
		val[k][j]++;
	}
	for (i=0; i<N-1; ++i) for (j=0; j<L; ++j) {
		if (j) f[i+1][j-1]=getmax(f[i+1][j-1], f[i][j]+val[i+1][j-1]);
		if (j<L-1) f[i+1][j+1]=getmax(f[i+1][j+1], f[i][j]+val[i+1][j+1]);
		f[i+1][j]=getmax(f[i+1][j], f[i][j]+val[i+1][j]);
	}
	for (ans=i=0; i<L; ++i) ans=getmax(ans, f[N-1][i]);
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n)!=EOF && n) conduct();
	return 0;
}
