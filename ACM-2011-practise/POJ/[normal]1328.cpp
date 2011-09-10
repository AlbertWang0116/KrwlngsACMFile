#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;

#define getmin(x, y) (x)<(y)?(x):(y)
#define N 1010
double lft[N], rit[N], x[N], y[N];
const double eps = 1e-6;
int seq[N];
int n, m; double r;

int cmp(const int &x, const int &y) { return lft[x] < lft[y]; }

void input()
{
	int i; r = m;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &x[i], &y[i]);
}

void conduct()
{
	int cnt, i;
	double lst, itv;
	for (i = 0; i < n; ++i) {
		if (fabs(y[i]) - r > eps) { printf("-1\n"); return; }
		itv = sqrt(r*r - y[i]*y[i]);
		lft[i] = x[i] - itv; rit[i] = x[i] + itv;
	}
	for (i = 0; i < n; ++i) seq[i] = i; std::sort(seq, seq+n, cmp); 
	lst = -1e8; cnt = 0;
	for (i = 0; i < n; ++i) if (lst - lft[seq[i]] > -eps) lst = getmin(lst, rit[seq[i]]);
	else { ++cnt; lst = rit[seq[i]]; }
	printf("%d\n", cnt);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time = 0;
	while (scanf("%d%d", &n, &m) != EOF && (n || m)) {
		printf("Case %d: ", ++time);
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

