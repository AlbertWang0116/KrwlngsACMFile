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
struct line { double a, b, c;};
#define vctor point
#define MAX 10001
#define N 100
#define eps 1e-6
int n;
point st, lst, p[N];
line ori, stk[N];

vctor getvec(point p1, point p2)
{
	vctor ret;
	ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y;
	return ret;
}

vctor unitvec(point p1, point p2)
{
	vctor ret;
	double dis = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	ret.x = (p2.x - p1.x) / dis;
	ret.y = (p2.y - p1.y) / dis;
	return ret;
}

vctor vervec(line l) { vctor ret; ret.x = l.a; ret.y = l.b; return ret;}
vctor horvec(line l) { vctor ret; ret.x = l.b; ret.y = -l.a; return ret;}

double judge(line l, point p) { return l.a * p.x + l.b * p.y - l.c; }

int nummul(vctor v1, vctor v2)
{
	double ret = v1.x * v2.x + v1.y * v2.y;
	if (ret > eps) return 1; if (ret < -eps) return -1; return 0;
}

point getcrs(line l1, line l2)
{
	point ret;
	ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b);
//	printf("l1:%.3f,%.3f,%.3f l2:%.3f,%.3f,%.3f ret:%.3f,%.3f\n", l1.a, l1.b, l1.c, l2.a, l2.b, l2.c, ret.x, ret.y);
	return ret;
}

line getline(point p1, point p2)
{
	line ret;
	vctor vec = unitvec(p1, p2);
	ret.a = -vec.y;
	ret.b = vec.x;
	ret.c = ret.a * p1.x + ret.b * p1.y;
	return ret;
}

void init()
{
	point p1, p2;
	srand(time(0));
	st.x = -MAX; st.y = -MAX;
	p1.x = -MAX; p1.y = -MAX; p2.x = MAX; p2.y = -MAX; stk[0] = getline(p1, p2);
	p1.x = MAX; p1.y = MAX; stk[1] = getline(p2, p1); p2.x = -MAX; p2.y = MAX; stk[2] = getline(p1, p2);
	p1.x = -MAX; p1.y = -MAX; stk[3] = getline(p2, p1);
	p1.x = -1; p1.y = 0; p2.x = 1; p2.y = 0; ori = getline(p1, p2);
//	printf("stk[0]:%.3f,%.3f,%.3f stk[1]:%.3f,%.3f,%.3f stk[2]:%.3f,%.3f,%.3f stk[3]:%.3f,%.3f,%.3f\n", stk[0].a, stk[0].b, stk[0].c, stk[1].a, stk[1].b, stk[1].c, stk[2].a, stk[2].b, stk[2].c, stk[3].a, stk[3].b, stk[3].c);
}

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%lf %lf", &p[i].x, &p[i].y);
	p[n] = p[0];
}	

bool insert(line l, int idx)
{
	int i;
	bool th, tt;
	vctor base;
	point crs, head, tail;
//	printf("idx:%d\n", idx);
	stk[idx] = l;
	if (judge(l, lst) > -eps) return true;
	th = false; tt = false; base = horvec(l); 
	for (i = 0; i < idx; ++i)
	{
		crs = getcrs(l, stk[i]);
		switch (nummul(base, vervec(stk[i])))
		{
		case 1:
			if (!th || nummul(getvec(head, crs), base) > 0) { th = true; head = crs; /*printf("i:%d head:%.3f,%.3f\n", i, head.x, head.y);*/}
			break;
		case -1:
			if (!tt || nummul(getvec(crs, tail), base) > 0) { tt = true; tail = crs; /*printf("i:%d tail:%.3f,%.3f\n", i, head.x, head.y);*/}
			break;
		}
	}
	if (nummul(getvec(head, tail), base) < 0) return false;
	if (judge(ori, head) > judge(ori, tail)) lst = tail;
	else lst = head;
	return true;
}

void conduct()
{
	int i;
	lst = st;
	for (i = 0; i < n; ++i) if (!insert(getline(p[i], p[i+1]), i+4)) break;
	if (i == n) cout << 1 << endl;
	else cout << 0 << endl;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	init();
	while (scanf("%d", &n) != EOF && n)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

