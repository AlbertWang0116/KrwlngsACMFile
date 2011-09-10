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

#define N 200010
const double eps = 1e-6, pi = acos(-1.0);
double ang[N];
int n;

void input()
{
	int i; double da;
	scanf("%d", &n); ang[0] = 0;
	for (i = 1; i <= n; ++i) {
		scanf("%lf", &da); ang[i] = ang[i-1] + da/180.0*pi;
		if (ang[i]-pi>-eps) ang[i]-=2*pi; if (ang[i]+pi<-eps) ang[i]+=2*pi;
	}
}

bool judge(double a1, double a2, double b1, double b2)
{
//	printf("a1:%.3f a2:%.3f b1:%.3f b2:%.3f\n", a1, a2, b1, b2);
	if (fabs(a2-a1)<eps && fabs(b2-b1)<eps && fabs(b1-a1)<eps) return true;
	if (fabs(a2-a1)<eps && (fabs(a1-b1)<eps||fabs(a1-b2)<eps)) return false;
	if (fabs(b2-b1)<eps && (fabs(b1-a1)<eps||fabs(b1-a2)<eps)) return false;
	if (a1-b1>-eps && a1-b2<eps && a2-b1>-eps && a2-b2<eps) return true;
	if (b1-a1>-eps && b1-a2<eps && b2-a1>-eps && b2-a2<eps) return true;
	return false;
}

void conduct()
{
	int i, j; double fl, fh, al, ah;
	sort(ang, ang+n+1);
	for (i = j = 1; i <= n; ++i) if (ang[i]-ang[j-1]>eps) ang[j++] = ang[i]; n = j-1;
//	for (i = 0; i <= n; ++i) printf("ang[%d]=%.3f\n", i, ang[i]);
	for (i = 0; i <= n; ++i) if (ang[i]-ang[0]-pi > -eps) break; 
	if (i > n) { printf("No\n"); return; } j = i;
	fl = ang[0]; fh = ang[j-1]; al = ang[j]; ah = ang[n];
//	printf("fl:%.3f fh:%.3f al:%.3f ah:%.3f\n", fl, fh, al, ah);
	if (judge(fl+pi, fh+pi, al, ah)) { printf("Yes\n"); return; }
	for (i = 0; i <= n; ++i) ang[i+n+1] = ang[i] + 2*pi;
	for (i = 1; i <= n; ++i) {
		while (ang[j]-ang[i]-pi<-eps) ++j;
		fl = ang[i]; fh = ang[j-1]; al = ang[j]; ah = ang[i+n];
//		printf("fl:%.3f fh:%.3f al:%.3f ah:%.3f\n", fl, fh, al, ah);
		if (judge(fl+pi, fh+pi, al, ah)) { printf("Yes\n"); return; }
	} printf("No\n");
}
		 

int main()
{
	int time; scanf("%d", &time);
	while (time--) { input(); conduct(); }
	return 0;
}
