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

struct edge { int nxt, des; };
#define N 1100
#define M 11000
#define L 40
edge e[M];
int hd[N], pre[N], vst[N];
int grd[L][L];
int n, r, c, cnt;
const int dr[] = { 1, 0, -1, 0 };
const int dc[] = { 0, -1, 0, 1 };

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

int hun_dfs(int x, int i=0, int u=0) {
	for (vst[x]=0, i=hd[x]; i; i=e[i].nxt)
		if (!~(u=pre[e[i].des])||(vst[u]&&hun_dfs(u))) break;
	if (i) pre[e[i].des]=x; return i;
}

int hungarian(int n, int i=0, int ret=0) {
	memset(pre, -1, sizeof(pre));
	for (i=0; i<n; ++i) { memset(vst, -1, sizeof(vst)); hun_dfs(i)?ret++:0; }
	return ret;
}

int valid(int tr, int tc) {
	if (tr<0 || tr>=r) return 0;
	if (tc<0 || tc>=c) return 0;
	return 1-grd[tr][tc];
}

void conduct() {
	int i, j, k, sum;
	scanf("%d%d%d", &r, &c, &k); sum=n=r*c;
	memset(grd, 0, sizeof(grd));
	while (k--) { 
		scanf("%d%d", &j, &i); 
		if (!grd[i-1][j-1]) {sum--; grd[i-1][j-1]=1; } 
	}
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<r; ++i) for (j=0; j<c; ++j) if (!grd[i][j])
		for (k=0; k<4; ++k) if (valid(i+dr[k], j+dc[k])) insert(i*c+j, (i+dr[k])*c+j+dc[k]);
	if (sum==hungarian(n)) printf("YES\n");
	else printf("NO\n");
}

int main() {
	conduct();
	return 0;
}
