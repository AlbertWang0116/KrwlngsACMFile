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

#define N 4010
int seq[N];
long long cc[N], cr[N], l[N], r[N], h[N], val[N];
bool f[N][N];
int n, nr, nc;
long long wi, hi;

int cmp(const int &x, const int &y) { return val[x] < val[y]; }

void conduct()
{
	int i, j; long long pre, ans, tc;
	for (i = 0; i < n; ++i) scanf("%lld%lld%lld%lld", &l[i], &h[i], &r[i], &pre);
	for (i = 0; i < n; ++i) { val[i*2] = l[i]; val[i*2+1] = r[i]; }
	for (i = 0; i < 2*n; ++i) seq[i] = i; sort(seq, seq+2*n, cmp);
	for (pre = -1, nc = i = 0; i < 2*n; ) {
		cc[nc] = val[seq[i]]-pre-1; if (cc[nc]) nc++; pre = val[seq[i]];
		for (; i < 2*n && val[seq[i]] == pre; ++i)
			if (seq[i]%2) r[seq[i]/2] = nc; else l[seq[i]/2] = nc;
		cc[nc++] = 1;
	} cc[nc] = wi-pre-1; if (cc[nc]) nc++;
	for (i = 0; i < n; ++i) { seq[i] = i; val[i] = h[i]; } sort(seq, seq+n, cmp);
	for (pre = -1, nr = i = 0; i < n; ) {
		cr[nr] = val[seq[i]]-pre-1; if (cr[nr]) nr++; pre = val[seq[i]];
		for (; i < n && val[seq[i]] == pre; ++i) h[seq[i]] = nr;
		cr[nr++] = 1;
	} cr[nr] = hi-pre-1; if (cr[nr]) nr++;
	memset(f, 1, sizeof(f)); 
	for (i = 0; i <= nr; ++i) f[i][nc] = 0; for (i = 0; i <= nc; ++i) f[nr][i] = 0;
	f[nr-1][nc] = f[nr][nc-1] = 1;
	for (i = 0; i < n; ++i) for (j = l[i]; j <= r[i]; ++j) f[h[i]][j] = 0;
//	printf("\n"); for (i = nr; i >= 0; --i) { for (j = 0; j <= nc; ++j) printf("%d", f[i][j]); printf("\n"); } 
	for (ans = 0, i = nr-1; i >= 0; --i) {
		for (tc = 0, j = nc-1; j >= 0; --j) if (f[i][j]) {
			f[i][j] = (f[i+1][j] || f[i][j+1]);
			if (!f[i][j]) tc += cc[j];
		} ans += tc * cr[i];
	} printf("%lld\n", ans);
}

int main()
{
	int time = 0;
	while (scanf("%lld%lld%d", &hi, &wi, &n) != EOF && (hi || wi || n)) {
		printf("Case %d: ", ++time); conduct();
	} return 0;
}
