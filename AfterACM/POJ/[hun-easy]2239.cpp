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
#define N 310
#define M 91000
edge e[M];
int hd[N], pre[N], vst[N];
int n, cnt;

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

void conduct() {
	int i, j, k, l;
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) {
		scanf("%d", &j);
		while (j--) {
			scanf("%d%d", &k, &l);
			insert((k-1)*12+l-1, i);
		}
	}
	printf("%d\n", hungarian(7*12));
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
