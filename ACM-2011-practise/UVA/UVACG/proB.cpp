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
const double pi = acos(-1.0), eps = 1e-6;
double a, b, c, d, e;

bool input()
{
	scanf("%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e);
	if (fabs(a)<eps && fabs(b)<eps && fabs(c)<eps && fabs(d)<eps && fabs(e)<eps) return false;
	return true;
}

void conduct()
{
	double A, B, C, ret;
	a = a / 180 * pi; b = b / 180 * pi; c = c / 180 * pi; d = d / 180 * pi; e = e / 180 * pi;
	if (fabs(a+b+c+d+e-pi) > eps) { printf("Impossible\n"); return; }
	A = sin(a)/sin(a+d)*sin(e); B = sin(a)/sin(a+b)*sin(d+e);
	C = sqrt(square(A)+square(B)-2*A*B*cos(b)); ret = acos((square(B)+square(C)-square(A))/(2*B*C));
	ret = ret / pi * 180; printf("%.2f\n", ret);
}

int main()
{
	while (input()) conduct();
	return 0;
}
