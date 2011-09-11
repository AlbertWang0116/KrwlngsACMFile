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

struct pnt {
	double x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	}
	pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	}
	pnt operator*(const double &c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	}
};
typedef pnt vec;
struct line { double a, b, c; };

#define square(x) (x)*(x)
#define N 110
const double eps = 1e-16, inf = 1e10;
pnt p[N], v[N];
int seq[N];
bool vst[N];
int n, ret;

int getmax(int x, int y) { return x > y ? x : y; }

void input()
{
	int i;
//	for (i = 0; i < n; ++i) scanf("%lf%lf%llf%llf", &p[i].x, &p[i].y, &v[i].x, &v[i].y);
	for (i = 0; i < n; ++i) cin >> p[i].x >> p[i].y >> v[i].x >> v[i].y;
}

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
	vec ret; ret.x = v.x/len; ret.y = v.y/len; return ret;
}

line getline(const pnt &p1, const pnt &p2) {
//	printf("p1:[%.3f][%.3f] p2:[%.3f][%.3f]\n", p1.x, p1.y, p2.x, p2.y);
	vec v = p2 - p1; v = uvec(v);
//	printf("v:%.3f %.3f\n", v.x, v.y);
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; 
//	printf("a:%.3f b:%.3f c:%.3f\n", ret.a, ret.b, ret.c);
	return ret;
}

double oridis(const line &l, const pnt &p) { 
//	printf("l:%.3f %.3f %.3f, p:%.3f %.3f\n", l.a, l.b, l.c, p.x, p.y);
	return l.a * p.x + l.b * p.y - l.c; 
}

int gettime(int i, int j, int k, double* ans) {
	double tmp1, tmp2, tmp3, tmp4, a, b, c;
	tmp1 = v[i].y-v[j].y; tmp2 = p[i].y-p[j].y; tmp3 = v[k].x; tmp4 = p[k].x;
	a = tmp1 * tmp3; b = (tmp1 * tmp4 + tmp2 * tmp3); c = tmp2 * tmp4;
	tmp1 = v[j].x-v[i].x; tmp2 = p[j].x-p[i].x; tmp3 = v[k].y; tmp4 = p[k].y;
	a += tmp1 * tmp3; b += (tmp1 * tmp4 + tmp2 * tmp3); c += tmp2 * tmp4;
	tmp1 = v[i].y-v[j].y; tmp2 = p[i].y-p[j].y; tmp3 = v[i].x; tmp4 = p[i].x;
	a -= tmp1 * tmp3; b -= (tmp1 * tmp4 + tmp2 * tmp3); c -= tmp2 * tmp4;
	tmp1 = v[j].x-v[i].x; tmp2 = p[j].x-p[i].x; tmp3 = v[i].y; tmp4 = p[i].y;
	a -= tmp1 * tmp3; b -= (tmp1 * tmp4 + tmp2 * tmp3); c -= tmp2 * tmp4;
	if (fabs(a)<eps) { if (fabs(b)<eps) { ans[0] = 0.0; return 1; } ans[0] = -c / b; return 1; } 
	b /= a; c /= a; a = b*b / 4 - c; if (a < -eps) return 0; if (a < eps) a = 0;
	ans[0] = sqrt(a) - b / 2; ans[1] = -sqrt(a) - b / 2; 
	return 2;
}

bool cmp(const pnt &p1, const pnt &p2) { return (fabs(p1.x-p2.x)<eps && fabs(p1.y-p2.y)<eps); }

void checkline(int a, int b, int c)
{
	int i, j, tmp, cnt; line pl; double ans[2];
	cnt = gettime(a, b, c, ans); if (!cnt) return;
	for (j = 0; j < cnt; ++j) {
		if (ans[j] < eps) continue; if (ans[j] - floor(ans[j]+eps) > eps) continue;
		if (cmp(p[a]+v[a]*ans[j], p[b]+v[b]*ans[j])) {
			if (cmp(p[c]+v[c]*ans[j], p[a]+v[a]*ans[j])) {
				for (seq[0] = tmp = i = 0; i < n; ++i) if (cmp(p[a]+v[a]*ans[j], p[i]+v[i]*ans[j])) { tmp++; seq[++seq[0]] = i; }
				if (tmp > ret) { ret = tmp; memset(vst, 0, sizeof(vst)); for (i = 1; i <= seq[0]; ++i) vst[seq[i]] = true; }
				continue;
			} else pl = getline(p[a]+v[a]*ans[j], p[c]+v[c]*ans[j]);
		} else pl = getline(p[a]+v[a]*ans[j], p[b]+v[b]*ans[j]);
		for (seq[0] = tmp = i = 0; i < n; ++i) if (fabs(oridis(pl, p[i]+v[i]*ans[j]))<eps) { tmp++; seq[++seq[0]] = i; }	
		if (tmp > ret) { ret = tmp; memset(vst, 0, sizeof(vst)); for (i = 1; i <= seq[0]; ++i) vst[seq[i]] = true; }
	}
}

void conduct()
{
	int i, j, k;
	memset(vst, 0, sizeof(vst));
	if (n < 3) { printf("%d\n", n); return; }
	for (ret = 2, i = 0; i < n; ++i)
		for (j = i+1; j < n; ++j) for (k = j+1; k < n; ++k) checkline(i, j, k);
	printf("%d\n", ret);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) { input(); conduct(); }
	return 0;
}
