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

struct pnt { double x, y; };
#define square(x) (x)*(x)
#define N 100010
const double pi = acos(-1.0), eps = 1e-9;
pnt p1, p2;
double edg[N], ang[N];
int n;

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }
double triarea(double a, double b, double c) {
	double d = (a+b+c) / 2;
	return sqrt(d*(d-a)*(d-b)*(d-c));
}

bool input()
{
	scanf("%lf%lf%lf%lf%d", &p1.x, &p1.y, &p2.x, &p2.y, &n);
	if (!n) return false; return true;
}

void conduct()
{
	double len, tang, c, ret; int i;
	len = getdis(p1, p2);
	if (n == 3) { printf("%.6f\n", triarea(len, len, len)); return; }
	tang = (n-2)*pi/n; ang[0] = 0; edg[0] = 1.0;
	for (i = 1; i < n/2; ++i) {
		edg[i] = sqrt(square(edg[i-1])+square(edg[0]) - 2*edg[i-1]*edg[0]*cos(tang-ang[i-1]));
		ang[i] = acos((square(edg[i])+square(edg[0])-square(edg[i-1]))/(2*edg[i]*edg[0]));
//		printf("%d: edg=%.3f,ang=%.3f\n", i, edg[i], ang[i]);
	} c = len / edg[n/2-1]; for (i = 0; i < n/2; ++i) edg[i] *= c;
	for (ret = i = 0; i < n/2-1; ++i) ret += triarea(edg[0], edg[i], edg[i+1]); ret *= 2;
	if (n % 2) ret += triarea(edg[0], edg[n/2-1], edg[n/2-1]); printf("%.6f\n", ret);
}

int main()
{
	while (input()) conduct();
	return 0;
}
