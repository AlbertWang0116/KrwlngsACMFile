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

#define N 210
#define M 10010
int cov[M], lft[N], rit[N], seq[N], col[N];
double len[M], dep[M], x[N], y[N], pos[N], ymp[N];
int n, m;
const double eps = 1e-6;

int ycmp(const int &p1, const int &p2) { return y[p1] < y[p2]; }
int seqcmp(const int &x, const int &y) { return pos[x] < pos[y]; }

void st_insert(int seg, int x, int y, int lft, int rit)
{
//	printf("%d %d %d %d\n", x, y, lft, rit);
	int mid;
	if (lft >= y || rit <= x) return;
	if (x >= lft && y <= rit) { cov[seg]++; len[seg] = ymp[y] - ymp[x]; return; }
	mid = (y + x) >> 1;
	st_insert(seg*2, x, mid, lft, rit); st_insert(seg*2+1, mid, y, lft, rit);
	dep[seg] = len[seg*2] + len[seg*2+1]; if (!cov[seg]) len[seg] = dep[seg];
}

void st_delete(int seg, int x, int y, int lft, int rit)
{
	int mid;
	if (lft >= y || rit <= x) return;
	if (x >= lft && y <= rit) { cov[seg]--; if (!cov[seg]) len[seg] = dep[seg]; return; }
	mid = (y + x) >> 1;
	st_delete(seg*2, x, mid, lft, rit); st_delete(seg*2+1, mid, y, lft, rit);
	dep[seg] = len[seg*2] + len[seg*2+1]; if (!cov[seg]) len[seg] = dep[seg];
}

void input()
{
	int i;
	for (i = 1; i <= n; ++i) scanf("%lf%lf%lf%lf", &x[i*2-1], &y[i*2-1], &x[i*2], &y[i*2]);
}

void conduct()
{
	int i, j; double ans, last;
	for (i = 1; i <= 2*n; ++i) seq[i] = i; std::sort(seq+1, seq+2*n+1, ycmp);
	ymp[1] = y[seq[1]]; m = col[seq[1]] = 1;
	for (i = 2; i <= 2*n; ++i) if (y[seq[i]] - y[seq[i-1]] < eps) col[seq[i]] = m;
							   else { col[seq[i]] = ++m; ymp[m] = y[seq[i]]; }
//	for (i = 1; i <= m; ++i) printf("ymp[%d]=%.2f\n", i, ymp[i]);
//	for (i = 1; i <= 2*n; ++i) printf("col[%d]=%d\n", i, col[i]);
	for (i = 1; i <= n; ++i) {
		pos[2*i-1] = x[2*i-1]; lft[2*i-1] = col[2*i-1]; rit[2*i-1] = col[2*i];
		pos[2*i] = x[2*i]; lft[2*i] = col[2*i-1]; rit[2*i] = col[2*i];
	}
	for (i = 1; i <= 2*n; ++i) seq[i] = i; std::sort(seq+1, seq+2*n+1, seqcmp);
	memset(len, 0, sizeof(len)); memset(dep, 0, sizeof(dep));
	memset(cov, 0, sizeof(cov)); last = pos[seq[1]]; ans = 0;
	for (i = 1; i <= 2*n; ++i) {
//		printf("len[%d]:%.2f\n", i, len[1]);
		ans += (pos[seq[i]] - last) * len[1]; last = pos[seq[i]];
		for (j = i; j <= 2*n; ++j) {
			if (seq[j] % 2) st_insert(1, 1, m, lft[seq[j]], rit[seq[j]]);
			else st_delete(1, 1, m, lft[seq[j]], rit[seq[j]]);
			if (pos[seq[j+1]] - pos[seq[j]] > eps) break;
		} i = j;
	}
	printf("Total explored area: %.2f\n\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time = 0;
	while (scanf("%d", &n) != EOF && n) {
		printf("Test case #%d\n", ++time);
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

