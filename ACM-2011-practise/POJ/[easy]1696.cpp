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

struct pnt { int x, y; };
typedef pnt vec;
#define square(x) (x)*(x)
#define N 1010
pnt p[N];
int seq[N], ans[N], id[N];
bool vst[N];
int n;

int submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
int dis2(const pnt &p1, const pnt &p2) { return square(p2.x-p1.x)+square(p2.y-p1.y); }

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x; ret.y = p2.y - p1.y; return ret;
}
int cmp(const int &x, const int &y) {
	if (p[x].y == p[y].y) return p[x].x < p[y].x;
	return p[x].y < p[y].y;
}

void conduct()
{
	int i, j, tx;
	vec tv, stv;
	scanf("%d", &n); for (i = 0; i < n; ++i) scanf("%d%d%d", &id[i], &p[i].x, &p[i].y);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
//	printf("seq-->\n"); for (i = 0; i < n; ++i) printf("%d->%d,%d\n", seq[i], p[seq[i]].x, p[seq[i]].y);
	memset(vst, 0, sizeof(vst)); vst[seq[0]] = 1; ans[0] = seq[0];
	for (i = 1; i < n; ++i) {
		for (ans[i] = -1, j = 0; j < n; ++j) if (!vst[j]) {
			tv = getvec(p[ans[i-1]], p[j]);
			if (ans[i] == -1) { stv = tv; ans[i] = j; continue;} else tx = submul(stv, tv);
			if (tx < 0 || (tx == 0 && dis2(p[j], p[ans[i-1]]) < dis2(p[ans[i]], p[ans[i-1]]))) { stv = tv; ans[i] = j; }
		} vst[ans[i]] = 1;
	} printf("%d", n); for (i = 0; i < n; ++i) printf(" %d", id[ans[i]]); printf("\n");
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
