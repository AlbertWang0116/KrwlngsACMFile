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

#define L(i) (i) << 1
#define R(i) ((i) << 1)+1
#define N 100010
#define RR 725
#define LL 105
int f[LL][RR], g[RR][LL], hash[RR][LL];
int seq[N], que[N], cov[N], val[N], ang[N], pos[N], cnt[N];
int n, m, mst;

int getmax(int x, int y) { return x > y ? x : y; }
int cmp(const int &x, const int &y) { return ang[x] < ang[y]; }

int cmp2(const int &x, const int &y) {
	if (val[x] == val[y]) return (x%2 == 0 && y%2 != 0);
	return val[x] < val[y];
}

int insert(int id, int lft, int rit, int lst, int mst, int cnt) {
//	if (id == 1) printf("insert:<%d,%d> --> %d-%d, lft, rit, lst, mst\n", lft, rit, lst, mst);
	if (lst > rit || lft > mst) return val[id];
	if (lst <= lft && mst >= rit) { cov[id] += cnt; val[id] += cnt; return val[id]; }
	int mid = (lft+rit) / 2;
	val[id] = getmax(insert(L(id), lft, mid, lst, mst, cnt), insert(R(id), mid+1, rit, lst, mst, cnt)) + cov[id];
	return val[id];
}

void remove(int id, int lft, int rit, int lst, int mst, int cnt) {
//	if (id == 1) printf("remove:<%d,%d> --> %d-%d, lft, rit, lst, mst\n", lft, rit, lst, mst);
	if (lst > rit || lft > mst) return;
	if (lst <= lft && mst >= rit) { cov[id]-=cnt; val[id]-=cnt; return; }
	int mid = (lft+rit) / 2;
	remove(L(id), lft, mid, lst, mst, cnt); remove(R(id), mid+1, rit, lst, mst, cnt);
	val[id] = getmax(val[L(id)], val[R(id)]) + cov[id];
}

/*void conduct()
{
	int i, j, cn, wi, hi, ans, pwi = -1, phi = -1;
	for (i = 0; i < LL; ++i) for (j = 0; j < RR; ++j) f[i][j] = -1;
	for (i = 0; i < n; ++i) scanf("%d%d", &pos[i], &ang[i]);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp); cnt[0] = 1;
	for (i = j = 1; i < n; ++i) if (ang[seq[i]] == ang[seq[j-1]] && pos[seq[i]] == pos[seq[j-1]]) cnt[j-1]++;
	else { seq[j++] = seq[i]; cnt[j-1] = 1; } n = j;
	for (i = 0; i < n; ++i) { seq[i+n] = seq[i]; cnt[i+n] = cnt[i]; }
	scanf("%d", &cn);
	while (cn--) {
		scanf("%d%d", &wi, &hi);
		if (f[wi][hi] != -1) { printf("%d\n", f[wi][hi]); continue; }
		for (i = 0; i < n; ++i) if (ang[seq[i]] > hi) break; m = n; n = i+n;
		for (i = 0; i < n; ++i) { val[i*2] = ang[seq[i]]; val[i*2+1] = ang[seq[i]]+hi; }
		for (i = m; i < n; ++i) { val[i*2] += 360; val[i*2+1] += 360; }
		for (i = 0; i < 2*n; ++i) que[i] = i; sort(que, que+2*n, cmp2);
		memset(val, 0, sizeof(val)); memset(cov, 0, sizeof(cov));
		for (ans = i = 0; i < 2*n; ++i)
			if (que[i] % 2) remove(1, 1, mst, getmax(1, pos[seq[que[i]/2]]-wi+1), pos[seq[que[i]/2]], cnt[seq[que[i]/2]]);
//			if (que[i] % 2) for (j = getmax(1, pos[seq[que[i]/2]]-wi); j <= pos[seq[que[i]/2]]; ++j) val[j]--;
//			else for (j = getmax(1, pos[seq[que[i]/2]]-wi); j <= pos[seq[que[i]/2]]; ++j) { val[j]++; ans = getmax(ans, val[j]); }
			else ans = getmax(ans, insert(1, 1, mst, getmax(1, pos[seq[que[i]/2]]-wi+1), pos[seq[que[i]/2]], cnt[seq[que[i]/2]]));
		printf("%d\n", ans); n = m; f[wi][hi] = ans;
	}
}*/

void conduct()
{
	int i, j, wi, hi, ans;
	memset(g, 0, sizeof(g)); memset(hash, 0, sizeof(hash));
	for (i = 0; i < n; ++i) scanf("%d%d", &pos[i], &ang[i]);
	for (i = 0; i < n; ++i) { ang[i]++; hash[ang[i]][pos[i]]++; hash[ang[i]+360][pos[i]]++; }
	for (i = 1; i < RR; ++i) for (j = 1; j < LL; ++j) g[i][j] = hash[i][j] + g[i-1][j] + g[i][j-1] - g[i-1][j-1];
	scanf("%d", &m);
	while (m--) {
		scanf("%d%d", &wi, &hi); hi++; ans = 0;
		for (i = hi; i < RR; ++i) for (j = wi; j < LL; ++j) ans = getmax(ans, g[i][j]-g[i-hi][j]-g[i][j-wi]+g[i-hi][j-wi]);
		printf("%d\n", ans);
	}
}

int main()
{
	while (scanf("%d%d", &n, &mst) != EOF && (n || mst)) conduct();
	return 0;
}
