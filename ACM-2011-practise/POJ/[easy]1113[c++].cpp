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
#define vctor point
#define N 1010
#define eps 1e-6
#define pi 3.14159

int n, m;
point p[N], stk[N];

int cmp(point p1, point p2)
{
	if (p1.y - p2.y < -eps) return -1;
	if (p1.y - p2.y > eps) return 1;
	if (p1.x - p2.x < -eps) return -1;
	if (p1.x - p2.x > eps) return 1;
	return 0;
}

vctor getvec(point p1, point p2)
{
	vctor ret;
	ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y;
	return ret;
}

int submul(vctor v1, vctor v2)
{
	double ret = v1.x * v2.y - v2.x * v1.y;
	if (ret > eps) return 1;
	if (ret < -eps) return -1;
	return 0;
}

double getdis(point p1, point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

void input()
{
	int i;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; ++i) scanf("%lf %lf", &p[i].x, &p[i].y);
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

void getcvx()
{
	int i;
	int top, bot;
//	for (i = 0; i < n; ++i) printf("%.0f %.0f\n", p[i].x, p[i].y);
//	printf("\n");
	stk[0] = p[0];
	top = 0;
	for (i = 1; i < n; ++i)
	{
		while (top > 0 && submul(getvec(stk[top-1], stk[top]), getvec(stk[top], p[i])) <= 0) --top;
		stk[++top] = p[i];
	}
	bot = top;
	for (i = n-2; i >= 0; --i)
	{
		while (top > bot && submul(getvec(stk[top-1], stk[top]), getvec(stk[top], p[i])) <= 0) --top;
		stk[++top] = p[i];
	}
	n = top;
	for (i = 0; i <= top; ++i) p[i] = stk[i];
}

void callen()
{
	double ans;
	int i;
//	for (i = 0; i < n; ++i) printf("%.0f %.0f\n", p[i].x, p[i].y);
	ans = 0;
	for (i = 0; i < n; ++i) ans += getdis(p[i], p[i+1]);
	ans += 2 * m * pi;
	printf("%.0f\n", ans);
}

void conduct()
{
	getsort(0, n-1);
	getcvx();
	callen();
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	srand(time(0));
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

