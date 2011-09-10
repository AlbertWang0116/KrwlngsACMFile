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
#define N 40
#define eps 1e-6
int n;
point mat[N][N];
double a[N], b[N], c[N], d[N];

double getmax(double x, double y) { return x > y ? x : y;}

double submul(vctor v1, vctor v2)
{
	return v1.x * v2.y - v2.x * v1.y;
}

line getline(point p1, point p2)
{
	line ret;
	ret.a = p1.y - p2.y;
	ret.b = p2.x - p1.x;
	ret.c = ret.a * p1.x + ret.b * p1.y;
	return ret;
}

point getcrs(line l1, line l2)
{
	point ret;
	ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b);
	return ret;
}

void input()
{
	int i, j;
	for (i = 1; i <= n; ++i) {scanf("%lf", &a[i]); mat[0][i].y = 0; mat[0][i].x = a[i];}
	for (i = 1; i <= n; ++i) {scanf("%lf", &b[i]); mat[n+1][i].y = 1; mat[n+1][i].x = b[i];}
	for (i = 1; i <= n; ++i) {scanf("%lf", &c[i]); mat[i][0].x = 0; mat[i][0].y = c[i];}
	for (i = 1; i <= n; ++i) {scanf("%lf", &d[i]); mat[i][n+1].x = 1; mat[i][n+1].y = d[i];}
	mat[0][0].x = 0; mat[0][0].y = 0; mat[0][n+1].x = 1; mat[0][n+1].y = 0;
	mat[n+1][0].x = 0; mat[n+1][0].y = 1; mat[n+1][n+1].x = 1; mat[n+1][n+1].y = 1;
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j) mat[i][j] = getcrs(getline(mat[i][0], mat[i][n+1]), getline(mat[0][j], mat[n+1][j]));
}

void conduct()
{
	double ans;
	int i, j;
	ans = 0;
	for (i = 0; i <= n; ++i)
		for (j = 0; j <= n; ++j) ans = getmax(ans, submul(mat[i][j], mat[i][j+1]) + submul(mat[i][j+1], mat[i+1][j+1]) +
												   submul(mat[i+1][j+1], mat[i+1][j]) + submul(mat[i+1][j], mat[i][j]));
	printf("%.6f\n", ans/2);
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

