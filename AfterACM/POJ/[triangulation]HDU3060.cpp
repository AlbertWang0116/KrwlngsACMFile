#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<climits>
#include<map>
#include<string>
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
int ltp[N], rtp[N], ltq[N], rtq[N], nxt[N], pre[N], vp[N], vq[N], tag[N];
pnt p[N], q[N];
int n, m;

double getmax(double x, double y) { return x>y?x:y; }
double getmin(double x, double y) { return x<y?x:y; }
double submul(const pnt &p1, const pnt &p2) { return p1.x*p2.y-p2.x*p1.y; }
double nummul(const pnt &p1, const pnt &p2) { return p1.x*p2.x+p1.y*p2.y; }
double SQR(double x) { return x*x; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(SQR(p2.x-p1.x)+SQR(p2.y-p1.y)); }
vec uvec(const vec &v) { return v/sqrt(nummul(v, v)); }
vec DCLOCK(const vec &v) { return (vec){-v.y, v.x }; }

line getline(const pnt &p, const vec &v) {
	vec lp=DCLOCK(uvec(v));
	line ret;
	ret.a=lp.x; ret.b=lp.y; ret.c=nummul(p, lp);
	return ret;
}

int is_cross(const line &l1, const line &l2) { return fabs(l1.a*l2.b-l2.a*l1.b)>eps; }
pnt cross(const line &l1, const line &l2) {
	pnt ret; ret.x=(l1.b*l2.c-l2.b*l1.c)/(l1.b*l2.a-l2.b*l1.a);
	ret.y=(l1.a*l2.c-l2.a*l1.c)/(l1.a*l2.b-l2.a*l1.b); return ret;
}

int split_valid(const pnt &st, const pnt &mid, const pnt &ed) {
	return nummul(mid-st, mid-ed)<-eps;
}
void split_insert(int &n, pnt *p, const pnt &mid) {
	int i;
	for (i=n; i>0; --i) 
		if (split_valid(p[0], mid, p[i])) p[i+1]=p[i];
		else break;
	if (i==n) return;
	n++; i++; p[i]=mid;
}

double poly_clip_poly_area(const pnt &q1, const pnt &q2, const pnt &p1, const pnt &p2, double tag) {
	int i, m, use[10];
	double ret, dis;
	line l[10], lq;
	pnt seg[10], lp;
	if (fabs(submul(q1, q2))<eps) return 0.0; // when q1=q2, the following will get error
	l[0]=getline(p1, p1); l[1]=getline(p2, p2); l[2]=getline(p1, p2-p1); lq=getline(q1, q2-q1);
	lp.x=l[2].a; lp.y=l[2].b; dis=l[2].c;
	m=1; seg[0]=q1; seg[1]=q2;
	for (i=0; i<3; ++i) if (is_cross(l[i], lq)) split_insert(m, seg, cross(l[i], lq));
	for (i=0; i<=m; ++i) if (submul(p1, seg[i]-p1)<-eps || submul(p2, seg[i]-p2)>eps) use[i]=0; else use[i]=1;
	for (i=0; i<=m; ++i) if (use[i] && submul(p2-p1, seg[i]-p1)<-eps) seg[i]=uvec(seg[i])*dis/nummul(lp, uvec(seg[i]));
	for (ret=0.0, i=0; i<m; ++i) if (use[i] && use[i+1]) ret+=submul(seg[i], seg[i+1]);
	return ret*tag/2.0;
}

double polyxpoly(int n, pnt *p, int m, pnt *q) {
	double ret, tmp;
	int i, j;
	p[n]=p[0]; q[m]=q[0];
	for (ret=0.0, i=0; i<n; ++i)
		if ((tmp=submul(p[i], p[i+1]))>eps)
			for (j=0; j<m; ++j) ret+=poly_clip_poly_area(q[j], q[j+1], p[i], p[i+1], 1.0);
		else if (tmp<-eps)
			for (j=0; j<m; ++j) ret+=poly_clip_poly_area(q[j], q[j+1], p[i+1], p[i], -1.0);
	return ret;
}

