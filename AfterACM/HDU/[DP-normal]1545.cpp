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

#define N 70
#define L 10
long long f[N][L][L];
int n, m;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j, k;
	long long ans;
	memset(f, 0, sizeof(f)); f[0][0][0]=1LL;
	for (i=0; i<=n; ++i) for (j=0; j<=m; ++j) for (k=0; k<=m; ++k) {
		if (j<m) f[i+1][j+1][getmax(k-1, 0)]+=f[i][j][k];
		if (k<m) f[i+1][getmax(j-1, 0)][k+1]+=f[i][j][k];
	}
	for (ans=j=0; j<=m; ++j) for (k=0; k<=m; ++k) ans+=f[n][j][k];
	cout << ans << endl;
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF) conduct();
	return 0;
}
