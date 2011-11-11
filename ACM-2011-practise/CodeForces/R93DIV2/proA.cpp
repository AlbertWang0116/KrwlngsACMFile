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
struct pnt { double x, y; };
#define N 10010
pnt p[N];

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

int main() {
	int i, n; double ans, k;
	scanf("%d%lf", &n, &k);
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (ans = i = 0; i < n-1; ++i) ans += getdis(p[i], p[i+1]);
	ans = ans * k / 50.0;
	printf("%.9f\n", ans);
}
