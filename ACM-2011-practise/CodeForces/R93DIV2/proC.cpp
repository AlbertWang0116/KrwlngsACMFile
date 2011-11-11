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

double t1, t2, x1, x2, t0;
const double eps = 1e-8, inf = 1e8;

void conduct() {
	double i, j, dlt, val, ret; int r1, r2;
	if (fabs(t1-t0)<eps && fabs(t2-t0)<eps) { printf("%d %d\n", (int)(x1+eps), (int)(x2+eps)); return; }
	if (fabs(t1-t0)<eps) { printf("%d %d\n", (int)(x1+eps), 0); return; }
	if (fabs(t2-t0)<eps) { printf("%d %d\n", 0, (int)(x2+eps)); return; }
	dlt = (t2-t1)/(t2-t0)-1.0;
	for (ret = inf, i = 0.0; (x1-i) > -eps; i = i+1.0) {
		j = ceil(dlt*i-eps); if (j-x2>eps) break;
		val = (t1*i+t2*j)/(i+j); if (val-ret < eps) { ret = val; r1 = (int)(i+eps); r2 = (int)(j+eps); }
	} dlt = (t2-t1)/(t0-t1)-1.0; 
	for (i = 0.0; (x2-i) > -eps; i = i+1.0) {
		j = floor(dlt*i+eps); if (j-x1>eps) j = x1;
		val = (t1*j+t2*i)/(i+j); if (val-ret < eps) { ret = val; r1 = (int)(j+eps); r2 = (int)(i+eps); } 
	} printf("%d %d\n", r1, r2);
}

int main() {
	while (scanf("%lf%lf%lf%lf%lf", &t1, &t2, &x1, &x2, &t0) != EOF) conduct();
	return 0;
}
