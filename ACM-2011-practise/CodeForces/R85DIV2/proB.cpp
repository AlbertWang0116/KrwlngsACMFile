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

int main()
{
	int n, x, y, dx, dy;
	while (scanf("%d%d%d", &n, &x, &y) != EOF) {
		dx = n-x+1; dy = n-y+1;
		if (abs(dx-x)<=1 && abs(dy-y)<=1) printf("NO\n");
		else printf("YES\n");
	} return 0;
}
