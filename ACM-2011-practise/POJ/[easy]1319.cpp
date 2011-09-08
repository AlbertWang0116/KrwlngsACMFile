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

#define getmax(x, y) (x)>(y)?(x):(y)
const double eps = 1e-6, pi = acos(-1.0);
double a, b;

void conduct()
{
	int col1, col2, row1, row2, crs1, crs2, skw1, skw2, crs, skw;
	col1 = floor(b+eps); col2 = floor(b-sin(pi/6)+eps);
	row1 = floor(a+eps); if (a - 1 > eps) row2 = floor((a-1)/cos(pi/6)+eps) + 1; else row2 = row1;
	crs1 = col1 * row1; skw1 = row2/2*col2 + (row2-row2/2)*col1;	
	col1 = floor(a+eps); col2 = floor(a-sin(pi/6)+eps);
	row1 = floor(b+eps); if (b - 1 > eps) row2 = floor((b-1)/cos(pi/6)+eps) + 1; else row2 = row1;
	crs2 = col1 * row1; skw2 = row2/2*col2 + (row2-row2/2)*col1;
	crs = getmax(crs1, crs2); skw = getmax(skw1, skw2);
	if (crs >= skw) printf("%d grid\n", crs);
	else printf("%d skew\n", skw);
}

int main()
{
	while (scanf("%lf%lf", &a, &b) != EOF) conduct();
	return 0;
}
