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

double a, b, c, d, e, f;

double getang(double a, double b, double c) {
	return acos((a*a+b*b-c*c)/(2.0*a*b));
}

void conduct() {
	double ang1, ang2, ang3, ang, ans;
	ang1 = getang(a, b, d); ang2 = getang(a, c, e); ang3 = getang(b, c, f);
	ang = (ang1+ang2+ang3)/2.0;
	ans = a*b*c*sqrt(sin(ang)*sin(ang-ang1)*sin(ang-ang2)*sin(ang-ang3))/3.0;
	printf("%.4f\n", ans);
}

int main() {
	while (scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f) != EOF) conduct();
	return 0;
}