int triangle_judge(pnt *p, int x) {
	vec v1, v2, v3;
	v1=p[x]-p[pre[x]]; v2=p[nxt[x]]-p[x]; v3=p[pre[x]]-p[nxt[x]];
	if (submul(v1, v2)<-eps) return 0; if (submul(v1, v2)<eps) return 1;
	for (int i=nxt[nxt[x]]; i!=pre[x]; i=nxt[i])
		if (submul(v1, p[i]-p[pre[x]])>-eps && submul(v2, p[i]-p[x])>-eps && submul(v3, p[i]-p[nxt[x]])>-eps) return 0;
	return 1;
}

void triangulation(int n, pnt *p, int *lft, int *rit, int *vst) {
	int i, j;
	memset(vst, 0, n*sizeof(int));
	for (i=0; i<n-1; ++i) { nxt[i]=i+1; pre[i+1]=i; } 
	nxt[n-1]=0; pre[0]=n-1; nxt[n]=pre[n]=n;
	for (i=0; i<n; ++i) if (triangle_judge(p, i)) tag[i]=1; else tag[i]=0;
	for (i=0; i<n-2; ++i) {
		for (j=0; j<n; ++j) if (!vst[j] && tag[j]) break;
		vst[j]=1; lft[j]=pre[j]; rit[j]=nxt[j];
		nxt[lft[j]]=rit[j]; pre[rit[j]]=lft[j];
		if (triangle_judge(p, lft[j])) tag[lft[j]]=1; else tag[lft[j]]=0;
		if (triangle_judge(p, rit[j])) tag[rit[j]]=1; else tag[rit[j]]=0;
	}
}

int seg_cross(const pnt &p1, const pnt &p2, const pnt &q1, const pnt &q2) {
		return (submul(p2-p1, q1-p1)*submul(p2-p1, q2-p1)<-eps &&
						submul(q2-q1, p1-q1)*submul(q2-q1, p2-q1)<-eps);
}

void dfs() {
	dfs();
}

void simple_poly_judge(int n, pnt *p, int query) {
	int cnt, i, j;
	for (i=0; i<n; ++i) {
		for (j=cnt=0; j<n; ++j) if (seg_cross(p[i], p[i+1], p[j], p[j+1])) cnt++;
		if (cnt) 
			if (query==2) while(1) printf("aaaaaa.\n");
			else dfs();	
	}
}

void conduct() {
	int i, j;
	double ans, t1, t2;
	pnt tp, pp[10], qq[10];
	for (i=0; i<n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y); p[n]=p[0];
	for (i=0; i<m; ++i) scanf("%lf%lf", &q[i].x, &q[i].y); q[m]=q[0];
//	simple_poly_judge(n, p, 1);
//	simple_poly_judge(m, q, 2);
	for (ans=0.0, i=0; i<n; ++i) ans+=submul(p[i], p[i+1]);
	if (ans<-eps) { for (i=0; i<n/2; ++i) { tp=p[i]; p[i]=p[n-i-1]; p[n-i-1]=tp; } t1=-1.0; }
	else t1=1.0;
	for (ans=0.0, i=0; i<m; ++i) ans+=submul(q[i], q[i+1]);
	if (ans<-eps) { for (i=0; i<m/2; ++i) { tp=q[i]; q[i]=q[m-i-1]; q[m-i-1]=tp; } t2=-1.0; }
	else t2=1.0;
	p[n]=p[0]; q[m]=q[0];
	triangulation(n, p, ltp, rtp, vp); 
	triangulation(m, q, ltq, rtq, vq);
//	for (ans=0.0, i=0; i<n; ++i) if (vp[i])
//		for (j=0; j<m; ++j) if (vq[j]) {
//			pp[0]=p[ltp[i]]; pp[1]=p[i]; pp[2]=p[rtp[i]];
//			qq[0]=q[ltq[j]]; qq[1]=q[j]; qq[2]=q[rtq[j]];
//			ans+=polyxpoly(3, pp, 3, qq);
//		}
	ans=polyxpoly(n, p, m, q);
	ans=ans*t1*t2;
	for (t1=0.0, i=0; i<n; ++i) t1+=submul(p[i], p[i+1])/2.0;
	for (t2=0.0, i=0; i<m; ++i) t2+=submul(q[i], q[i+1])/2.0;
	printf("%.2f\n", t1+t2-ans);
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF) conduct();
	return 0;
}
