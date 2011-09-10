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

struct pnt { double x, y, z; };
pnt p1, p2;
double r1, r2, l, ans;
const double pi = acos(-1.0), eps = 1e-6;

double getdis(pnt p1, pnt p2)
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y) + (p2.z-p1.z)*(p2.z-p1.z));
}

double getans(double r1, double r2, double l)
{
	double v1, v2, v3, v4, v5, v6;
	double l1, l2;
	v1 = pi * r1 * r1 * r1 * 2 / 3; v2 = pi * r2 * r2 * r2 * 2 / 3;
	if (r1 - r2 - l > -eps) return pi * r1 * r1 * r1 * 4 / 3;
	if (r1 + r2 - l < eps) return pi * r1 * r1 * r1 * 4 / 3 + pi * r2 * r2 * r2 * 4 / 3;
	l1 = (l * l + r1 * r1 - r2 * r2) / (2 * l);
	l2 = (l * l - r1 * r1 + r2 * r2) / (2 * l);
	v3 = pi * l1 * l1 * l1 / 3 + pi * l2 * l2 * l2 / 3; v4 = pi * r1 * r1 * l1;
	v5 = pi * r2 * r2 * l2; v6 = pi * r2 * l2 * l2;
	if (l2 > -eps) return v1 + v2 - v3 + v4 + v5;
	else return v1 + v2 - v3 + v4 - v6;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p1.z, &r1, &p2.x, &p2.y, &p2.z, &r2);
		l = getdis(p1, p2);
		if (r1 > r2) ans = getans(r1, r2, l); else ans = getans(r2, r1, l);
		printf("%.2f\n", ans);
	}
//	fclose(stdin);
//	fclose(stdout);
}

