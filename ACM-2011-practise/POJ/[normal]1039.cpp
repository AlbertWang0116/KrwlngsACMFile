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

struct point { double x, y; };
struct vctor { double x, y; };
struct line { double a, b, c; };

#define N 30
#define MAX 1e20
#define eps 1e-6
int n;
point p[N], q[N];

int getmax(int x, int y) { return x > y ? x : y;}

vctor getvec(point p1, point p2)
{
	vctor ret;
	ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y;
	return ret;
}

line getline(point p1, point p2)
{
	line ret;
	ret.a = p1.y - p2.y;
	ret.b = p2.x - p1.x;
	ret.c = ret.a * p1.x + ret.b * p1.y;
	return ret;
}

int submul(vctor v1, vctor v2)
{
	double ret = v1.x * v2.y - v2.x * v1.y;
	if (ret > eps) return 1;
	if (ret < -eps) return -1;
	return 0;
}

point getcrs(line l1, line l2)
{
	point ret;
	ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b); 
	return ret;
}

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%lf %lf", &p[i].x, &p[i].y);
	for (i = 0; i < n; ++i) {q[i] = p[i]; q[i].y = p[i].y-1; }
}

void conduct()
{
	double ans, tmp;
	int i, j, k;
	int mst;
	vctor vec;
	line lne;
	point upcrs, dncrs;
	ans = -MAX;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) if (i != j)
		{
			vec = getvec(p[i], q[j]);
			lne = getline(p[i], q[j]);
			mst = getmax(i, j);
			for (k = 0; k < n; ++k) if (submul(vec, getvec(p[i], p[k])) * submul(vec, getvec(p[i], q[k])) > 0) break;
			if (k <= mst) continue;
			if (k == n) {ans = MAX; break;}
			upcrs = getcrs(lne, getline(p[k-1], p[k]));
			dncrs = getcrs(lne, getline(q[k-1], q[k]));
			if (upcrs.x - p[k-1].x > eps && upcrs.x - p[k].x < -eps) tmp = upcrs.x;
			else tmp = dncrs.x;
			if (tmp > ans) 
			{
				ans = tmp;
//				printf("upidx:%d dnidx:%d k:%d upcrs:%.3f dncrs:%.3f ans:%.3f\n", i, j, k, upcrs.x, dncrs.x, ans);
			}
		}
	if (fabs(ans - MAX) < eps) printf("Through all the pipe.\n");
	else printf("%.2f\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) && n)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

