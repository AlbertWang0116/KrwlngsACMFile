#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

struct point { int x, y; };
#define vctor point
#define N 1010
#define M 100010
#define MAX 1000000
point p[N];
int xcov[M], ycov[M];
bool cov[N][N];
int n;

vctor getvec(point p1, point p2)
{
	vctor ret;
	ret.x = p2.x - p1.x; ret.y = p2.y - p1.y;
	return ret;
}

int cmp(point p1, point p2)
{
	if (p1.y > p2.y) return 1; if (p1.y < p2.y) return -1;
	if (p1.x > p2.x) return 1; if (p1.x < p2.x) return -1;
	return 0;
}

void getsort(int x, int y)
{
	if (x >= y) return;
	int i, j;
	point k;
	i = rand() % (y-x) + x;
	k = p[i];
	p[i] = p[x];
	i = x;
	j = y;
	while (i < j)
	{
		while (i < j && cmp(p[j], k) >= 0) --j;
		p[i] = p[j];
		while (i < j && cmp(p[i], k) <= 0) ++i;
		p[j] = p[i];

	}
	p[i] = k;
	getsort(x, i-1);
	getsort(j+1, y);
}

bool find(point pnt, int x, int y)
{
	int ret, mid;
	if (x > y) return false;
	mid = (x + y) / 2; ret = cmp(pnt, p[mid]);
	switch (ret)
	{
		case 0: return true; break;
		case 1: return find(pnt, mid+1, y); break;
		case -1: return find(pnt, x, mid-1); break;
	}
}

bool exist(point pnt, int x, int y)
{
	pnt.x += x; pnt.y += y;
	if (pnt.x < 0 || pnt.y < 0) return false;
	if (xcov[pnt.x] && ycov[pnt.y] && cov[xcov[pnt.x]][ycov[pnt.y]]) return true;
	return false;
}

void input()
{
	int i;
	int xmin, ymin;
	for (i = 0; i < n; ++i) scanf("%d %d", &p[i].x, &p[i].y);
	xmin = MAX; ymin = MAX;
	for (i = 0; i < n; ++i)
	{
		if (p[i].x < xmin) xmin = p[i].x;
		if (p[i].y < ymin) ymin = p[i].y;
	}
	for (i = 0; i < n; ++i) { p[i].x -= xmin; p[i].y -= ymin; }
	memset(xcov, 0, sizeof(xcov)); memset(ycov, 0, sizeof(ycov));
	for (i = 0; i < n; ++i) { xcov[p[i].x] = i+1; ycov[p[i].y] = i+1; }
	memset(cov, false, sizeof(cov));
	for (i = 0; i < n; ++i) cov[xcov[p[i].x]][ycov[p[i].y]] = true;
}

void conduct()
{
	int ans, i, j;
	vctor v;
	ans = 0;
 	for (i = 0; i < n; ++i)
		for (j = i+1; j < n; ++j)
		{
			v = getvec(p[i], p[j]);
			if (exist(p[i], -v.y, v.x) && exist(p[j], -v.y, v.x)) ans++;
			if (exist(p[i], v.y, -v.x) && exist(p[j], v.y, -v.x)) ans++;
		}
	ans /= 4;
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	srand(time(0));
	while (scanf("%d", &n) != EOF && n)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

