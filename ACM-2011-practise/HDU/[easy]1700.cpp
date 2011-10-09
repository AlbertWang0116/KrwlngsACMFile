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

const double eps = 5e-4, pi = acos(-1.0);
struct pnt {
	double x, y;
	bool operator<(const pnt &p) const {
		if (fabs(y-p.y)<eps) return x-p.x < -eps;
		return y-p.y < -eps;
	}
};
typedef pnt vec;

double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

pnt rotate(const pnt &p, double ang) {
	vec v = { sin(ang), cos(ang) };
	pnt ret = { submul(p, v), nummul(p, v) }; return ret;
}

int main()
{
	pnt p1, q1, q2;
	int time; scanf("%d", &time);
	while (time--) {
		scanf("%lf%lf", &p1.x, &p1.y);
		q1 = rotate(p1, 2*pi/3); q2 = rotate(q1, 2*pi/3);
		if (q2 < q1) { p1 = q1; q1 = q2; q2 = p1; }
		printf("%.3f %.3f %.3f %.3f\n", q1.x, q1.y, q2.x, q2.y);
	} return 0;
}
