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

#define N 210
int e[N][N], len[N], pre[N], vst[N], mst[N][N];
int n, m;
const int MAX = 0x7fffffff;

inline int getmin(int x, int y) { return x<y?x:y; }
inline int getmax(int x, int y) { return x>y?x:y; }

void prim(int s) {
	int i, j, k, l;
	for (i=0; i<n; ++i) { len[i]=e[i][s]; pre[i]=s; }
	memset(vst, 0, sizeof(vst));
	for (i=0; i<n; ++i) {
		for (j=0, k=MAX; j<n; ++j) if (!vst[j] && len[j]<k) { k=len[j]; l=j; }
		for (j=0; j<n; ++j) if (vst[j]) mst[l][j]=mst[j][l]=getmax(mst[pre[l]][j], len[l]);
		vst[l]=1;
		for (j=0; j<n; ++j) if (!vst[j] && len[j]>e[l][j]) { len[j]=e[l][j]; pre[j]=l; }
	}
}

void conduct() {
	int i, j, k, l;
	long long ans;
	scanf("%d%d", &n, &m);
	memset(e, 0x7f, sizeof(e));
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &j, &k, &l); --j; --k;
		e[j][k]=e[k][j]=getmin(e[j][k], l);
	}
	for (i=0; i<n; ++i) { e[i][i]=0; mst[i][i]=-1; }
	prim(0);
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) 
		if (j!=pre[i] && i!=pre[j] && e[i][j]==mst[i][j]) { printf("Not Unique!\n"); return; }
	for (ans=i=0; i<n; ++i) ans+=len[i];
	if (ans>=0x7f7f7f7f) printf("Not Unique!\n");
	else cout << ans << endl;
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
}
