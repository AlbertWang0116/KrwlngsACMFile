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

int aa, bb, px, py, qx, qy;

void conduct()
{
	int r1, r2, c1, c2;
	r1 = (px+py)/(aa*2); if (px+py < 0) r1--;
    r2 = (qx+qy)/(aa*2); if (qx+qy < 0) r2--;
    c1 = (px-py)/(bb*2); if (px-py < 0) c1--;
    c2 = (qx-qy)/(bb*2); if (qx-qy < 0) c2--;
	printf("%d\n", max(abs(r1-r2),abs(c1-c2)));
}

int main()
{
	while (scanf("%d%d%d%d%d%d", &aa, &bb, &px, &py, &qx, &qy) != EOF) conduct();
	return 0;
}
