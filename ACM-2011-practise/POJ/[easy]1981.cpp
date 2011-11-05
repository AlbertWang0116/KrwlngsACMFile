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

const double eps = 1e-9;
#define square(x) (x)*(x)
struct pnt {
	double x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
#define N 400
pnt p[N];
int n;

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
	return v / len;
}

double dis2(const pnt &p1, const pnt &p2) { return square(p2.x-p1.x)+square(p2.y-p1.y); }
double getmax(const double x, const double y) { return x > y ? x : y; }

void conduct()
{
	int i, j, k, ret, cnt; pnt tp, mp; vec v; double td;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y); ret = min(1, n);
	for (i = 0; i < n; ++i) for (j = i+1; j < n; ++j) if (dis2(p[i], p[j])-4.0<eps) {
		mp = (p[i]+p[j])/2.0; v = uvec(p[j]-p[i]); v = (vec){ -v.y, v.x };
		td = sqrt(1.0-dis2(p[i],p[j])/4.0);
		tp = mp + v * td; for (cnt = k = 0; k < n; ++k) if (dis2(p[k], tp)-1.0<eps) cnt++;
		ret = getmax(ret, cnt);
		tp = mp - v * td; for (cnt = k = 0; k < n; ++k) if (dis2(p[k], tp)-1.0<eps) cnt++;
		ret = getmax(ret, cnt);
	} printf("%d\n", ret);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
