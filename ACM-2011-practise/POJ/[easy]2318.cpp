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

struct pnt {
	int x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x =  x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
#define N 50010
pnt p[N], q[N], pos;
int cnt[N];
int n, m;

int submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

void conduct() {
	int i, lst, mst, mid, x1, x2, y1, y2;
	scanf("%d%d%d%d%d", &m, &x1, &y1, &x2, &y2);
	p[0] = (pnt){ x1, y2 }; q[0] = (pnt){ x1, y1 };
	for (i = 1; i <= n; ++i) {
		scanf("%d%d", &x1, &x2);
		p[i] = (pnt){ x2, y2 }; q[i] = (pnt){ x1, y1 };
	} memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < m; ++i) {
		scanf("%d%d", &pos.x, &pos.y);
		lst = 0; mst = n;
		while (lst < mst) {
			mid = (lst+mst)/2+1;
			if (submul(q[mid]-p[mid], pos-p[mid]) > 0) mst = mid-1; else lst = mid;
		} cnt[lst]++;
	} for (i = 0; i <= n; ++i) printf("%d: %d\n", i, cnt[i]);
}

int main() {
	int time = 0;
	while (scanf("%d", &n) != EOF && n) {
		if (time) printf("\n"); else time = 1;
		conduct();
	} return 0;
}
