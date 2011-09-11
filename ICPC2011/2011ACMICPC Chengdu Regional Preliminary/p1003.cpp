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
#define N 110
const double eps = 1e-10, pi = acos(-1.0);
double e[N], squa[N], mul[N];
int n;

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf", &e[i]); e[n] = e[0];
}

void conduct()
{
	int i; double lst, mst, mid, sum;
	for (i = 0; i < n; ++i) { squa[i] = square(e[i]) + square(e[i+1]); mul[i] = 2 * e[i] * e[i+1]; }
	lst = -1; mst = 1;
	while (mst - lst > eps) {
		mid = (mst + lst) / 2; sum = acos(mid);
		for (i = 1; i < n; ++i) sum += acos((squa[i]-squa[0]+mul[0]*mid) / mul[i]);
		if (2 * pi - sum > eps) mst = mid; else lst = mid;
	}
	if (fabs(mid+1)<eps || fabs(mid-1)<eps) printf("impossible\n"); else printf("%.3f\n", sqrt(squa[0]-mul[0]*mid));
}

int main()
{
	int time; scanf("%d", &time);
	for (int i = 1; i <= time; ++i) {
		printf("Case %d: ", i);
		input(); conduct();
	} return 0;
}
