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
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	}
};
typedef pnt vec;
#define N 110
pnt p[N];
int seq[N], tmp[N];
int n;

int cmp(const int &i, const int &j) {
	if (p[i].y == p[j].y) return p[i].x < p[j].x; return p[i].y < p[j].y;
}

int submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

int main()
{
	int i, j, top, bot;
	n = 0; while (scanf("%d%d", &p[n].x, &p[n].y) != EOF) n++;
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	top = bot = 0; tmp[0] = seq[0];
	for (i = 1; i < n; ++i) {
		while (top > bot && submul(p[tmp[top]]-p[tmp[top-1]], p[seq[i]]-p[tmp[top]]) < 0) --top;
		tmp[++top] = seq[i];
	} bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && submul(p[tmp[top]]-p[tmp[top-1]], p[seq[i]]-p[tmp[top]]) < 0) --top;
		tmp[++top] = seq[i];
	} n = top;
	for (i = 0; i < n; ++i) if (p[tmp[i]].x == 0 && p[tmp[i]].y == 0) break;
	for (j = 0; j < n; ++j) printf("(%d,%d)\n", p[tmp[(i+j)%n]].x, p[tmp[(i+j)%n]].y);
}
