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

#define getvec(x, y) ((y)-(x))
struct pnt {
	long long x, y;
	pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x; ret.y = y - p.y; return ret;
	} bool operator<(const pnt &p) const {
		if (p.y == y) return x < p.x;
		return y < p.y;
	}
};
typedef pnt vec;
pnt p1, p2;

long long submul(const vec &v1, const vec &v2) { return v1.x*v2.y - v2.x*v1.y; }

bool checkcrs(pnt p1, pnt p2, pnt q1, pnt q2)
{
	pnt tmp;
	if (p2 < p1) { tmp = p2; p2 = p1; p1 = tmp; }
	if (q2 < q1) { tmp = q2; q2 = q1; q1 = tmp; }
	if ((p2 < q1) || (q2 < p1)) return false;
	if (submul(getvec(p1, p2), getvec(p1, q1)) * submul(getvec(p1, p2), getvec(p1, q2)) > 0) return false;
	if (submul(getvec(q1, q2), getvec(q1, p1)) * submul(getvec(q1, q2), getvec(q1, p2)) > 0) return false;
	return true;
}

void conduct()
{
	long long lft, rit, up, dn, tmp;
	scanf("%lld%lld%lld%lld", &p1.x, &p1.y, &p2.x, &p2.y);
	scanf("%lld%lld%lld%lld", &lft, &up, &rit, &dn);
	if (lft > rit) { tmp = lft; lft = rit; rit = tmp; }
	if (dn > up) { tmp = dn; dn = up; up = tmp; } 
	if (p1.x >= lft && p1.x <= rit && p1.y >= dn && p1.y <= up) { printf("T\n"); return; }
	if (p2.x >= lft && p2.x <= rit && p2.y >= dn && p2.y <= up) { printf("T\n"); return; }
	pnt q1 = { lft, dn}, q2 = { lft, up}, q3 = { rit, up}, q4 = { rit, dn};
	if (checkcrs(p1, p2, q1, q2) || checkcrs(p1, p2, q2, q3) ||
		checkcrs(p1, p2, q3, q4) || checkcrs(p1, p2, q4, q1)) printf("T\n");
	else printf("F\n");
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
