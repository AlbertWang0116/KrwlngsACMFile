#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

struct point { double x, y; };
struct line { double a, b, c; };

#define vctor point
#define N 10010
#define eps 1e-6
point p[N], peg;
int n;
double pr;

vctor getvec(point p1, point p2)
{
	vctor ret;
	ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y;
	return ret;
}

int submul(vctor v1, vctor v2)
{
	double ret = v1.x * v2.y - v2.x * v1.y;
	if (ret > eps) return 1;
	if (ret < -eps) return -1;
	return 0;
}

int nummul(vctor v1, vctor v2)
{
	double ret = v1.x * v2.x + v1.y * v2.y;
	if (ret > eps) return 1;
	if (ret < -eps) return -1;
	return 0;
}

line getline(point p1, point p2)
{
	line ret;
	ret.a = p1.y - p2.y;
	ret.b = p2.x - p1.x;
	ret.c = ret.a * p1.x + ret.b * p1.y;
	return ret;
}

double getdis(line l, point p)
{
	return fabs(l.a * p.x + l.b * p.y - l.c) / sqrt(l.a * l.a + l.b * l.b);
}

void input()
{
	int i;
	scanf("%lf %lf %lf", &pr, &peg.x, &peg.y);
	for (i = 0; i < n; ++i) scanf("%lf %lf", &p[i].x, &p[i].y);
	p[n] = p[0]; p[n+1] = p[1];
}

void conduct()
{
	int i, judge;
	for (i = 0; i < n; ++i) if ((judge = submul(getvec(p[i], p[i+1]), getvec(p[i+1], p[i+2]))) != 0) break;
	for (; i < n; ++i) if (judge * submul(getvec(p[i], p[i+1]), getvec(p[i+1], p[i+2])) < 0) break;
	if (i < n) { cout << "HOLE IS ILL-FORMED" << endl; return; }
	for (i = 0; i < n; ++i) if ((judge = submul(getvec(peg, p[i]), getvec(peg, p[i+1]))) != 0) break;
	for (; i < n; ++i) if (judge * submul(getvec(peg, p[i]), getvec(peg, p[i+1])) < 0) break;
	if (i < n) { cout << "PEG WILL NOT FIT" << endl; return; }
	for (i = 0; i < n; ++i) if (getdis(getline(p[i], p[i+1]), peg) - pr < -eps) break;
	if (i < n) { cout << "PEG WILL NOT FIT" << endl; return; }
	cout << "PEG WILL FIT" << endl;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF && n >= 3)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

