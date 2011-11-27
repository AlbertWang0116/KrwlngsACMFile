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
struct pnt {
	double x, y;
	bool operator<(const pnt &p) const {
		if (fabs(x-p.x)<eps) return y-p.y<-eps;
		return x-p.x<-eps;
	};
};
#define N 2010
pnt p[N];
double ang[N];
int n;

inline double getmax(const double &x, const double &y) { return x > y ? x : y; }

void conduct() {
	int i, j, k, ret;
	map<double, int>::iterator pos;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y); sort(p, p+n);
	for (ret = i = 0; i < n; ++i) {
		for (j = i+1; j < n; ++j) ang[j-i-1] = atan2(p[j].y-p[i].y, p[j].x-p[i].x);
		sort(ang, ang+n-i-1);
		for (j = k = 1; j < n-i-1; ++j) if (ang[j]-ang[j-1]>eps) { ret = getmax(ret, k); k = 1; } else k++;
		ret = getmax(ret, k);
	} printf("%d\n", ret+1);
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
