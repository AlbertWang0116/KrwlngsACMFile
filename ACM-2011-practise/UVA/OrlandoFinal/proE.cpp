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

#define MAX LONG_MAX
#define N 2010
int g[N][N];
int wi, hi, n, m, req;

void conduct()
{
	int i, j, ret, tv, dx, dy, hit, wid, sti, stj, edi, edj;
	memset(g, 0, sizeof(g));
	for (i = 0; i < n; ++i) {
		scanf("%d%d", &dx, &dy);
		g[wi+dy-dx][dx+dy]++;
	} n = wi+hi;
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) g[i][j] += g[i-1][j] + g[i][j-1] - g[i-1][j-1];
//	printf("---map---\n"); for (i = n; i >= 1; --i) { for (j = 1; j <= n; ++j) printf("%d ", g[i][j]); printf("\n"); }
	while (req--) {
		scanf("%d", &m); dx = 1; dy = 1;
		for (ret = 0, i = 1; i <= hi; ++i) for (j = 1; j <= wi; ++j) {
			sti = min(i-j+wi+m, n); stj = min(i+j+m, n); edi = max(i-j+wi-m-1, 0); edj = max(i+j-m-1, 0);
//			printf("(%d,%d) st:(%d,%d) ed:(%d,%d)\n", j, i, stj, sti, edj, edi);
			tv = g[sti][stj]-g[edi][stj]-g[sti][edj]+g[edi][edj];
			if (tv > ret) { ret = tv; dx = j; dy = i; }
		} printf("%d (%d,%d)\n", ret, dx, dy);
	}

}
			

int main()
{
	int time = 0;
	while (scanf("%d%d%d%d", &wi, &hi, &n, &req) != EOF && req) {
		printf("Case %d:\n", ++time);
		conduct();
	} return 0;
}
