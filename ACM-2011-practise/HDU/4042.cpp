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

const double eps = 1e-9;
struct pnt {
	double x, y, z;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x; ret.y = y + p.y;
		ret.z = z + p.z; return ret;
	}
	pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x; ret.y = y - p.y;
		ret.z = z - p.z; return ret;
	}
	pnt operator*(const double &c) const {
		pnt ret; ret.x = x * c; ret.y = y * c;
		ret.z = z * c; return ret;
	}
	pnt operator/(const double &c) const {
		pnt ret; ret.x = x / c; ret.y = y / c;
		ret.z = z / c; return ret;
	}
	bool operator<(const pnt &p) const {
		if (fabs(z-p.z)<eps && fabs(y-p.y)<eps) return x-p.x<-eps;
		if (fabs(z-p.z)<eps) return y-p.y<-eps; return z-p.z<-eps;
	}
};
struct eqt2 { double a, b, c; };
typedef pnt vec;
#define getvec(x, y) ((y)-(x))
#define N 1010
vec ver1, ver2, ori;
pnt p[N], q[N], org;
int c1, c2;
double d1, d2, s1[N], s2[N];
int n, m;

vec submul(const vec &v1, const vec &v2) {
	vec ret; ret.x = v1.y*v2.z - v2.y*v1.z; ret.y = v1.z*v2.x - v2.z*v1.x;
	ret.z = v1.x*v2.y - v2.x*v1.y; return ret;
}
double nummul(const vec &v1, const vec &v2) { return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z; }
double len(const vec &v) { return sqrt(nummul(v, v)); }
vec uvec(const vec &v) { return v / len(v); }

int cmp2(const int &x, const int &y) {
	if (fabs(s1[x]-s2[y])<eps && (x%2) == (y%2)) return 0;
	if (s1[x]-s2[y] > eps) return -1; if (s1[x]-s2[y] < -eps) return 1;
	if ((x%2) > (y%2)) return 1; return -1;
}

pair<double, double> calc(const eqt2 &l1, const eqt2 &l2) {
	pair<double, double> ret; ret.first = (l1.b*l2.c - l2.b*l1.c) / (l1.b*l2.a - l2.b*l1.a);
	ret.second = (l1.a*l2.c - l2.a*l1.c) / (l1.a*l2.b - l2.a*l1.b); return ret;
}

bool checkcrs(pnt p1, pnt p2, pnt p3, pnt p4) {
	pnt tmp;
	if (p2 < p1) { tmp = p1; p1 = p2; p2 = tmp; } if (p4 < p3) { tmp = p3; p3 = p4; p4 = tmp; }
	if (p2 < p3 || p4 < p1) return false;
	if (nummul(submul(getvec(p1, p2), getvec(p1, p3)), submul(getvec(p1, p2), getvec(p1, p4))) > eps) return false;
	if (nummul(submul(getvec(p3, p4), getvec(p3, p1)), submul(getvec(p3, p4), getvec(p3, p2))) > eps) return false;
	return true;
}

void conduct()
{
	int i, j, k, l, val; vec tmp1, tmp2;
//	printf("n:%d m:%d\n", n, m);
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z); p[n] = p[0]; p[n+1] = p[1];
	for (i = 0; i < m; ++i) scanf("%lf%lf%lf", &q[i].x, &q[i].y, &q[i].z); q[m] = q[0]; q[m+1] = q[1];
	ver1 = submul(getvec(p[0], p[1]), getvec(p[0], p[2])); if (len(ver1)<eps) while(1); ver1 = uvec(ver1);
	ver2 = submul(getvec(q[0], q[1]), getvec(q[0], q[2])); if (len(ver2)<eps) while(1); ver2 = uvec(ver2);
	ori = submul(ver1, ver2); ori = uvec(ori); d1 = nummul(ver1, p[0]); d2 = nummul(ver2, q[0]);
	if (len(ori) < eps) {
		if (fabs(d1-d2) > eps) { printf("NO\n"); return; }
		for (i = 0; i < n; ++i) for (j = 0; j < m; ++j) 
			if (checkcrs(p[i], p[i+1], q[j], q[j+1])) { printf("YES\n"); return; }
	} else {
		tmp1 = submul(ori, ver1); org = p[0] + tmp1 * (d2 - nummul(ver2, p[0])) / nummul(ver2, tmp1);
		for (i = c1 = 0; i < n; ++i) {
			if (nummul(submul(getvec(org, p[i]), ori), submul(getvec(org, p[i+1]), ori)) > eps) continue;
			tmp1 = getvec(p[i], p[i+1]); if (len(tmp2 = submul(ori, tmp1)) < eps) continue;
			if (len(submul(getvec(org, p[i+1]), ori))<eps && nummul(submul(getvec(org, p[i]), ori), submul(getvec(org, p[i+2]), ori)) < -eps) continue;
			tmp2 = submul(tmp1, tmp2); s1[++c1] = (nummul(tmp2, p[i]) - nummul(tmp2, org)) / nummul(tmp2, ori);
//			s1[++c1] = calc((eqt2){ori.x, -tmp1.x, p[i].x-org.x}, (eqt2){ori.y, -tmp1.y, p[i].y-org.y}).first;
//			printf("st:%d ed:%d val:%.2f\n", i, i+1, s1[c1]);
		} for (i = c2 = 0; i < m; ++i) {
			if (nummul(submul(getvec(org, q[i]), ori), submul(getvec(org, q[i+1]), ori)) > eps) continue;
			tmp1 = getvec(q[i], q[i+1]); if (len(tmp2 = submul(ori, tmp1)) < eps) continue;
			if (len(submul(getvec(org, q[i+1]), ori))<eps && nummul(submul(getvec(org, q[i]), ori), submul(getvec(org, q[i+2]), ori)) < -eps) continue;
			tmp2 = submul(tmp1, tmp2); s2[++c2] = (nummul(tmp2, q[i]) - nummul(tmp2, org)) / nummul(tmp2, ori);
//			s2[++c2] = calc((eqt2){ori.x, -tmp1.x, q[i].x-org.x}, (eqt2){ori.y, -tmp1.y, q[i].y-org.y}).first;
//			printf("st:%d ed:%d val:%.2f\n", i, i+1, s2[c2]);
		} sort(s1+1, s1+c1+1); sort(s2+1, s2+c2+1);
//		printf("org:%.2f,%.2f,%.2f ori:%.2f,%.2f,%.2f\n", org.x, org.y, org.z, ori.x, ori.y, org.z);
//		printf("s1:"); for (i = 1; i <= c1; ++i) printf("%.2f ", s1[i]); printf("\n");
//		printf("s2:"); for (i = 1; i <= c2; ++i) printf("%.2f ", s2[i]); printf("\n");
		for (i = j = 1, k = l = 0; i <= c1 && j <= c2; ) {
			val = cmp2(i, j);
			if (val > 0) { k = 1-k; ++i; } else if (val < 0) { l = 1-l; ++j; }
			else { k = 1-k; l = 1-l; ++i; ++j; }
			if (k && l) { printf("YES\n"); return; }
		}
	} printf("NO\n");
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF && (n || m)) conduct();
	return 0;
}
