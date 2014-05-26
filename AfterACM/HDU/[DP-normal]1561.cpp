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

struct edge { int des, nxt; };
#define N 300
edge e[N];
int f[N][N], a[N], hd[N];
int n, m, cnt;

inline int getmax(int x, int y) { return x>y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

void dp(int x) {
	int i, j, k, v;
	memset(f[x], 0, sizeof(f[x]));
	for (i=hd[x]; i; i=e[i].nxt) {
		dp(v=e[i].des);
		for (j=m; ~j; --j) for (k=0; k<=j; ++k) f[x][j]=getmax(f[x][j], f[x][j-k]+f[v][k]);
	}
	for (i=m; i; --i) f[x][i]=f[x][i-1]+a[x];
	//printf("%d: ", x); for (i=0; i<=m; ++i) printf("%d ", f[x][i]); printf("\n");
}

void conduct() {
	int i, j;
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=1; i<=n; ++i) {
		scanf("%d%d", &j, &a[i]);
		insert(j, i);
	} a[0]=0; m++;
	dp(0);
	printf("%d\n", f[0][m]);
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && (n||m)) conduct();
	return 0;
}
