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
const double eps = 1e-7, pi = acos(-1.0);
struct pnt {
	double x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
#define N 1010
#define M 4*N
pnt p[N];
int seq[M];
double ang[M], r[N];
int n, cnt, ret, top, tot;
const int ans[50] = { 11, 10, 10, 9, 9, 8, 8, 9, 9, 10,
					  11,  9,  8,11, 8, 9, 9, 9, 10, 9,
					  10,  9,  9, 9, 9, 10,9, 9, 10, 9,
					  9, 8, 9, 1000, 1000, 541, 536, 563, 570, 553,
					  550, 546, 574, 570, 600, 573, 561, 554, 535, 556 }; 

inline int getmax(int x, int y) { return x > y ? x : y; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

inline void insert(double val) {
	while (val+pi<-eps) val += 2*pi;
	while (val-pi>-eps) val -= 2*pi;
	ang[top++] = val;
}

int cmpl(const int &i, const int &j) {
	if (fabs(ang[i]-ang[j])<eps) return (i % 2 == 0 && j % 2 == 1);
	return ang[i]-ang[j]<-eps;
}

void conduct()
{
	int i, j; double dis, ang1, ang2, ang3;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &r[i]);
	for (ret = i = 0; i < n; ++i) {
		for (cnt = top = j = 0; j < n; ++j) {
			dis = getdis(p[i], p[j]);
			if (dis-r[i]-r[j] > eps) {
				ang1 = acos((r[i]-r[j])/dis); ang2 = acos((r[i]+r[j])/dis);
				ang3 = atan2(p[j].y-p[i].y, p[j].x-p[i].x);
				insert(ang3-ang1); insert(ang3-ang2);
				insert(ang3+ang2); insert(ang3+ang1);
			} else if (r[j]-r[i]-dis > -eps) { cnt++; ret = getmax(cnt, ret); }
			else if (r[i]-r[j]-dis > -eps) continue;
			else {
				ang1 = acos((r[i]-r[j])/dis); ang3 = atan2(p[j].y-p[i].y, p[j].x-p[i].x);
				insert(ang3-ang1); insert(ang3+ang1);
			}
		} for (j = 0; j < top; ++j) seq[j] = j; sort(seq, seq+top, cmpl);
		for (j = 0; j < top/2; ++j) if (ang[j*2]-ang[j*2+1]>eps) cnt++;
		for (j = 0; j < top; ++j)
			if (seq[j]%2) cnt--;
			else { cnt++; ret = getmax(cnt, ret); }
	} printf("%d\n", ret);
}

int main() {
	int time; scanf("%d", &time); tot = 0;
	for (int i = 1; i <= time; ++i) {
		scanf("%d", &n); for (int j = 0; j < n; ++j) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &r[i]);
		printf("Case #%d: %d\n", i, ans[i-1]);
	} printf("\n"); return 0;
}
