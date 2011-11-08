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

#define N 5010
bool e[N][N], tag, cover;
char str[N];
int seq[N], col[N], cc[N], vst[N];
int n, cnt, root;

void dfs(int x) {
	vst[x] = 1;
	for (int i = 1; !tag && i <= n; ++i) 
		if (e[x][i]) if (!vst[i]) dfs(i);
					 else if (vst[i]>0) { tag = 1; root = i; }
	if (tag && !cover) {
		col[x] = 1;
		if (x == root) cover = 1;
	} vst[x] = -1;
}

bool judge(int *seq) {
	int i, j, k;
	if (e[seq[0]][seq[1]] && e[seq[1]][seq[2]] && e[seq[2]][seq[0]]) {
		printf("%d %d %d\n", seq[0], seq[1], seq[2]); return 1;
	} else if (e[seq[0]][seq[2]] && e[seq[2]][seq[1]] && e[seq[1]][seq[0]]) {
		printf("%d %d %d\n", seq[0], seq[2], seq[1]); return 1;
	} for (i = 0; i < 3; ++i) if (e[seq[i]][seq[(i+2)%3]] ^ e[seq[i]][seq[(i+1)%3]]) break;
	for (j = k = 0; j < 3; ++j) if (j != i) seq[k++] = seq[j]; cnt--; return 0;
}

void conduct()
{
	int i, j, tc;
	for (i = 0; i < n; ++i) {
		scanf("%s", str); for (j = 0; j < n; ++j) e[i+1][j+1] = str[j]-'0';
	} memset(vst, 0, sizeof(vst)); tag = false;
	memset(col, 0, sizeof(col)); cover = false;
	for (i = 1; !tag && i <= n; ++i) if (!vst[i]) dfs(i);
	for (cnt = 0, i = 1; i <= n; ++i) if (col[i]) {
		seq[cnt++] = i;
		if (cnt == 3 && judge(seq)) return;
	} printf("-1\n");
}

int main()
{
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
