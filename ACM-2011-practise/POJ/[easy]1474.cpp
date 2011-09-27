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

struct pnt { int x, y; };
typedef pnt vec;
#define N 1010
const int MIN = LONG_MIN;
pnt p[N];
const vec stv[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int val[4];
int n;

int getmax(int x, int y) { return x > y ? x : y; }

int submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }
int nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
vec getvec(const pnt &p1, const pnt &p2) {
	vec ret; ret.x = p2.x - p1.x; ret.y = p2.y - p1.y; return ret;
}

void conduct()
{
	int i, j, ans;
	for (i = 0; i < 4; ++i) val[i] = MIN;
	for (i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y); p[n] = p[0];
	for (i = 0; i < n; ++i) for (j = 0; j < 4; ++j) if (submul(getvec(p[i+1], p[i]), stv[j]) > 0) {
		val[j] = getmax(val[j], nummul(p[i], stv[j]));
	}
	if (val[0] <= -val[1] && val[2] <= -val[3]) printf("Surveillance is possible.\n\n");
	else printf("Surveillance is impossible.\n\n");
}

int main()
{
	int time = 0;
	while (scanf("%d", &n) != EOF && n) {
		printf("Floor #%d\n", ++time);
		conduct();
	} return 0;
}
