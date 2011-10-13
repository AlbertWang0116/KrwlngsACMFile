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
const double eps = 1e-12, pi = acos(-1.0), inf = 1e20;
struct pnt {
	double x, y;
	bool operator<(const pnt &p) const {
		if (fabs(y-p.y)<eps) return x-p.x<-eps;
		return y-p.y < -eps;
	}
};
typedef pnt vec;
struct line { double a, b, c; };
struct info { double ang1, ang2, val; };
#define N 10010
pnt p[N], q[N];
int n;
map<pnt, info> que;

double getmin(double x, double y) { return x < y ? x : y; }
double getmax(double x, double y) { return x > y ? x : y; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b*l2.c-l2.b*l1.c) / (l1.b*l2.a-l2.b*l1.a);
	ret.y = (l1.a*l2.c-l2.a*l1.c) / (l1.a*l2.b-l2.a*l1.b); return ret;
}

line getline(const pnt &p, double ang) {
	vec v = { cos(ang), sin(ang) };
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p.x + ret.b * p.y; return ret;
}

void conduct()
{
	pnt pos, des; info pv, qv; line l1, l2; int i;
	double ang1, ang2, x1, x2, y1, ret;
	map<pnt, info>::iterator itr, del;
	scanf("%lf%lf", &pos.x, &pos.y);
	for (i = 0; i < n; ++i) {
		scanf("%lf%lf%lf", &y1, &x1, &x2);
		p[i] = (pnt){ x1, y1 }; q[i] = (pnt){ x2, y1 };
	}
	que.clear(); pv = (info){ -pi, 0, 0 };
	que.insert(pair<pnt, info>(pos, pv));
	for (i = 0; i < n-1; ++i) {
		pv = (info){-pi, 0, inf }; qv = (info){ -pi, 0, inf };
		for (itr = que.begin(); itr != que.end(); ) {
			pos = itr->first;
			ang1 = atan2(p[i].y-pos.y, p[i].x-pos.x);
			ang2 = atan2(q[i].y-pos.y, q[i].x-pos.x);
			itr->second.ang1 = getmax(itr->second.ang1, ang1);
			itr->second.ang2 = getmin(itr->second.ang2, ang2);
			if (itr->second.ang1 - itr->second.ang2 > eps) del = itr;
			else {
				del = que.end();
				if (itr->second.ang1 - ang1 < eps) pv.val = getmin(pv.val, getdis(pos, p[i])+itr->second.val);
				if (itr->second.ang2 - ang2 > -eps) qv.val = getmin(qv.val, getdis(pos, q[i])+itr->second.val);
			} itr++; if (del != que.end()) que.erase(del);
		} que.insert(pair<pnt, info>(p[i], pv)); que.insert(pair<pnt, info>(q[i], qv));
	} ret = inf; 
	for (itr = que.begin(); itr != que.end(); ++itr) {
		pos = itr->first;
		ang1 = atan2(p[i].y-pos.y, p[i].x-pos.x); ang1 = getmax(itr->second.ang1, ang1);
		ang2 = atan2(q[i].y-pos.y, q[i].x-pos.x); ang2 = getmin(itr->second.ang2, ang2);
		if (ang1 - ang2 > eps) continue;
		if ((ang1+pi/2) * (ang2+pi/2) < eps) ret = getmin(ret, pos.y - p[i].y + itr->second.val);
		else {
			ret = getmin(ret, (pos.y-p[i].y)/cos(getmin(fabs(ang1+pi/2), fabs(ang2+pi/2)))+itr->second.val);
		}
	} printf("%.11f\n", ret);
}


int main()
{
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
