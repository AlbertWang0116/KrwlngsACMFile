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

struct pnt { long long x, y; };
#define N 1000010
#define MAX 50000
long long lth[N], pos[N], lft[N], rit[N];
int seq[N], cov[N];
int n;

bool input()
{
	pnt p1, p2;
	n = 0;
	while (scanf("%lld%lld%lld%lld", &p1.x, &p1.y, &p2.x, &p2.y) != EOF && p1.x >= 0 && p1.y >= 0 && p2.x >= 0 && p2.y >= 0) {
		pos[n*2] = p1.x; pos[n*2+1] = p2.x; lft[n] = p1.y; rit[n] = p2.y; n++;
	} if (!n) return false; return true;
}

int cmp(const int &x, const int &y) { return pos[x] < pos[y]; }

long long insert(int id, int lst, int mst, int lft, int rit) {
	if (lft >= mst || lst >= rit) return (cov[id]? mst-lst : lth[id]);
	if (lft <= lst && rit >= mst) { cov[id]++; return mst-lst; }
	lth[id] = insert(id*2+1, lst, (lst+mst)/2, lft, rit) + insert(id*2+2, (lst+mst)/2, mst, lft, rit);
	return (cov[id]? mst-lst : lth[id]);
}

long long remove(int id, int lst, int mst, int lft, int rit) {
	if (lft >= mst || lst >= rit) return (cov[id]? mst-lst : lth[id]);
	if (lft <= lst && rit >= mst) { cov[id]--; return (cov[id]? mst-lst : lth[id]); }
	lth[id] = remove(id*2+1, lst, (lst+mst)/2, lft, rit) + remove(id*2+2, (lst+mst)/2, mst, lft, rit);
	return (cov[id]? mst-lst : lth[id]);
}

void conduct()
{
	int i;
	long long last, ans, len;
	memset(cov, 0, sizeof(cov)); memset(lth, 0, sizeof(lth));
	for (i = 0; i < 2*n; ++i) seq[i] = i; sort(seq, seq+2*n, cmp);
	for (last = pos[seq[0]], ans = len = i = 0; i < 2*n; ++i)
		if (seq[i]%2) {
			ans += len * (pos[seq[i]]-last); last = pos[seq[i]];
			len = remove(0, 0, MAX, lft[seq[i]/2], rit[seq[i]/2]);	
		} else {
			ans += len * (pos[seq[i]]-last); last = pos[seq[i]];
			len = insert(0, 0, MAX, lft[seq[i]/2], rit[seq[i]/2]);
		}
	printf("%lld\n", ans);
}

int main()
{
	while (input()) conduct();
	return 0;
}
