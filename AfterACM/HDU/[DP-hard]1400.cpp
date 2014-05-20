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

#define N 2050
#define M 20
int t[N][N], val[N];
long long f[M][N];
int n, m;

int check(int x, int y) {
	int i;
	for (i=0; i<y; ++i) if ((x&(1<<i))==0)
		if (i==y-1 || (x&(1<<(i+1)))) break;
		else ++i;
	return i==y;
}

void init(int x) {
	int i, j;
	for (i=0; i<(1<<x); ++i) if (check(i, x)) val[i]=1; else val[i]=0;
	for (i=0; i<(1<<x); ++i) {
		t[i][0]=0;
		for (j=0; j<(1<<x); ++j) if ((i&j)==0 && val[i|j]) t[i][++t[i][0]]=j;
	}
}

void conduct() {
	int i, j, k;
	long long ans;
	init(m);
	memset(f, 0, sizeof(f)); f[0][0]=1LL;
	for (i=0; i<n-1; ++i) for (j=0; j<(1<<m); ++j) for (k=1; k<=t[j][0]; ++k) f[i+1][t[j][k]]+=f[i][j];
	for (ans=i=0; i<(1<<m); ++i) if (val[i]) ans+=f[n-1][i];
	cout << ans << endl;
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && (n||m)) conduct();
	return 0;
}
