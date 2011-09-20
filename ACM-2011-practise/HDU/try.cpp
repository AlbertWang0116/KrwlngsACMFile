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
const double eps = 1e-8, pi = acos(-1.0);
struct pnt {
	double x, y;
	bool operator<(const pnt &p) const {
		if (fabs(x-p.x)<eps) return y-p.y<-eps;
		return x-p.x<-eps;
	}
};
struct line { double a, b, c; };
typedef pnt vec;
#define square(x) (x)*(x)
#define N 100010

struct evpinfo { int s, c; };
struct scmp { 
	static pnt pre[N], p[N], q[N]; static line l[N];
    bool operator()(const int &i, const int &j) {
        double y1, y2, ang1, ang2; pnt pos;
        ang1 = atan2(q[i].y - p[i].y, q[i].x - p[i].x); ang2 = atan2(q[j].y - p[j].y, q[j].x - p[j].x);
        if (pre[i] < pre[j]) pos = pre[j]; else pos = pre[i];
        if (fabs(ang1-pi/2)<eps) y1 = pos.y; else y1 = p[i].y + (q[i].y-p[i].y)/(q[i].x-p[i].x) * (pos.x-p[i].x);
        if (fabs(ang2-pi/2)<eps) y2 = pos.y; else y2 = p[j].y + (q[j].y-p[j].y)/(q[j].x-p[j].x) * (pos.x-p[j].x);
        if (fabs(y1-y2)<eps && fabs(ang1-ang2)<eps) return i < j; if (fabs(y1-y2)<eps) return ang1-ang2<-eps; return y1-y2<-eps;
    }
};
pnt scmp::pre[N] = {0, 0}, scmp::p[N] = {0, 0}, scmp::q[N] = {0, 0};
line scmp::l[N] = {0, 0, 0};
const evpinfo dft = {0, 0};
map<pnt, evpinfo> evt;
map<int, int, scmp> seg;
int hd[N], tl[N], snext[N];
int ans;

bool equal(const pnt &p1, const pnt &p2) { return (fabs(p1.x-p2.x)<eps && fabs(p1.y-p2.y)<eps); }

double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b); return ret;
}

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}
vec uvec(const vec &v) {
	double len = sqrt(square(v.x) + square(v.y));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; return ret;
}

line getline(const pnt &p1, const pnt &p2) {
	vec v = getvec(p1, p2); /* v = uvec(v); */
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}

int cmpl(pnt *p, pnt *q, int i, int j) {
    double val = submul(getvec(p[i], q[i]), getvec(p[j], q[j]));
	if (fabs(val)<eps) if (i > j) return 1; else return -1;
    if (val > eps) return -1; if (val < -eps) return 1; 
}

void evtinsert(const pnt &p, const int id) {
	map<pnt, evpinfo>::iterator pos;
	pos = evt.find(p); if (pos == evt.end()) pos = evt.insert(pair<pnt, evpinfo>(p, dft)).first;
	if (!pos->second.c) pos->second.c = id;
}

bool checkcrs(pnt* p, pnt* q, line* l, int i, int j, pnt &crs) {
	if (q[i] < p[j] || q[j] < p[i]) return false;
	if (submul(getvec(p[i], q[i]), getvec(p[i], p[j])) * submul(getvec(p[i], q[i]), getvec(p[i], q[j])) > eps) return false;
	if (submul(getvec(p[j], q[j]), getvec(p[j], p[i])) * submul(getvec(p[j], q[j]), getvec(p[j], q[i])) > eps) return false;
	if (fabs(submul(getvec(p[i], q[i]), getvec(p[j], q[j]))) < eps) if (q[i] < q[j]) crs = q[i]; else crs = q[j];
	else crs = getcrs(l[i], l[j]); return true;
}

void line_intersection(int n, pnt* p, pnt* q)
{
    int i, lst, mst, lb, rb;
    pnt np, evp;
    evpinfo info;
    map<pnt, evpinfo>::iterator pos, ipos;
    map<int, int, scmp>::iterator cur, lft, rit;
	bool empty;
    evt.clear(); seg.clear();
    for (i = 1; i <= n; ++i) if (q[i] < p[i]) { evp = p[i]; p[i] = q[i]; q[i] = evp; }
	for (i = 1; i <= n; ++i) { scmp::p[i] = p[i]; scmp::q[i] = q[i]; scmp::l[i] = getline(p[i], q[i]); }
    for (i = 1; i <= n; ++i) {
        pos = evt.find(p[i]); if (pos == evt.end()) pos = evt.insert(pair<pnt, evpinfo>(p[i], dft)).first;
        snext[i] = pos->second.s; pos->second.s = i; if (!equal(p[i], q[i])) evtinsert(q[i], i);
    }
    while (evt.size()) {
        pos = evt.begin(); info = pos->second; evp = pos->first; hd[0] = 0; tl[0] = 0;
        if (info.c) {
            cur = seg.find(info.c); lft = rit = cur;
            while (lft != seg.begin() && fabs(oridis(scmp::l[(--lft)->first], evp))<eps)  
				if (!equal(q[lft->first], evp)) hd[++hd[0]] = lft->first; else tl[++tl[0]] = lft->first;
			while (rit != seg.end() && fabs(oridis(scmp::l[rit->first], evp))<eps) 
				if (!equal(q[rit->first], evp)) hd[++hd[0]] = (rit++)->first; else tl[++tl[0]] = (rit++)->first;
			if (fabs(oridis(scmp::l[lft->first], evp))>eps) { lb = lft->first; lft++; } else lb = 0;
            if (rit != seg.end()) rb = rit->first; else rb = 0;
        }
		//handle the intersection.
		for (mst = 0, i = info.s; i; i = snext[i]) mst++; ans += mst + tl[0] + hd[0] - 1;
		//handle ended.
        if (info.c) for (; lft != rit; ) { cur = lft; lft++; seg.erase(cur); }
		for (i = info.s; i; i = snext[i]) hd[++hd[0]] = i;
        if (hd[0]) {
            for (empty = true, i = 1; i <= hd[0]; ++i) if (!equal(p[hd[i]], q[hd[i]])) {
				if (empty) { empty = false; mst = hd[i]; lst = hd[i]; }
                if (cmpl(p, q, mst, hd[i]) < 0) mst = hd[i]; if (cmpl(p, q, lst, hd[i]) > 0) lst = hd[i];
                scmp::pre[hd[i]] = evp; seg.insert(pair<int, int>(hd[i], 0));
            } if (!empty) { 
			if ((lft = seg.find(lst)) != seg.begin()) { cur = lft--; if (checkcrs(p, q, scmp::l, cur->first, lft->first, np) && evp < np) evtinsert(np, lst); }
            cur = rit = seg.find(mst); rit++; if (rit != seg.end()) if (checkcrs(p, q, scmp::l, cur->first, rit->first, np) && evp < np) evtinsert(np, mst);
			}
        } if ((!hd[0] || empty) && info.c && lb && rb) {
            lft = seg.find(lb); rit = seg.find(rb);
            if (checkcrs(p, q, scmp::l, lft->first, rit->first, np) && evp < np) evtinsert(np, lb);
        } evt.erase(pos);
    }
}

pnt p[N], q[N];
int n;

void input()
{
	for (int i = 1; i <= n; ++i) scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
}

void conduct()
{
	ans = 0;
	line_intersection(n, p, q);
	printf("%d\n", ans);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) { input(); conduct(); }
	return 0;
}
