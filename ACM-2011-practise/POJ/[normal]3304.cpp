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

const double eps = 1e-7;
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
	} bool operator<(const pnt &p) const {
		if (fabs(x-p.x)<eps) return y-p.y < -eps;
		return x-p.x < -eps;
	}
};
typedef pnt vec;
#define N 1010
pnt p[N], q[N];
int n;

double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

bool check(pnt p1, pnt p2) {
	if (!(p1<p2) && !(p2<p1)) return false;
	for (int i = 0; i < n; ++i) 
		if (submul(p2-p1, p[i]-p1) * submul(p2-p1, q[i]-p1) > eps) return false;
	return true;
}

void conduct() {
	int i, j; pnt tmp;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
	for (i = 0; i < n; ++i) if (q[i] < p[i]) { tmp = p[i]; p[i] = q[i]; q[i] = tmp; }
	if (n <= 1) { printf("Yes!\n"); return; }
	for (i = 0; i < n; ++i) for (j = i+1; j < n; ++j) {
		if (check(p[i], p[j]) || check(p[i], q[j]) ||
			check(q[i], p[j]) || check(q[i], q[j])) { printf("Yes!\n"); return; }
	} printf("No!\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
