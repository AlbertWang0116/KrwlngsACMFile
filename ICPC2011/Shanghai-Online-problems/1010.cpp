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
	long long x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	}
	pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	}
	pnt operator*(const long long &c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	}
};
typedef pnt vec;
#define N 110
const double eps = 1e-16;
pnt p[N];
vec v[N];
int n, ans;

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%I64d%I64d%I64d%I64d", &p[i].x, &p[i].y, &v[i].x, &v[i].y);
}

bool cmp(const pnt &p1, const pnt &p2) { return (p1.x == p2.x && p1.y == p2.y); }
long long submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

int gettime(int i, int j, int k, long long* clk)
{
	int ret; long long tmp;
	pnt s1 = p[j] - p[i], s2 = p[k] - p[i]; vec t1 = v[j] - v[i], t2 = v[k] - v[i];
	long long a = submul(t1, t2), b = submul(t1, s2) - submul(t2, s1), c = submul(s1, s2);
	long long tmp1, tmp2; if (a < 0) tmp1 = -a; else tmp1 = a; if (c<0) tmp2 = -c; else tmp2 = c;
	if (b*b < 0) while(1); if (tmp1*tmp2*4<0) while (1);
	if (a == 0) {
		if (b == 0) { clk[0] = 1; return 1; }
		else { tmp = -c / b; if (tmp > 0 && tmp * b == -c) {clk[0] = tmp; return 1; } else return 0; }
	} tmp = b * b - 4 * a * c;  if (tmp < 0) return 0;	
//	printf("a:%lld b:%lld c:%lld tmp:%lld\n", a, b, c, tmp);
	long long d = sqrtl((long double)tmp); if (d * d != tmp) return 0; ret = 0;
	tmp = (d - b) / (2 * a); if (tmp > 0 && tmp * a * 2 == d - b) clk[ret++] = tmp;
	tmp = (-d- b) / (2 * a); if (tmp > 0 && tmp * a * 2 == -d -b) clk[ret++] = tmp;
	return ret;
}

void cal(int a, int b, int c)
{
	int i, j, cnt, tmp; pnt p1, p2, p3; vec ori;
	long long clk[2];
	cnt = gettime(a, b, c, clk);
	for (i = 0; i < cnt; ++i) {
//		printf("a:%d b:%d c:%d clk:%lld\n", a, b, c, clk[i]);
		p1 = p[a]+v[a]*clk[i]; p2 = p[b]+v[b]*clk[i]; p3 = p[c]+v[c]*clk[i];
		if (cmp(p1, p2) && cmp(p2, p3)) {
			for (tmp = j = 0; j < n; ++j) if (cmp(p1, p[j]+v[j]*clk[i])) tmp++;
			if (tmp > ans) ans = tmp;
		} else {
			if (cmp(p1, p2)) ori = p3 - p2; else ori = p2 - p1;
			for (tmp = j = 0; j < n; ++j) if (submul(ori, (p[j]+v[j]*clk[i])-p1) == 0) tmp++;
			if (tmp > ans) ans = tmp;
		}
	}
}

void conduct()
{
	int i, j, k;
	if (n < 2) { printf("%d\n", n); return ; }
	for (ans = 2, i = 0; i < n; ++i)
		for (j = i+1; j < n; ++j) for (k = j+1; k < n; ++k) cal(i, j, k);
	printf("%d\n", ans);
}

int main()
{
	while (scanf("%d", &n) != EOF && n) { input(); conduct(); }
	return 0;
}
