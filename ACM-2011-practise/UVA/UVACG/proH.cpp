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

const double eps = 1e-8, pi = acos(-1.0), inf = 1e100;
struct pnt { double x, y; };
typedef pnt vec;
#define N 1000010
int seq[N], tmp[N], hp[N];
pnt p[N];
double ang[N];
int n;

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

double getmin(double x, double y) { return x < y ? x : y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }

int cmp(const int &x, const int &y) {
	if (fabs(p[x].y-p[y].y)<eps) return p[x].x-p[y].x<-eps;
	return p[x].y-p[y].y<-eps;
}

double mkang(int id, double st) {
	double ta, ang;
	ta = st; ang = atan2(p[seq[id+1]].y-p[seq[id]].y, p[seq[id+1]].x-p[seq[id]].x); 
	while (ang-ta<-eps) ang += 2*pi; ang -= ta; return ang;
}

int getele() {
	int ret, ele, i, j;
	ret = hp[1]; ele = hp[hp[0]--]; if (!hp[0]) return ret;
	for (i = 1, j = (i << 1); j <= hp[0]; i = j, j = (i << 1)) {
		if (j < hp[0] && cmp(hp[j+1], hp[j])) j++;
		if (cmp(hp[j], ele)) hp[i] = hp[j]; else break;
	} hp[i] = ele; return ret;
}

void update(int idx)
{
	int i, j, ele;
	for (ele = hp[idx], i = idx, j = (i >> 1); j > 0; i = j, j = (i >> 1))
		if (cmp(ele, hp[j])) hp[i] = hp[j]; else break;
	hp[i] = ele;
}

void conduct()
{
	int i, top, bot, id1, id2, id3, id4;
	double wi, hi, area, len, ang1, ang2, ang3, ang4, delta, tot;
	vec v1, v2;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
//	for (hp[0] = i = 0; i < n; ++i) { hp[++hp[0]] = i; update(hp[0]); }
//	for (i = 0; i < n; ++i) seq[i] = getele();
	top = bot = 0; tmp[0] = seq[0];
	for (i = 1; i < n; ++i) {
		while (top > bot && submul(getvec(p[tmp[top-1]], p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < eps) --top;
		tmp[++top] = seq[i];
	} bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && submul(getvec(p[tmp[top-1]], p[tmp[top]]), getvec(p[tmp[top]], p[seq[i]])) < eps) --top;
		tmp[++top] = seq[i];
	} n = top; for (i = 0; i < n; ++i) seq[i] = tmp[i]; seq[n] = seq[0]; seq[n+1] = seq[1];
//	printf("convex----->\n"); for (i = 0; i < n; ++i) printf("%lf,%lf\n", p[seq[i]].x, p[seq[i]].y);
	for (i = 1; i <= n; ++i) {
		ang1 = atan2(p[seq[i]].y-p[seq[i-1]].y, p[seq[i]].x-p[seq[i-1]].x);
		ang2 = atan2(p[seq[i+1]].y-p[seq[i]].y, p[seq[i+1]].x-p[seq[i]].x);
		while (ang2-ang1 < -eps) ang2 += 2*pi; ang[i] = ang2 - ang1;
	} ang[0] = ang[n];
	for (id1 = id2 = id3 = id4 = 0, i = 1; i < n; ++i) {
		if (p[seq[id1]].y-p[seq[i]].y>eps || (fabs(p[seq[id1]].y-p[seq[i]].y)<eps && p[seq[id1]].x-p[seq[i]].x>eps)) id1 = i;
		if (p[seq[id2]].y-p[seq[i]].y<-eps || (fabs(p[seq[id2]].y-p[seq[i]].y)<eps && p[seq[id2]].x-p[seq[i]].x<-eps)) id2 = i;
		if (p[seq[id3]].x-p[seq[i]].x>eps || (fabs(p[seq[id3]].x-p[seq[i]].x)<eps && p[seq[id3]].y-p[seq[i]].y<-eps)) id3 = i;
		if (p[seq[id4]].x-p[seq[i]].x<-eps || (fabs(p[seq[id4]].x-p[seq[i]].x)<eps && p[seq[id4]].y-p[seq[i]].y>eps)) id4 = i;
	} ang1 = mkang(id1, 0); ang2 = mkang(id2, pi); ang3 = mkang(id3, -pi/2); ang4 = mkang(id4, pi/2);
//	printf("preoperation----->\n");
//	printf("ang1:%.3f,ang2:%.3f,ang3:%.3f,ang4:%.3f,id1:%d,id2:%d,id3:%d,id4:%d\n", ang1, ang2, ang3, ang4, id1, id2, id3, id4);
//	printf("ang----->\n"); for (i = 0; i < n; ++i) printf("ang[%d]=%.3f\n", i, ang[i]);
	for (len = area = inf, tot = 0; tot - pi < eps; ) {
		delta = getmin(ang1, getmin(ang2, getmin(ang3, ang4)));
		tot += delta; ang1 -= delta; ang2 -= delta; ang3 -= delta; ang4 -= delta;
		if (fabs(ang1)<eps) { id1 = (id1+1)%n; ang1 = ang[id1]; }
		if (fabs(ang2)<eps) { id2 = (id2+1)%n; ang2 = ang[id2]; }
		if (fabs(ang3)<eps) { id3 = (id3+1)%n; ang3 = ang[id3]; }
		if (fabs(ang4)<eps) { id4 = (id4+1)%n; ang4 = ang[id4]; }
		v1 = (vec){ cos(tot), sin(tot) }; v2 = getvec(p[seq[id3]], p[seq[id4]]); wi = fabs(nummul(v1, v2));
		v1 = (vec){ cos(tot+pi/2), sin(tot+pi/2) }; v2 = getvec(p[seq[id1]], p[seq[id2]]); hi = fabs(nummul(v1, v2));
//		printf("tot:%.3f ---> id1:%d,id2:%d,id3:%d,id4:%d,wi:%.3f,hi:%.3f\n", tot, id1, id2, id3, id4, wi, hi);
		len = getmin(len, (wi+hi)*2); area = getmin(area, wi*hi);
	} printf("%.2f %.2f\n", area, len);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
