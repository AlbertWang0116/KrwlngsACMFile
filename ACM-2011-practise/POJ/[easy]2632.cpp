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
int grd[N][N], f[N], x[N], y[N];
int dx[4] = { 0, 1, 0, -1};
int dy[4] = { 1, 0, -1, 0};
char trs[4] = { 'N', 'E', 'S', 'W'};
int n, m, wid, hig;

void input()
{
	int i, j; char tmp[10];
	scanf("%d%d", &wid, &hig);
	scanf("%d %d", &n, &m); memset(grd, 0, sizeof(grd));
	for (i = 1; i <= n; ++i) {
		scanf("%d%d%s", &x[i], &y[i], tmp); grd[x[i]][y[i]] = i;
		for (j = 0; j < 4; ++j) if (tmp[0] == trs[j]) f[i] = j;
	}
}

void conduct()
{
	bool error;
	int idx, rpt, i, j;
	char cmd[10];
	error = false;
	while (m--) {
		scanf("%d%s%d", &idx, cmd, &rpt);
		if (error) continue;
//		for (j = hig; j > 0; --j) {
//			for (i = 1; i <= wid; ++i) if (grd[i][j]) printf("%c ", trs[f[grd[i][j]]]); else printf("0 ");
//			printf("\n");
//		} printf("\n");
		switch(cmd[0]) {
			case 'L': f[idx] = (f[idx] + 3 * rpt) % 4; break;
			case 'R': f[idx] = (f[idx] + rpt) % 4; break;
			case 'F':
				for (i = 1; i <= rpt && !error; ++i) {
					if (x[idx] + dx[f[idx]] * i <= 0 || x[idx] + dx[f[idx]] * i > wid ||
						y[idx] + dy[f[idx]] * i <= 0 || y[idx] + dy[f[idx]] * i > hig) {
							printf("Robot %d crashes into the wall\n", idx); error = true;
					}
					if (grd[x[idx]+dx[f[idx]]*i][y[idx]+dy[f[idx]]*i]) {
							printf("Robot %d crashes into robot %d\n", idx, grd[x[idx]+dx[f[idx]]*i][y[idx]+dy[f[idx]]*i]);
							error = true;
					}
				}
				if (!error) { grd[x[idx]][y[idx]] = 0; grd[x[idx]+dx[f[idx]]*rpt][y[idx]+dy[f[idx]]*rpt] = idx;
							  x[idx] += dx[f[idx]] * rpt; y[idx] += dy[f[idx]] * rpt; }
				break;
		}
	}
	if (!error) printf("OK\n");
}


int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--) { 
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

