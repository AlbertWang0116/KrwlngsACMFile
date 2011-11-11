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

#define N 2010
int mp[N][N], w[N][N], hor[N][N], ver[N][N];
char str[N];
int n;

void conduct() {
	int i, j, ts, state, ret;
	memset(w, 0, sizeof(w)); memset(hor, 0, sizeof(hor)); memset(ver, 0, sizeof(ver));
	for (i = 1; i <= n; ++i) {
		scanf("%s", str);
		for (j = 1; j <= n; ++j) mp[i][j] = str[j-1]-'0';
	} for (i = 1; i <= n; ++i) {
		state = mp[i][i+1] ^ ver[i-1][i+1]; ver[i][i+1] = ver[i-1][i+1];
		for (j = i+2; j <= n; ++j) {
			ts = mp[i][j] ^ ver[i-1][j]; ver[i][j] = ver[i-1][j];
			if (ts != state) { state = ts; w[i][j-1] = 1; ver[i][j-1] ^= 1; }
		} if (state) { w[i][j-1] = 1; ver[i][j-1] ^= 1; }
		state = mp[i+1][i] ^ hor[i+1][i-1]; hor[i+1][i] = ver[i+1][i-1];
		for (j = i+2; j <= n; ++j) {
			ts = mp[j][i] ^ hor[j][i-1]; hor[j][i] = hor[j][i-1];
			if (ts != state) { state = ts; w[j-1][i] = 1; hor[j-1][i] ^= 1; }
		} if (state) { w[j-1][i] = 1; hor[j-1][i] ^= 1; }
		for (state = 0, j = 1; j <= n; ++j) state = state ^ w[i][j] ^ w[j][i];
		if (state ^ mp[i][i]) w[i][i] = 1;
	} for (ret = i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) if (w[i][j]) ret++;
	printf("%d\n", ret-1);
//	for (i = 1; i <= n; ++i) { for (j = 1; j <= n; ++j) printf("%d", w[i][j]); printf("\n"); }
//	printf("\n"); for (i = 1; i <= n; ++i) { for (j = 1; j <= n; ++j) printf("%d", mp[i][j]); printf("\n"); }
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
