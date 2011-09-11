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

#define square(x) (x)*(x)
struct pnt {
	double x, y;
	pnt operator+(const pnt &p) {
		pnt ret; ret.x = p.x + x;
		ret.y = p.y + y; return ret;
	}
	pnt operator*(const double &c) {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	}
};
typedef pnt vec;
const double eps = 1e-10, inf = 1e10;
pnt p1, p2;
vec l;
double vd, vb, len;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p1.x-p2.x)+square(p1.y-p2.y)); }

bool input()
{
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &l.x, &l.y, &vd, &vb, &len);
	if (fabs(p1.x)<eps && fabs(p1.y) < eps && fabs(p2.x)<eps && fabs(p2.y)<eps && fabs(l.x)<eps &&
		fabs(l.y)<eps && fabs(vd)<eps && fabs(vb)<eps && fabs(len) < eps) return false;
	return true;
}

void conduct()
{
	double mst, lst, mid, dis, sht;
	pnt pa;
	lst = 0; mst = inf; sht = len / vb;
	while (mst-lst>eps) {
		mid = (mst+lst) / 2; pa = p1 + l * mid; dis = fabs(getdis(p2, pa) - len);
		if (mid - dis / vd - sht> eps) mst = mid; else lst = mid;
	} printf("%.3f %.3f\n", len, mid);
}

int main()
{
	while (input()) conduct();
	return 0;
}
