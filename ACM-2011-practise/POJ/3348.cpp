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
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const int c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const int c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
#define N 10010
pnt p[N];
int seq[N], tmp[N];
int n;

int submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

int cmp(const int &i, const int &j) {
	if (p[i].y == p[j].y) return p[i].x<p[j].x;
	return p[i].y<p[j].y;
}

void conduct() {
	int i, top, bot, ret;
	for (i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	top = bot = 0; tmp[0] = seq[0];
	for (i = 1; i < n; ++i) {
		while (top > bot && submul(p[tmp[top]]-p[tmp[top-1]], p[seq[i]]-p[tmp[top]]) <= 0) --top;
		tmp[++top] = seq[i];
	} bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && submul(p[tmp[top]]-p[tmp[top-1]], p[seq[i]]-p[tmp[top]]) <= 0) --top;
		tmp[++top] = seq[i];
	} n = top;
	for (ret = i = 0; i < n; ++i) ret += submul(p[tmp[i]], p[tmp[i+1]]);
	ret /= 2; ret /= 50; printf("%d\n", ret);
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
