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

const int N = 8;
const int dr[9] = { -1, -1, -1, 0, 1, 1, 1, 0, 0 };
const int dc[9] = { -1,  0,  1, 1, 1, 0,-1,-1, 0 };
int pos[N][N][2], valid[N][N];
char grd[N+10][N+10];

void assgn(int r, int c, int cur) {
	if (r < 0 || r >= N || c < 0 || c >= N) return;
	if (!valid[r][c]) return;
	pos[r][c][1^cur] = 1;
}

void conduct() {
	int i, j, k, l, cur;
	for (i = N-1; i >= 0; --i) scanf("%s", grd[i]);
	memset(pos, 0, sizeof(pos)); pos[0][0][0] = 1;
	for (cur = l = 0; l < N; ++l) {
		if (pos[N-1][N-1][cur]) { printf("WIN\n"); return; }
		for (i = 0; i < N-1; ++i) for (j = 0; j < N; ++j)
			if (grd[i][j] != 'S' && grd[i+1][j] != 'S') valid[i][j] = 1; else valid[i][j] = 0;
		for (j = 0; j < N; ++j) if (grd[i][j] != 'S') valid[i][j] = 1; else valid[i][j] = 0;
		for (i = 0; i < N-1; ++i) for (j = 0; j < N; ++j) grd[i][j] = grd[i+1][j];
		for (j = 0; j < N; ++j) grd[i][j] = '.';
		for (i = 0; i < N; ++i) for (j = 0; j < N; ++j) if (pos[i][j][cur])
			for (k = 0; k < 9; ++k) assgn(i+dr[k], j+dc[k], cur);
		for (i = 0; i < N; ++i) for (j = 0; j < N; ++j) pos[i][j][cur] = 0;
//		printf("l=%d ---\n", l);
//		for (i = N-1; i >= 0; --i) { for (j = 0; j < N; ++j) printf("%d", valid[i][j]); printf("\n"); }
		cur ^= 1;
	} for (i = 0; i < N; ++i) for (j = 0; j < N; ++j) if (pos[i][j][cur]) { printf("WIN\n"); return; }
	printf("LOSE\n");
}

int main() {
	conduct();
	return 0;
}
