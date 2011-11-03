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

#define N 110
bool e[N][N], vst[N];
int n, m;

void dfs(int x) {
	vst[x] = 1;
	for (int i = 1; i <= n; ++i) if (e[x][i] && !vst[i]) dfs(i);
}

int main()
{
	int i, st, ed;
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(e, 0, sizeof(e));
		for (i = 0; i < m; ++i) {
			scanf("%d%d", &st, &ed); e[st][ed] = e[ed][st] = 1;
		} if (n != m) { printf("NO\n"); return 0; }
		memset(vst, 0, sizeof(vst)); dfs(1);
		for (i = 1; i <= n; ++i) if (!vst[i]) { printf("NO\n"); return 0; }
		printf("FHTAGN!\n"); return 0;
	} return 0;
}
