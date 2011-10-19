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

double a, b, c, len;
const double eps = 1e-9, pi = acos(-1.0);

bool input()
{
	scanf("%lf%lf%lf%lf", &a, &b, &c, &len);
	return (fabs(a) > eps);
}

void conduct()
{
	double tr, tt, ans;
	double p = (a+b+c) / 2, st = sqrt(p*(p-a)*(p-b)*(p-c));
	double r = st / p, sc = pi * r * r, cc = 2 * pi * r;
	if (len - cc < eps) { printf("%.2f\n", len * len / (4 * pi)); return; }
	else if (fabs(len-p*2) < eps) { printf("%.2f\n", st); return; }
	tr = (len - 2*p) * r / (cc - 2*p); tt = r / tr;
	ans = st - st / tt / tt + tr * tr * pi; printf("%.2f\n", ans);
}

int main()
{
	int time = 0;
	while (input()) {
		printf("Case %d: ", ++time);
		conduct();
	} return 0;
}
