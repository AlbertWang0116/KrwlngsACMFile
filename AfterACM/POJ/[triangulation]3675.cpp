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
int nxt[N], pre[N], tag[N], vst[N], lft[N], rit[N];
pnt p[N], cen;
int n;
double rad;

double submul(const pnt &p1, const pnt &p2) { return p1.x*p2.y-p2.x*p1.y; }
double nummul(const pnt &p1, const pnt &p2) { return p1.x*p2.x+p1.y*p2.y; }
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
	vec lp, fp;
	int ret;
	double dis, rem;
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
	double ret;
	int i, j, m;
	pnt seg[10];
	p[n]=p[0];
	for (ret=0.0, i=0; i<n; ++i) {
		m=segxcircle(p[i], p[i+1], cen, rad, seg);
		for (j=0; j<m; ++j) ret+=circle_clip_area(seg[j], seg[j+1], cen, rad);
	}
	return ret;
}

int triangle_judge(int x) {
	vec v1, v2, v3;
	v1=p[x]-p[pre[x]]; v2=p[nxt[x]]-p[x]; v3=p[pre[x]]-p[nxt[x]];
	if (submul(v1, v2)<-eps) return 0;
	for (int i=nxt[nxt[x]]; i!=pre[x]; i=nxt[i])
		if (submul(v1, p[i]-p[pre[x]])>-eps && submul(v2, p[i]-p[x])>-eps && submul(v3, p[i]-p[nxt[x]])>-eps) return 0;
	return 1;	
}

void conduct() {
	int i, j;
	double ans;
	pnt tp, q[10];
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y); p[n]=p[0];
	for (ans=i=0; i<n; ++i) ans+=submul(p[i], p[i+1]);
	if (ans<-eps) for (i=0; i<n/2; ++i) { tp=p[i]; p[i]=p[n-1-i]; p[n-1-i]=tp; }
	for (i=0; i<n-1; ++i) { nxt[i]=i+1; pre[i+1]=i; }
	nxt[n-1]=0; pre[0]=n-1;
	for (i=0; i<n; ++i) if (triangle_judge(i)) tag[i]=1; else tag[i]=0;
	memset(vst, 0, sizeof(vst));
	for (i=0; i<n-2; ++i) {
		for (j=0; j<n; ++j) if (!vst[j] && tag[j]) break;
		vst[j]=1; lft[j]=pre[j]; rit[j]=nxt[j];
		pre[rit[j]]=lft[j]; nxt[lft[j]]=rit[j];
		if (triangle_judge(lft[j])) tag[lft[j]]=1; else tag[lft[j]]=0;
		if (triangle_judge(rit[j])) tag[rit[j]]=1; else tag[rit[j]]=0;
	}
	for (ans=0.0, i=0; i<n; ++i) if (vst[i]) {
		q[0]=p[lft[i]]; q[1]=p[i]; q[2]=p[rit[i]];
		ans+=polyxcircle(3, q, cen, rad);
	}
	printf("%.2f\n", ans);
}

int main() {
	cen.x=0.0; cen.y=0.0;
	while (scanf("%lf", &rad)!=EOF) conduct();
	return 0;
}
