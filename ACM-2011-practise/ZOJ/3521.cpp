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

#define square(x) (x)*(x)
struct pnt { long long x, y; };
#define N 50010
pnt p[N], cen;
int seq[2*N], rt[N], stk[N], hp[2*N];
long long val[2*N], r, wid;
bool col[N];
int n;
map<long long, int> st;

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%lld%lld", &p[i].x, &p[i].y);
	scanf("%lld%lld", &cen.x, &cen.y);
}

int cmp(const int &x, const int &y) {
	if (val[x] == val[y]) return (x % 2 == 0);
	return val[x] < val[y];
}

int root(int x)
{
	for (stk[0] = 0; rt[x] != x; x = rt[x]) stk[++stk[0]] = x;
	for (int i = 1; i <= stk[0]; ++i) rt[stk[i]] = x; return x;
}

void update(int idx)
{
	int ele, i, j; ele = hp[idx];
	for (i = idx, j = (i >> 1); j; i = j, j = (i >> 1))
		if (cmp(ele, hp[j])) hp[i] = hp[j]; else break;
	hp[i] = ele;
}

int getele()
{
	int ret = hp[1], ele = hp[hp[0]--], i, j;
	for (i = 1, j = (i << 1); j <= hp[0]; i = j, j = (i << 1)) {
		if (j < hp[0] && cmp(hp[j+1], hp[j])) j++;
		if (cmp(hp[j], ele)) hp[i] = hp[j]; else break;
	} hp[i] = ele; return ret;
}

void conduct()
{
	int i, ans, v;
	map<long long, int>::iterator pos, lft, rit;
	for (i = 0; i < n; ++i) { p[i].x *= 2; p[i].y *= 2; }
	cen.x *= 2; cen.y *= 2; r *= 2;
	for (i = 0; i < n; ++i) { val[i*2] = p[i].x; val[i*2+1] = p[i].x + wid; }
	for (i = hp[0] = 0; i < 2*n; ++i) { hp[++hp[0]] = i; update(hp[0]); }
	for (i = 0; i < 2*n; ++i) seq[i] = getele(); 
//	for (i = 0; i < 2*n; ++i) seq[i] = i; std::sort(seq, seq+2*n, cmp);
	st.clear(); for (i = 0; i < n; ++i) rt[i] = i;
	for (i = 0; i < 2*n; ++i)
		if (seq[i]%2) {
			v = seq[i] / 2; pos = st.find(p[v].y);
			if (pos != st.end() && pos->second == v) st.erase(pos);
		} else {
			v = seq[i] / 2;
			if ((pos = st.find(p[v].y)) != st.end()) {
				if (root(v) != root(pos->second)) rt[rt[pos->second]] = rt[v];
				pos->second = v;
			} else pos = st.insert(pair<long long, int>(p[v].y, v)).first;
			lft = rit = pos; if (lft != st.begin()) lft--; rit++;
			if (pos != st.begin() && llabs(pos->first-lft->first) <= wid)
				if (root(pos->second) != root(lft->second)) rt[rt[lft->second]] = rt[pos->second];
			if (rit != st.end() && llabs(pos->first-rit->first) <= wid)
				if (root(pos->second) != root(rit->second)) rt[rt[rit->second]] = rt[pos->second];
		}
	memset(col, 0, sizeof(col));
	for (i = 0; i < n; ++i) if (square(r) - square(p[i].x-cen.x) >= square(p[i].y-cen.y)) col[root(i)] = 1;
	for (ans = i = 0; i < n; ++i) if (col[root(i)]) ans++; printf("%d\n", ans);
}

int main()
{
	while (scanf("%d%lld%lld", &n, &r, &wid) != EOF) {
		input();
		conduct();
	} return 0;
}
