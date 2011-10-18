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
double r, r1, r2, r3;

bool input()
{
	scanf("%lf%lf%lf%lf", &r, &r1, &r2, &r3);
	return r > 0;
}

double getlen(double R, double r) {
	double len = (R+r)*R/(R-r);
	double ret = sqrt(square(len)-square(R));
	return ret;
}

void conduct()
{
	double l1, l2, l3, a, b, c, tot, ans;
	l1 = getlen(r, r1); l2 = getlen(r, r2); l3 = getlen(r, r3);
	a = l1 + l2; b = l2 + l3; c = l3 + l1; tot = (a + b + c) / 2;
	ans = sqrt(tot*(tot-a)*(tot-b)*(tot-c));
	printf("%.2f\n", ans);
}

int main()
{
	int time = 0;
	while (input()) {
		printf("Case %d: ", ++time);
		conduct();
	} return 0;
}
