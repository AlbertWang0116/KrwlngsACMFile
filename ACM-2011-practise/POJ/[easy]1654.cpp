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
		pnt ret; ret.x = x + p.x; ret.y = y + p.y; return ret;
	};
};
typedef pnt vec;
pnt p, q;
char str[1000], cmd;
const vec dp[9] = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} };
int n;

long long submul(const vec &v1, const vec &v2) { return v1.x*v2.y - v2.x*v1.y; }

void conduct()
{
	long long ret; int i;
	p = (pnt){ 0, 0 }; gets(str); ret = 0;
	while ((cmd = getchar()) != '5') { q = p + dp[cmd-'1']; ret += submul(p, q); p = q; }
	if (ret < 0) ret = -ret; if (ret % 2) printf("%lld.5\n", ret/2); else printf("%lld\n", ret/2);
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
