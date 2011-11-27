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

struct pnt { long long x, y; };
typedef pnt vec;

long long gcd(long long x, long long y) {
	if (!y) return x; return gcd(y, x % y);
}

long long submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

long long count(const pnt &p1, const pnt &p2) {
	long long dx, dy;
	dx = llabs(p2.x-p1.x); dy = llabs(p2.y-p1.y);
	return gcd(dx, dy);
}

int main() {
	pnt p1, p2, p3; long long ret;
	while (scanf("%lld%lld%lld%lld%lld%lld", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y) != EOF) {
		if (!p1.x && !p1.y && !p2.x && !p2.y && !p3.x && !p3.y) break;
		ret = submul(p1, p2) + submul(p2, p3) + submul(p3, p1);
		if (ret < 0) ret = -ret; ret += 2;
		ret -= count(p1, p2) + count (p1, p3) + count(p2, p3);
		printf("%lld\n", ret/2);
	} return 0;
}
