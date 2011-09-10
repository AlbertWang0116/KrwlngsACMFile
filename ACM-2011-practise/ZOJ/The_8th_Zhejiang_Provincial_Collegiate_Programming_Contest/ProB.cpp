#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define eps 1e-6

void conduct()
{
	double a, b, c, d, e, f, aa, ac;
	scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f);
	aa = fabs(a);
	ac = fabs(c);
	if (aa < eps || ac < eps) cout << "parabola" << endl;
	else if (fabs(a/aa - c/ac) > eps) cout << "hyperbola" << endl;
	else if (fabs(a - c) < eps) cout << "circle" << endl;
	else cout << "ellipse" << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--) conduct();
	//fclose(stdin);
	//fclose(stdout);
}


