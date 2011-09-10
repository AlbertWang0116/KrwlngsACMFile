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
pnt p[N], pp[N];
bool typ[N];
int n;

vec getvec(pnt p1, pnt p2)
{
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

int submul(vec v1, vec v2) { return v1.x * v2.y - v2.x * v1.y; }
int cmp(const pnt &p1, const pnt &p2) { return p1.y < p2.y ? 1 : (p1.y == p2.y && p1.x < p2.x ? 1 : 0); }

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
}

void conduct()
{
	int i, top, bot, val, cnt;
	sort(p, p+n, cmp);
//	for (i = 0; i < n; ++i) printf("%d %d\n", p[i].x, p[i].y);
	top = 0; pp[0] = p[0];
	for (i = 1; i < n; ++i) {
		while (top > 0 && (val = submul(getvec(pp[top-1], pp[top]), getvec(pp[top], p[i]))) < 0) top--;
		if (top > 0 && !val) typ[top] = true; else typ[top] = false; pp[++top] = p[i];
	}
	bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && (val = submul(getvec(pp[top-1], pp[top]), getvec(pp[top], p[i]))) < 0) top--;
		if (top > bot && !val) typ[top] = true; else typ[top] = false; pp[++top] = p[i];
	} typ[top] = false;
	for (i = cnt = 0; i < top; ++i) {
		if (!typ[i]) cnt++;
		if (!(typ[i] || typ[i+1])) break;
	}
//	printf("i:%d cnt:%d\n", i, cnt);
//	for (i = 0; i < top; ++i) printf("%d ", typ[i]); printf("\n");
//	for (i = 0; i < top; ++i) printf("%d %d\n", pp[i].x, pp[i].y);
	if (i < top || cnt < 3) printf("NO\n"); else printf("YES\n");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

