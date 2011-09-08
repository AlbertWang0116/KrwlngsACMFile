#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;

struct pnt { double x, y; };
typedef pnt vec;
#define N 210
pnt p[N], q[N], ori, des;
bool m[N][N], *up[N], *dn[N], *lft[N], *rit[N];
int n;
const double eps = 1e-8;

int getmin(int x, int y) { return x < y ? x : y; }

vec getvec(pnt p1, pnt p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

int submul(vec v1, vec v2) {
	double tmp = v1.x * v2.y - v2.x * v1.y;
	if (tmp > eps) return 1; else if (tmp < -eps) return -1; return 0;
}

void input()
{
	int i, x1, y1, x2, y2;
	for (i = 0; i <= 100; ++i) { up[i] = &m[i][100]; dn[i] = &m[i][0]; lft[i] = &m[0][i]; rit[i] = &m[100][i]; }
	memset(m, false, sizeof(m));
	scanf("%d", &n);
	for (i = 0; i < n; ++i) { 
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2); 
		m[x1][y1] = true; m[x2][y2] = true;
		p[i].x = x1; p[i].y = y1; q[i].x = x2; q[i].y = y2;
	}
	scanf("%lf%lf", &des.x, &des.y);
}

int judge()
{
	int ret = 0, i;
	vec path = getvec(ori, des);
	for (i = 0; i < n; ++i) if (submul(path, getvec(ori, p[i])) * submul(path, getvec(ori, q[i])) < 0 &&
								submul(getvec(p[i], q[i]), getvec(p[i], ori)) * submul(getvec(p[i], q[i]), getvec(p[i], des)) < 0) ret++;
	return ret;
}

void conduct()
{
	int i, ans;
	ans = 100;
	ori.y = 0; for (i = 0; i < 100; ++i) if (!i || *dn[i]) { ori.x = i + 0.5; ans = getmin(judge(), ans); }
	ori.y = 100; for (i = 0; i < 100; ++i) if (!i || *up[i]) { ori.x = i + 0.5; ans = getmin(judge(), ans); }
	ori.x = 0; for (i = 0; i < 100; ++i) if (!i || lft[i]) { ori.y = i + 0.5; ans = getmin(judge(), ans); }
	ori.x = 100; for (i = 0; i < 100; ++i) if (!i || rit[i]) { ori.y = i + 0.5; ans = getmin(judge(), ans); }
	printf("Number of doors = %d\n", ++ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

