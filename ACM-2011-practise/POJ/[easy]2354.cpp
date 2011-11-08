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

#define L 50
char str[L], str1[L], str2[L], pos1[L], pos2[L], pos3[L], pos4[L];
const double R = 6875.0 / 2.0, pi = acos(-1.0), eps = 5e-3;
double tmp;

double getver(double ang, double mnt, double sec, bool N) {
	ang = (ang + mnt / 60.0 + sec / 3600.0) / 180.0 * pi;
	double ret = cos(ang); tmp = ret; ret = sqrt(1 - ret * ret);
	if (N) return ret; else return -ret;
}

void gethor(double ang, double mnt, double sec, bool E, double &x, double &y) {
	ang = (ang+mnt / 60.0 + sec / 3600.0) / 180.0 * pi;
	if (!E) ang = -ang;
	x = cos(ang) * tmp; y = sin(ang) * tmp;
}

void conduct()
{
	int i; char chr1, chr2, chr3; double x1, x2, y1, y2, z1, z2, ans;
	double ang1, ang2, ang3, ang4, mnt1, mnt2, mnt3, mnt4, sec1, sec2, sec3, sec4;
	for (i = 0; i < 7; ++i) scanf("%s", str);
	scanf("%s", str); sscanf(str, "%lf%c%lf%c%lf%c", &ang1, &chr1, &mnt1, &chr2, &sec1, &chr3);
//	printf("str:%s\n", str);
	scanf("%s", pos1); scanf("%s", str);
	scanf("%s", str); sscanf(str, "%lf%c%lf%c%lf%c", &ang2, &chr1, &mnt2, &chr2, &sec2, &chr3);
//	printf("str:%s\n", str);
	scanf("%s", pos2); for (i = 0; i < 5; ++i) scanf("%s", str);
	scanf("%s", str); sscanf(str, "%lf%c%lf%c%lf%c", &ang3, &chr1, &mnt3, &chr2, &sec3, &chr3);
//	printf("str:%s\n", str);
	scanf("%s", pos3); scanf("%s", str);
	scanf("%s", str); sscanf(str, "%lf%c%lf%c%lf%c", &ang4, &chr1, &mnt4, &chr2, &sec4, &chr3);
//	printf("str:%s\n", str);
	scanf("%s", pos4); scanf("%s", str);
//	printf("str:%s\n", str);
	z1 = getver(ang1, mnt1, sec1, pos1[0] == 'N'); gethor(ang2, mnt2, sec2, pos2[0] == 'E', x1, y1);
	z2 = getver(ang3, mnt3, sec3, pos3[0] == 'N'); gethor(ang4, mnt4, sec4, pos4[0] == 'E', x2, y2);
//	printf("x1:%.4f y1:%.4f z2:%.4f\n x2:%.4f y2:%.4f z2:%.4f\n", x1, y1, z1, x2, y2, z2);
//	printf("ang:%.4f\n", acos(x1*x2+y1*y2+z1*z2));
//	printf("sqr1:%.4f, sqr2:%.4f\n", x1*x1+y1*y1+z1*z1, x2*x2+y2*y2+z2*z2);
	ans = acos(x1*x2 + y1*y2 + z1*z2) * R;
	printf("The distance to the iceberg: %.2f miles.\n", ans);
	if (ans-100.0<-eps) printf("DANGER!\n");
}

int main()
{
	while (scanf("%s%s", str1, str2) != EOF) conduct();
	return 0;
}
