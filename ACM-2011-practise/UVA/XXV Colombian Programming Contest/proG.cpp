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

#define N 100010
int seq[N], val[N], pos[N], rad[N], lft[N], rit[N];
int n, nc, len;

int getmax(int x, int y) { return x > y ? x : y; }
int getmin(int x, int y) { return x < y ? x : y; }

int cmp(const int &x, const int &y) { return val[x] < val[y]; }

int cmp2(const int &x, const int &y) { return rit[x] > rit[y]; }

void conduct()
{
	int i, j, pre, tmp, ans;
	for (i = 0; i < n; ++i) scanf("%d%d", &pos[i], &rad[i]);
	for (i = 0; i < n; ++i) { 
		val[i*2] = lft[i] = getmax(0, pos[i]-rad[i]);
		val[i*2+1] = rit[i] = getmin(len, pos[i]+rad[i]);
	} for (i = 0; i < 2*n; ++i) seq[i] = i; sort(seq, seq+2*n, cmp);
	for (pre = -1, nc = i = 0; i < 2*n; ) {
		tmp = val[seq[i]]-pre-1; if (tmp) nc++; pre = val[seq[i]];
		for (; i < 2*n && val[seq[i]] == pre; ++i) 
			if (seq[i] % 2) rit[seq[i]/2] = nc; else lft[seq[i]/2] = nc;
		nc++;
	} if (len-pre) nc++;
//	for (i = 0; i < n; ++i) printf("%d--->lft:%d,rit:%d\n", i, lft[i], rit[i]);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp2);
	for (i = 0; i < nc; ++i) val[i] = i;
	for (i = 0; i < n; ++i) for (j = lft[seq[i]]; j < rit[seq[i]] && (!(val[j]-j)); ++j) val[j] = rit[seq[i]];
//	for (i = 0; i < nc; ++i) printf("%d ", val[i]); printf("\n");
	for (ans = i = 0; val[i]-i; i = val[i]) ans++;
//	printf("i:%d ans:%d\n", i, ans);
	if (i != nc-1) printf("-1\n"); else printf("%d\n", n-ans);
}

int main()
{
	while (scanf("%d%d", &len, &n) != EOF && (len || n)) conduct();
	return 0;
}
