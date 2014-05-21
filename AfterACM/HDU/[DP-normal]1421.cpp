#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<climits>
#include<string>
using namespace std;

#define N 2010
int a[N];
int f[2][N];
int n, k;

inline int SQR(int x) { return x*x; }
inline int getmin(int x, int y) { return x<y?x:y; }

void conduct() {
	int i, j, cur, pre, ans;
	for (i=1; i<=n; ++i) scanf("%d", &a[i]); sort(a+1, a+n+1);
	memset(f, 0, sizeof(f));
	for (cur=i=1, pre=0; i<=k; ++i) {
		cur=1-cur; pre=1-pre;
		f[cur][i*2-1]=LONG_MAX;
		for (j=i*2; j<=n; ++j) f[cur][j]=getmin(f[pre][j-2]+SQR(a[j]-a[j-1]), f[cur][j-1]);
	}
	for (ans=LONG_MAX, i=k*2; i<=n; ++i) ans=getmin(ans, f[cur][i]);
	cout << ans << endl;
}

int main() {
	while (scanf("%d%d", &n, &k)!=EOF) conduct();
	return 0;
}
