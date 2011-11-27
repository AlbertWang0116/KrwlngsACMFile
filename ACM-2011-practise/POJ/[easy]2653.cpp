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
		if (fabs(x-p.x)<eps) return y-p.y<-eps;
		return x-p.x<-eps;
	}
};
typedef pnt vec;
#define N 100010
pnt p[N], q[N];
int n;
map<int, int> curstk;

double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

bool checkcrs(int i, int j) {
	if (q[i] < p[j] || q[j] < p[i]) return false;
	if (submul(q[i]-p[i], p[j]-p[i]) * submul(q[i]-p[i], q[j]-p[i]) > eps) return false;
	if (submul(q[j]-p[j], p[i]-p[j]) * submul(q[j]-p[j], q[i]-p[j]) > eps) return false;
	return true;
}

void conduct() {
	int i; pnt tmp;
	map<int, int>::iterator pos, tp;
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
	for (i = 0; i < n; ++i) if (q[i] < p[i]) { tmp = p[i]; p[i] = q[i]; q[i] = tmp; }
	curstk.clear();
	for (i = 0; i < n; ++i) {
		for (pos = curstk.begin(); pos != curstk.end(); ) {
			tp = pos; ++pos;
			if (checkcrs(i, tp->first)) curstk.erase(tp);
		} curstk.insert(pair<int, int>(i, 0));
	} printf("Top sticks: "); pos = curstk.begin(); printf("%d", pos->first+1);
	while ((++pos) != curstk.end()) printf(", %d", pos->first+1); printf(".\n");
}

int main() {
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
