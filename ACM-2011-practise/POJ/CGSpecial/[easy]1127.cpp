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
#define getmax(x, y) ((x)>(y)?(x):(y))
#define getmin(x, y) ((x)<(y)?(x):(y))
pnt p[N], q[N];
int root[N];
int n;

void input()
{
	int i;
	for (i = 1; i <= n; ++i) scanf("%d%d%d%d", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
}

int getroot(int x) { if (root[x] == x) return x; else return (root[x] = getroot(root[x])); }

vec getvec(pnt p1, pnt p2) {
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

int submul(vec v1, vec v2) { return v1.x * v2.y - v2.x * v1.y; }

bool cross(int i, int j)
{
	if ((p[i].x-p[j].x)*(p[i].x-q[j].x) > 0 && (q[i].x-p[j].x)*(q[i].x-q[j].x) > 0 && (p[j].x-p[i].x)*(p[j].x-q[i].x) > 0) return false;
	if ((p[i].y-p[j].y)*(p[i].y-q[j].y) > 0 && (q[i].y-p[j].y)*(q[i].y-q[j].y) > 0 && (p[j].y-p[i].y)*(p[j].y-q[i].y) > 0) return false;
	return (submul(getvec(p[i], q[i]), getvec(p[i], p[j])) * submul(getvec(p[i], q[i]), getvec(p[i], q[j])) <= 0 &&
			submul(getvec(p[j], q[j]), getvec(p[j], p[i])) * submul(getvec(p[j], q[j]), getvec(p[j], q[i])) <= 0 );
}

void conduct()
{
	int i, j;
	for (i = 1; i <= n; ++i) root[i] = i;
	for (i = 1; i <= n; ++i) for (j = i+1; j <= n; ++j)
		if (getroot(i) != getroot(j) && cross(i, j)) root[root[i]] = root[j];
	while (scanf("%d%d", &i, &j) != EOF && i && j)
		if (getroot(i) == getroot(j)) printf("CONNECTED\n"); else printf("NOT CONNECTED\n");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF && n)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

