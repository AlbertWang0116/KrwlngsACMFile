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
#define N 100010
int n;
point p[N], stk[N];

int getmax(int x, int y) {return x > y ? x : y;}

int cmp(point p1, point p2)
{
	if (p1.y < p2.y) return -1;
	if (p1.y > p2.y) return 1;
	if (p1.x < p2.x) return -1;
	if (p1.x > p2.x) return 1;
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
	return v1.x * v2.y - v2.x * v1.y;
}

int getdis(point p1, point p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%d %d", &p[i].x, &p[i].y);
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

void transcvx()
{
	int top, bot;
	int i;
	top = 0;
	stk[0] = p[0];
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
	for (i = 0; i <= n; ++i) p[i] = stk[i];
}

void rotate()
{
	if (n == 2) { cout << getdis(p[0], p[1]) << endl; return; }
	int top, ans;
	int i;
	top = 0;
	ans = 0;
	for (i = 0; i < n; ++i)
		while (true)
		{
			ans = getmax(ans, getdis(p[i], p[top]));
			if (submul(getvec(p[i], p[i+1]), getvec(p[i], p[top])) <= submul(getvec(p[i], p[i+1]), getvec(p[i], p[top+1]))) top = (top + 1) % n;
			else break;
		}
	cout << ans << endl;
}

void conduct()
{
	getsort(0, n-1);
	transcvx();
	rotate();
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

