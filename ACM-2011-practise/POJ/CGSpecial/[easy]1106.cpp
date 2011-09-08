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

struct pnt { double x, y; };
#define N 1010
#define getmax(x,y) (x) > (y) ? (x) : (y)
pnt p[N], ctr;
int n;
bool use[N];
double r;
const double eps = 1e-8;

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
}

int judge(int id)
{
	double ang = -atan2(p[id].y, p[id].x);
	int ret = 0, i;
	for (i = 0; i < n; ++i) if (use[i] && p[i].x*sin(ang) + p[i].y*cos(ang) > -eps) ++ret;
	return ret;
}

void conduct()
{
	int i, ans;
	for (i = 0; i < n; ++i) { p[i].x -= ctr.x; p[i].y -= ctr.y; }
	memset(use, true, sizeof(use));
	for (i = 0; i < n; ++i) if (p[i].x*p[i].x + p[i].y*p[i].y - r*r > eps) use[i] = false;
	ans = 0;
	for (i = 0; i < n; ++i) if (use[i]) ans = getmax(judge(i), ans);
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%lf%lf%lf", &ctr.x, &ctr.y, &r) != EOF && r > 0) {
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

