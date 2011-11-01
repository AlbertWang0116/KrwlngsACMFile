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

const double eps = 1e-11, pi = acos(-1.0);
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
		if (fabs(y-p.y)<eps) return x-p.x<-eps;
		return y-p.y<-eps;
	}
};
typedef pnt vec;
#define N 1010
#define M 1000010
pnt p[N], mid[M];
int n, m;

void conduct()
{
	int i, j, ans, cnt;
	scanf("%d", &n); for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (m = i = 0; i < n; ++i) for (j = i+1; j < n; ++j) mid[m++] = (p[i]+p[j]) / 2;
	sort(mid, mid+m);
	for (ans = i = 0; i < m; ) {
		for (cnt = 1, ++i; i < m && fabs(mid[i].x-mid[i-1].x)<eps && fabs(mid[i].y-mid[i-1].y)<eps; ++i) cnt++;
		ans += cnt * (cnt-1) / 2;
	} printf("%d\n", ans);
}

int main()
{
	int time; scanf("%d", &time);
	for (int i = 1; i <= time; ++i) conduct();
	return 0;
}
