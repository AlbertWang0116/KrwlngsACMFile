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
int cnt[N], e[N][N], vst[N], tmp[N];
int n, m;

void conduct() {
	int i, j, k, tag, ret;
	memset(e, 0, sizeof(e)); memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < m; ++i) {
		scanf("%d%d", &j, &k); j--; k--;
		e[j][k] = e[k][j] = 1;
		cnt[j]++; cnt[k]++;
	} memset(vst, 0, sizeof(vst)); ret = 0;
	while (1) {
//		printf("pp:"); for (i = 0; i < n; ++i) if (!vst[i]) printf("%d ", i); printf("\n");
		for (i = 0; i < n; ++i) tmp[i] = cnt[i];
		for (tag = i = 0; i < n; ++i) if (!vst[i] && cnt[i] == 1) {
			tag = vst[i] = 1;
			for (j = 0; j < n; ++j) if (!vst[j] && e[i][j]) tmp[j]--;
		} for (i = 0; i < n; ++i) cnt[i] = tmp[i]; if (!tag) break; ret++;
	} printf("%d\n", ret);
}

int main() {
//	while (scanf("%d%d", &n, &m) != EOF) conduct();
	scanf("%d%d", &n, &m); conduct();
	return 0;
}
