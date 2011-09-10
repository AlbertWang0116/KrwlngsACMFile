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
#define getmax(x, y) (x)>(y)?(x):(y)
#define getmin(x, y) (x)<(y)?(x):(y)
const double eps = 1e-6;

int main()
{
	double a, b, x, y, ang1, ang2, len, tmp;
	int time; scanf("%d", &time);
	while (time--) {
		scanf("%lf%lf%lf%lf", &a, &b, &x, &y);
//		printf("a:%.3f b:%.3f x:%.3f y:%.3f\n", a, b, x, y);
		if (a - b > eps) { tmp = a; a = b; b = tmp; }
		if (x - y > eps) { tmp = x; x = y; y = tmp; }
		if (x - a > eps) { printf("Box cannot be dropped.\n"); continue; }
		if (y - b < eps) { printf("Escape is possible.\n"); continue; }
		ang1 = atan2(x, y); len = sqrt(square(x)+square(y));
		ang2 = asin(a/len); ang2 -= 2 * ang1; len = len * cos(ang2);
//		printf("ang1:%.3f ang2:%.3f len:%.3f\n", ang1, ang2, len);
		if (len - b < eps) printf("Escape is possible.\n"); else printf("Box cannot be dropped.\n");
	} return 0;
}
