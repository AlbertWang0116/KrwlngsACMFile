#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

const double eps=1e-6;
const double pi=acos(-1.0);
struct pnt {
	double x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x=x+p.x;
		ret.y=y+p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x=x-p.x;
		ret.y=y-p.y; return ret;
	} pnt operator*(double c) const {
		pnt ret; ret.x=x*c;
		ret.y=y*c; return ret;
	} pnt operator/(double c) const {
		pnt ret; ret.x=x/c;
		ret.y=y/c; return ret;
	}
};
typedef pnt vec;

#define N 10
pnt p[N];
pnt cen;
double rad;
int n=3;

inline double submul(const vec &v1, const vec &v2) { return v1.x*v2.y-v2.x*v1.y; }
inline double nummul(const vec &v1, const vec &v2) { return v1.x*v2.x+v1.y*v2.y; }
inline vec uvec(const vec &v) { return v/sqrt(nummul(v, v)); }
inline vec DCLOCK(const vec &v) { return (vec){ -v.y, v.x }; }
inline int split_valid(const pnt &st, const pnt &mid, const pnt &ed) {
	return nummul(mid-st, mid-ed)<-eps;
}
inline double angle_interval(const vec &v1, const vec &v2) {
	double ret=atan2(v2.y, v2.x)-atan2(v1.y, v1.x);
	if (ret-pi>eps) ret-=2*pi; if (ret+pi<eps) ret+=2*pi;
	return ret;
}
inline double SQR(double x) { return x*x; }
inline double getdis(const pnt &p1, const pnt &p2) { 
	return sqrt(SQR(p2.x-p1.x)+SQR(p2.y-p1.y));
}

int segxcircle(const pnt &p1, const pnt &p2, const pnt &cen, double rad, pnt *res) {
	int ret;
	vec fp, lp;
	double dis, rem;
	fp=uvec(p2-p1); lp=DCLOCK(fp); dis=submul(fp, cen-p1);
	ret=1; res[0]=p1;
	if (fabs(dis)-rad<eps) {
		rem=sqrt(SQR(rad)-SQR(dis));
		res[ret]=cen-lp*dis-fp*rem; if (split_valid(res[ret-1], res[ret], p2)) ret++;
		res[ret]=cen-lp*dis+fp*rem; if (split_valid(res[ret-1], res[ret], p2)) ret++;
	}
	res[ret]=p2; return ret;
}

double circle_clip_area(const pnt &p1, const pnt &p2, const pnt &cen, double rad) {
	if (getdis(p1, cen)-rad<eps && getdis(p2, cen)-rad<eps) return submul(p1-cen, p2-cen)/2.0;
	else return SQR(rad)*angle_interval(uvec(p1-cen), uvec(p2-cen))/2.0;
}

double polyxcircle(int n, pnt *p, const pnt &cen, double rad) {
	double ret;
	int i, j, m;
	pnt seg[10];
	p[n]=p[0];
	for (ret=i=0; i<n; ++i) {
		m=segxcircle(p[i], p[i+1], cen, rad, seg);
		for (j=0; j<m; ++j) ret+=circle_clip_area(seg[j], seg[j+1], cen, rad);
	}
	return ret;
}

void conduct() {
	int i; double ans;
	for (i=1; i<n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	scanf("%lf%lf%lf", &cen.x, &cen.y, &rad);
	ans=polyxcircle(n, p, cen, rad);
	printf("%.2f\n", fabs(ans));
}

int main() {
	while (scanf("%lf%lf", &p[0].x, &p[0].y)!=EOF) conduct();
	return 0;
}
