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
#define N 100010
const double eps = 1e-8, pi = acos(-1.0);

struct pnt {
	double x, y;
	bool operator<(const pnt &p) const {
		if (fabs(p.x-x)<eps) return y-p.y < -eps;
		return x-p.x < -eps;
	}
};
struct line { double a, b, c; };
typedef pnt vec;

pnt p[N], q[N], pre[N];
line l[N];
int cl[N], snext[N];
bool cov[N], fst;
int n;

vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
//	if (fabs(len)<eps) while(1) printf("\n");
	vec ret; ret.x = v.x / len; ret.y = v.y / len; return ret;
}

double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }

bool equal(const pnt &p1, const pnt &p2) { return (fabs(p1.x-p2.x)<eps && fabs(p1.y-p2.y)<eps); }

int cmpl(int i, int j) {
	double val = submul(getvec(p[i], q[i]), getvec(p[j], q[j]));
	if (val > eps) return -1; if (val < -eps) return 1; return 0; 
}

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b*l2.c - l2.b*l1.c) / (l1.b*l2.a - l2.b*l1.a);
	ret.y = (l1.a*l2.c - l2.a*l1.c) / (l1.a*l2.b - l2.a*l1.b); return ret;
}

line getline(const pnt &p1, const pnt &p2) {
	vec v = getvec(p1, p2); v = uvec(v);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}

bool checkcrs(int i, int j, pnt &crs) {
//	return false;
	if (q[i] < p[j] || q[j] < p[i]) return false;
	if (submul(getvec(p[i], q[i]), getvec(p[i], p[j])) * submul(getvec(p[i], q[i]), getvec(p[i], q[j])) > eps) return false;
	if (submul(getvec(p[j], q[j]), getvec(p[j], p[i])) * submul(getvec(p[j], q[j]), getvec(p[j], q[i])) > eps) return false;
	if (fabs(submul(getvec(p[i], q[i]), getvec(p[j], q[j]))) < eps) if (q[i] < q[j]) crs = q[i]; else crs = q[j];
	else crs = getcrs(l[i], l[j]); return true;
}

struct evpinfo { int s, c; };
struct seginfo { 
	int id;
	bool operator<(const seginfo &si) const {
		double y1, y2; pnt pos;
		double ang1 = atan2(q[id].y - p[id].y, q[id].x - p[id].x);
		double ang2 = atan2(q[si.id].y-p[si.id].y, q[si.id].x-p[si.id].x);
		if (pre[id] < pre[si.id]) pos = pre[si.id]; else pos = pre[id];
		if (fabs(ang1-pi/2)<eps) y1 = pos.y; else y1 = p[id].y + (q[id].y-p[id].y)/(q[id].x-p[id].x) * (pos.x-p[id].x);
		if (fabs(ang2-pi/2)<eps) y2 = pos.y; else y2 = p[si.id].y + (q[si.id].y-p[si.id].y)/(q[si.id].x-p[si.id].x) * (pos.x-p[si.id].x);
		if (fabs(y1-y2)<eps && fabs(ang1-ang2)<eps) return id < si.id;
		if (fabs(y1-y2)<eps) return ang1-ang2<-eps; return y1-y2<-eps;
	}
};
const evpinfo dft = {0, 0};
map<pnt, evpinfo> evt;
map<seginfo, int> seg;

void input()
{
	for (int i = 1; i <= n; ++i) scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
}


