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
#define N 1010
pnt p[N], st;
double ti, g, ves, ang, rad;
int n;

double nummul(const pnt &p1, const pnt &p2) { return p1.x*p2.x+p1.y*p2.y; }
double submul(const pnt &p1, const pnt &p2) { return p1.x*p2.y-p2.x*p1.y; }
double SQR(double x) { return x*x; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(SQR(p2.x-p1.x)+SQR(p2.y-p1.y)); }
vec uvec(const vec &v) { return v/sqrt(nummul(v, v)); }
vec DCLOCK(const vec &v) { return (vec){-v.y, v.x}; }
int split_valid(const pnt &st, const pnt &mid, const pnt &ed) {
	return nummul(mid-st, mid-ed)<-eps;
}
double angle_interval(const vec &v1, const vec &v2) {
	double ret=atan2(v2.y, v2.x)-atan2(v1.y, v1.x);
	if (ret-pi>eps) ret-=2*pi; else if (ret+pi<eps) ret+=2*pi;
	return ret;
}

int segxcircle(const pnt &p1, const pnt &p2, const pnt &cen, double rad, pnt *res) {
	int ret;
	double dis, rem;
	vec lp, fp;
	fp=uvec(p2-p1); lp=DCLOCK(fp); dis=submul(fp, cen-p1);
	ret=1; res[0]=p1;
	if (dis-rad<eps) {
		rem=sqrt(SQR(rad)-SQR(dis));
		res[ret]=cen-lp*dis-fp*rem; if (split_valid(res[ret-1], res[ret], p2)) ret++;
		res[ret]=cen-lp*dis+fp*rem; if (split_valid(res[ret-1], res[ret], p2)) ret++;
	}
	res[ret]=p2; return ret;
}

double circle_clip_area(const pnt &p1, const pnt &p2, const pnt &cen, double rad) {
	if (getdis(p1, cen)-rad<eps && getdis(p2, cen)-rad<eps) return submul(p1-cen, p2-cen)/2.0;
	else return SQR(rad)*angle_interval(p1-cen, p2-cen)/2.0;
}

double polyxcircle(int n, pnt *p, const pnt &cen, double rad) {
	int m, i, j;
	double ret;
	pnt seg[10];
	p[n]=p[0];
	for (ret=0.0, i=0; i<n; ++i) {
		m=segxcircle(p[i], p[i+1], cen, rad, seg);
		for (j=0; j<m; ++j) ret+=circle_clip_area(seg[j], seg[j+1], cen, rad);
	}
	return ret;
}

int conduct() {
	double v1, v2, ans;
	int i;
	vec cen, off;
	scanf("%lf%lf%lf%lf%lf%lf%lf", &st.x, &st.y, &ves, &ang, &ti, &g, &rad);
	if (fabs(st.x)<eps && fabs(st.y)<eps && fabs(ves)<eps && fabs(ang)<eps && fabs(ti)<eps && fabs(g)<eps && fabs(rad)<eps) return 0;
	ang=ang/180.0*pi;
	v1=ves*cos(ang); v2=ves*sin(ang);
	off.x=v1*ti; off.y=(2.0*v2-g*ti)*ti/2.0;
	cen=st+off;
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	ans=polyxcircle(n, p, cen, rad);
	printf("%.2f\n", fabs(ans));
	return 1;
}

int main() {
	while (conduct());
	return 0;
}
