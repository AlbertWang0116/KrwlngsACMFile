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

struct edge { int des, nxt; };
#define N 110
edge e[1100];
int val[N], req[N], f[N][N], hd[N];
int n, m, cnt;

inline int getmax(int x, int y) { return x>y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].des=y; e[cnt].nxt=hd[x]; hd[x]=cnt;
}

void dp(int x, int pa) {
	int i, j, k;
	for (i=0; i<=m; ++i) f[x][i]=0;
	for (i=hd[x]; i; i=e[i].nxt) if (e[i].des!=pa) {
		dp(e[i].des, x);
		for (j=m; j>=0; --j)
			for (k=0; k<=j; ++k) f[x][j]=getmax(f[x][j], f[x][j-k]+f[e[i].des][k]);
	}
	for (i=m; i>0 && i-req[x]>=0; --i) f[x][i]=f[x][i-req[x]]+val[x];
	for (; i>=0; --i) f[x][i]=0;
}

void conduct() {
	int i, j, k;
	for (i=0; i<n; ++i) {
		scanf("%d%d", &j, &val[i]);
		req[i]=(j+19)/20;
	}
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=1; i<n; ++i) {
		scanf("%d%d", &j, &k); --j; --k;
		insert(j, k); insert(k, j);
	}
	dp(0, -1);
	for (i=0; i<n; ++i) if (f[i][0]>0) while (1);
	printf("%d\n", f[0][m]);
}

int main() {
	while (scanf("%d%d", &n, &m) && (~n || ~m)) conduct();
	return 0;
}
