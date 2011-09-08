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
#define N 1010
pnt p[N];
int n;

int gcd(int x, int y) { if (y == 0) return x; else return gcd(y, x % y); }

int submul(vec v1, vec v2) { return v1.x * v2.y - v2.x * v1.y; }

void conduct()
{
	int i, ec, area, dx, dy;
	p[0].x = 0; p[0].y = 0;
	scanf("%d", &n); ec = 0; area = 0;
	for (i = 1; i <= n; ++i) {
		scanf("%d%d", &dx, &dy);
		p[i].x = p[i-1].x + dx; p[i].y = p[i-1].y + dy;
		if (!dx) ec += abs(dy); else if (!dy) ec += abs(dx); else ec += gcd(abs(dx), abs(dy));
//		printf("dx:%d dy:%d\n", dx, dy);
		area += submul(p[i-1], p[i]);
	}
	printf("%d %d %.1f\n\n", (area-ec) / 2 + 1, ec, (double)area / 2);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	for (int i = 1; i <= time; ++i) {
		printf("Scenario #%d:\n", i);
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

