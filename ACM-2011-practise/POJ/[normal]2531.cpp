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

#define getmax(x, y) (x)>(y)?(x):(y)
#define N 110
#define M (1<<20)+10
int dis[N][N], bit[N], len[M];
bool vst[M];
int n;

void input()
{
	int i, j;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) for (j = 0; j < n; ++j) scanf("%d", &dis[i][j]);
	for (i = 0; i <= n; ++i) bit[i] = (1 << i);
}

void conduct()
{
	int i, j, des, ans, val;
	ans = 0;
	memset(vst, false, sizeof(vst)); len[0] = 0; vst[0] = true;
	for (val = 0; val < bit[n]; ++val)
		for (i = 0; i < n; ++i) if (!(val & bit[i])) {
			des = val + (1 << i); if (vst[des]) continue;
		 	vst[des] = true; len[des] = len[val];
			for (j = 0; j < n; ++j) if (val & bit[j]) len[des] -= dis[i][j]; else len[des] += dis[i][j];
			ans = getmax(ans, len[des]);
		}
//	for (i = 0; i < bit[n]; ++i) printf("%d:%d\n", i, len[i]);
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

