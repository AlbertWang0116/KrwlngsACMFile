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
#define square(x) (x)*(x)
double eps = 1e-6;
pnt a, b, c;
double slp;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

void input()
{
	scanf("%lf", &slp);
	scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
}

void conduct()
{
	double ang; pnt tmp;
	ang = atan(slp); ang = -ang;
	a.x -= c.x; a.y -= c.y; b.x -= c.x; b.y -= c.y;
	tmp.x = a.x * cos(ang) - a.y * sin(ang); tmp.y = a.x * sin(ang) + a.y * cos(ang); a = tmp;
	tmp.x = b.x * cos(ang) - b.y * sin(ang); tmp.y = b.x * sin(ang) + b.y * cos(ang); b = tmp;
	if (a.y * b.y < eps) printf("%.2f\n", getdis(a, b));
	else { a.y = -a.y; printf("%.2f\n", getdis(a, b)); }
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) { input(); conduct(); }
	return 0;
}
