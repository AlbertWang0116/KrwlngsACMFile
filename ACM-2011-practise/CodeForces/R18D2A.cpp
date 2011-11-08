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
	int x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
const pnt dp[4] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
pnt p1, p2, p3, tp;

int nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
int submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

bool judge(const pnt &p1, const pnt &p2, const pnt &p3) {
	if (!submul(p2-p1, p3-p1)) return 0;
	if (!nummul(p2-p1, p3-p1)) return 1;
	if (!nummul(p3-p2, p1-p2)) return 1;
	if (!nummul(p1-p3, p2-p3)) return 1;
	return 0;
}

void conduct() {
		int i;
		if (judge(p1, p2, p3)) { printf("RIGHT\n"); return; }
		else {
			for (i = 0; i < 4; ++i) {
				tp = p1 + dp[i];
				if (judge(tp, p2, p3)) { printf("ALMOST\n"); return; }
			} for (i = 0; i < 4; ++i) {
				tp = p2 + dp[i];
				if (judge(p1, tp, p3)) { printf("ALMOST\n"); return; }
			} for (i = 0; i < 4; ++i) {
				tp = p3 + dp[i];
				if (judge(p1, p2, tp)) { printf("ALMOST\n"); return; }
			} printf("NEITHER\n");
		}
}

int main()
{
	scanf("%d%d%d%d%d%d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
	conduct(); return 0;
}
