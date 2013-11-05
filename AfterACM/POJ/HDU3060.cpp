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

const double eps=1e-6;
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
struct line { double a, b, c; };

#define N 1010
pnt p[N], q[N];
int n, m;

double submul(const vec &v1, const vec &v2) { return v1.x*v2.y-v2.x*v1.y; }
double nummul(const vec &v1, const vec &v2) { return v1.x*v2.x+v1.y*v2.y; }
inline double SQR(double x) { return x*x; }
vec uvec(const vec &v) { return v/sqrt(nummul(v, v)); }
vec DCLOCK(const vec &v) { return (vec){-v.y, v.x}; }
pnt cross(const line &l1, const line &l2) {
	pnt ret; ret.x=(l1.b*l2.c-l2.b*l1.c)/(l1.b*l2.a-l2.b*l1.a);
	ret.y=(l1.a*l2.c-l2.a*l1.c)/(l1.a*l2.b-l2.a*l1.b); return ret;
}

line getline(const pnt &p, const vec &v) {
	vec lp=DCLOCK(uvec(v));
	line ret;
	ret.a=lp.x; ret.b=lp.y;
	ret.c=nummul(p, lp); return ret;
}

int split_valid(const pnt &st, const pnt &mid, const pnt &ed) {
	return nummul(mid-st, mid-ed)<-eps;
}
void split_insert(int &n, pnt *p, const pnt &q) {
	int i;
	for (i=n; i>0; --i) 
		if (split_valid(p[0], q, p[i])) p[i+1]=p[i];
		else break;
	if (i==n) return;
	n++; i++; p[i]=q;	
}

double triangle_common_area(const pnt &q1, const pnt &q2, const pnt &p1, const pnt &p2, double tag) {
	line l1, l2, l3, l4;
	pnt tp1, tp2, seg[10];
	int i, m;
	double ret;
	l1=getline(p1, p1); l2=getline(p2, p2); l3=getline(p1, p2-p1); l4=getline(q1, q2-q1);
	m=1; seg[0]=q1; seg[1]=q2;
	if (fabs(submul(p1, q2-q1))>eps) split_insert(m, seg, cross(l1, l4));
	if (fabs(submul(p2, q2-q1))>eps) split_insert(m, seg, cross(l2, l4));
	if (fabs(submul(p2-p1, q2-q1))>eps) split_insert(m, seg, cross(l3, l4));
	for (ret=0.0, i=0; i<m; ++i) {
		if (submul(p1, seg[i])<-eps || submul(p2, seg[i])>eps) continue;
		if (submul(p1, seg[i+1])<-eps || submul(p2, seg[i+1])>eps) { ++i; continue; }
		if (submul(p2-p1, seg[i]-p1)<-eps) tp1=cross(getline(seg[i], seg[i]), l3); else tp1=seg[i];
		if (submul(p2-p1, seg[i+1]-p1)<-eps) tp2=cross(getline(seg[i+1], seg[i+1]), l3); else tp2=seg[i+1];
		ret+=submul(tp1, tp2);
	}
	return ret*tag/2.0;
}

void conduct() {
	int i, j;
	double ans, tmp, a1, a2;
	for (i=0; i<n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (i=0; i<m; ++i) scanf("%lf%lf", &q[i].x, &q[i].y);
	p[n]=p[0]; q[m]=q[0];
	for (ans=0.0, i=0; i<n; ++i)
		if ((tmp=submul(p[i], p[i+1]))>eps) 
			for (j=0; j<m; ++j) ans+=triangle_common_area(q[j], q[j+1], p[i], p[i+1], 1.0);
		else if (tmp<-eps) 
			for (j=0; j<m; ++j) ans+=triangle_common_area(q[j], q[j+1], p[i+1], p[i], -1.0);
	for (a1=0.0, i=0; i<n; ++i) a1+=submul(p[i], p[i+1])/2.0;
	for (a2=0.0, i=0; i<m; ++i) a2+=submul(q[i], q[i+1])/2.0;
	printf("%.2f\n", fabs(a1)+fabs(a2)-fabs(ans));
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF) conduct();
}