void conduct()
{
	int i, lst, mst, lb, rb;
	pnt np, ptmp, evp;
	evpinfo info; seginfo si;
	double tmp = 0;
	map<pnt, evpinfo>::iterator pos, ipos;
	map<seginfo, int>::iterator cur, lft, rit;
	evt.clear(); seg.clear(); memset(cov, 0, sizeof(cov));
	for (i = 1; i <= n; ++i) if (q[i] < p[i]) { ptmp = p[i]; p[i] = q[i]; q[i] = ptmp; }
	for (i = 1; i <= n; ++i) {
		l[i] = getline(p[i], q[i]);
		pos = evt.find(p[i]); if (pos == evt.end()) pos = evt.insert(pair<pnt, evpinfo>(p[i], dft)).first;
		snext[i] = pos->second.s; pos->second.s = i;
		pos = evt.find(q[i]); if (pos == evt.end()) pos = evt.insert(pair<pnt, evpinfo>(q[i], dft)).first;
		if (!pos->second.c) pos->second.c = i;
	}
	while (evt.size()) {
		pos = evt.begin(); info = pos->second; evp = pos->first;
//		info.c = 0; info.s = 0;
		if (info.c) {
			si.id = info.c; cur = seg.find(si); lft = rit = cur; cl[0] = 0; 
//			if (cur == seg.end()) while(1) printf("\n");
			while (lft != seg.begin()) { lft--; if (!equal(q[lft->first.id], evp)) if (fabs(oridis(l[lft->first.id], evp))<eps) cl[++cl[0]] = lft->first.id; else break; }
			while (rit != seg.end() && fabs(oridis(l[rit->first.id], evp))<eps) { if (!equal(q[rit->first.id], evp)) cl[++cl[0]] = rit->first.id; rit++; }
			if (fabs(oridis(l[lft->first.id], evp))>eps) lb = lft->first.id; else lb = 0;
			if (rit != seg.end()) rb = rit->first.id; else rb = 0;
		} else cl[0] = 0;
//		printf("---------intersection: [%.3f][%.3f] ---------\nline: ", evp.x, evp.y);
//		for (i = info.s; i; i = snext[i]) printf("s:%d ", i); 
//		if (info.c) {
//			cur = lft; if (fabs(oridis(l[lft->first.id], evp))>eps) cur++;
//			for (; cur != rit; cur++) printf("c:%d ", cur->first.id);
//		}
//		printf("\n");
//		printf("cl: "); for (i = 1; i <= cl[0]; ++i) printf("%d ", cl[i]); printf("\n");
		mst = 0; cur = lft;
		for (i = info.s; i; i = snext[i]) if (i < mst) cov[i] = true; else { cov[mst] = true; mst = i; } 
		if (info.c) {
			if (fabs(oridis(l[lft->first.id], evp))>eps) cur++;
			for (; cur != rit; cur++) if (cur->first.id < mst) cov[cur->first.id] = true; else { cov[mst] = true; mst = cur->first.id; }
		}
		if (info.c) {
			if (fabs(oridis(l[lft->first.id], evp))>eps) lft++;
			for (; lft != rit; ) { cur = lft; lft++; seg.erase(cur); }
		}
		if (info.s || cl[0]) {
			if (cl[0]) { mst = cl[1]; lst = cl[1]; } else { mst = info.s; lst = info.s; }
			for (i = 1; i <= cl[0]; ++i) {
				if (cmpl(mst, cl[i]) < 0) mst = cl[i]; if (cmpl(lst, cl[i]) > 0) lst = cl[i];
				si.id = cl[i]; pre[cl[i]] = evp; seg.insert(pair<seginfo, int>(si, 0));
			}
			for (i = info.s; i; i = snext[i]) {
				if (cmpl(mst, i) < 0) mst = i; if (cmpl(lst, i) > 0) lst = i;
				si.id = i; pre[i] = evp; seg.insert(pair<seginfo, int>(si, 0));
			}
//			printf("lst:%d mst%d\n", lst, mst);
			si.id = lst; lft = seg.find(si);
//			if (lft == seg.end()) while(1) printf("\n");
			if (lft != seg.begin()) {
				cur = lft; lft--; 
//				printf("cur:%d lft:%d\n", cur->first.id, lft->first.id);
				if (checkcrs(cur->first.id, lft->first.id, np) && evp < np) {
					ipos = evt.find(np); if (ipos == evt.end()) ipos = evt.insert(pair<pnt, evpinfo>(np, dft)).first;
					if (!ipos->second.c) ipos->second.c = lst;
				}
			} si.id = mst; cur = rit = seg.find(si); cur++;
//			if (rit == seg.end()) while(1) printf("\n");
			if (cur != seg.end()) {
//				printf("cur:%d rit:%d\n", cur->first.id, rit->first.id);
				if (checkcrs(cur->first.id, rit->first.id, np) && evp < np) {
					ipos = evt.find(np); if (ipos == evt.end()) ipos = evt.insert(pair<pnt, evpinfo>(np, dft)).first;
					if (!ipos->second.c) ipos->second.c = mst;
				}
			}
		} else if (info.c && lb && rb) {
			si.id = lb;  lft = seg.find(si);
			si.id = rb;  rit = seg.find(si);
//			if (lft == seg.end() || rit == seg.end()) while(1) printf("\n");
//			printf("lft:%d rit:%d\n", lft->first.id, rit->first.id);
			if (checkcrs(lft->first.id, rit->first.id, np) && evp < np) {
				ipos = evt.find(np); if (ipos == evt.end()) ipos = evt.insert(pair<pnt, evpinfo>(np, dft)).first;
				if (!ipos->second.c) ipos->second.c = lb;
			}
		} evt.erase(pos);
//		printf("seg: "); for (cur = seg.begin(); cur != seg.end(); ++cur) printf("%d ", cur->first.id); printf("\n");
	} printf("Top sticks: "); fst = true;
	for (i = 1; i <= n; ++i) if (!cov[i]) if (fst) { printf("%d", i); fst = false; } else printf(", %d", i); printf(".\n");
//	if (seg.size()) 1 / tmp;
}

int main()
{
	while (scanf("%d", &n) != EOF && n) { input(); conduct(); }
	return 0;
}
