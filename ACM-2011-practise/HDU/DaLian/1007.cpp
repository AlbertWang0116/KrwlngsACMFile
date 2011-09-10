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
struct pnt { int x, y; };
#define N 1010
pnt p[N];
int seq[2*N], val[2*N];
int n, r;
map<int, int> st;

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
}

int cmp(const int &x, const int &y) {
	if (val[x] == val[y]) return x % 2 == 0;
	return val[x] < val[y];
}

void conduct()
{
	int ans, tmp, i;
	map<int, int>::iterator pos, lft, rit;
	st.clear(); ans = 0;
	for (i = 0; i < n; ++i) { val[i*2] = p[i].x; val[i*2+1] = p[i].x + r; }
	for (i = 0; i < 2*n; ++i) seq[i] = i; sort(seq, seq+2*n, cmp);
	for (i = 0; i < 2*n; ++i)
		if (seq[i]%2) {
			pos = st.find(p[seq[i]/2].y); if (pos == st.end()) continue;
			if (pos->second > 1) pos->second--; else st.erase(pos);
		} else {
			pos = st.find(p[seq[i]/2].y);
			if (pos != st.end()) pos->second = pos->second + 1;
			else pos = st.insert(pair<int, int>(p[seq[i]/2].y, 1)).first;
			lft = rit = pos; tmp = 0; 
			while (lft != st.begin() && rit->first - lft->first <= r) { lft--; tmp += lft->second; }
			if (rit->first - lft->first > r) { tmp -= lft->second; lft++; }
			for (;; tmp -= lft->second, lft++) {
				while (rit != st.end() && rit->first - lft->first <= r) { tmp += rit->second; rit++; }
				ans = getmax(ans, tmp); if (lft == pos) break;
			}
		}
	printf("%d\n", ans);
}

int main()
{
	while (scanf("%d%d", &n, &r) != EOF) { input(); conduct(); }
	printf("\n");
	return 0;
}
