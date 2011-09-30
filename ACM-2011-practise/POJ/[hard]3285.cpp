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

const double eps = 1e-6, EPS = 1e-3, inf = 1e100;
struct pnt { double x, y; };
#define square(x) (x)*(x)
#define NUM 3
#define BD 3
pnt p[3];
double r[3];

bool build(int &id) {
	scanf("%lf%lf%lf", &p[id].x, &p[id].y, &r[id]);
	if (fabs(p[id].x)<eps && fabs(p[id].y)<eps && fabs(r[id])<eps) return false;
	return true;
}

bool input()
{
	bool tag; int i;
	for (tag = false, i = 0; i < 3; ++i) tag |= build(i);
	return tag;
}

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

double valuate(const pnt &pp) {
	double avg, ret, dis[3]; int i;
//	for (avg = 0, i = 0; i < 3; ++i) {dis[i] = r[i]/getdis(pp, p[i]); avg += dis[i]; }avg /= 3;
	for (avg = 0, i = 0; i < 3; ++i) {dis[i] = getdis(pp, p[i])/r[i]; avg += dis[i]; }avg /= 3;
	for (ret = 0, i = 0; i < 3; ++i) ret += square(dis[i] - avg); return ret;
}

bool cmp(const pnt &p1, const pnt &p2) { return getdis(p1, p[0]) < getdis(p2, p[0]); }

void conduct()
{
	int i, j, k, l;
	double ans, val, vt, vtt, stx, sty, stp, ang;
	double lft, dn, up ,rit;
	pnt pa, pv, pt, ptt;
	ans = inf; pa.x = inf; pa.y = inf;
	up = rit = -inf; lft = dn = inf;
	for (i = 0; i < 3; ++i) {
		if (p[i].x > rit) rit = p[i].x; if (p[i].x < lft) lft = p[i].x;
		if (p[i].y > up) up = p[i].y; if (p[i].y < dn) dn = p[i].y;
	} stx = rit - lft; sty = up - dn;
	for (i = 0; i <= NUM; ++i) for (j = 0; j <= NUM; ++j) {
		pv.x = lft+stx/NUM*i; pv.y = dn+sty/NUM*j; val = valuate(pv);
		for (stp = (stx+sty)/NUM/BD; stp > eps; stp *= 0.96) {
			for (pt = pv, vt = val, k = -BD; k <= BD; ++k) for (l = -BD; l <= BD; ++l) {
//				ang = rand(); ptt.x = pv.x+cos(ang)*stp; ptt.y = pv.y+sin(ang)*stp; vtt = valuate(ptt);
				ptt.x = pv.x+stp*k; ptt.y = pv.y+stp*l; vtt = valuate(ptt);
				if (ptt.x < lft || ptt.x > rit || ptt.y < dn || ptt.y > up) continue;
				if (vtt < vt) { vt = vtt; pt = ptt; }
			} pv = pt; val = vt;
		} if (val < ans || (fabs(val)<EPS && cmp(pv, pa))) { ans = val; pa = pv; }
	} if (fabs(ans)<EPS) printf("%.2lf %.2lf\n", pa.x+eps, pa.y+eps); else printf("No solution\n");
}

int main()
{
	while (input()) conduct();
	return 0;
}
