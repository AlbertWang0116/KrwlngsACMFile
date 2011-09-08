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

struct pnt { double x, y; };
struct node { int stt, des; double dis; };
struct node2 { int idx, next; };
#define N 110
#define M 10010
int n, m;
node info[M];
node2 way[N];
int seq[N], in[N], color[N], colcnt[N], head[N];
double val[N], tmp[N], len[N];
bool valid[M], vst[N];
pnt p[N];

double getdis(pnt p1, pnt p2) { return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y)); }

void input()
{
	int i, st, ed;
	for (i = 1; i <= n; ++i) scanf("%lf %lf", &p[i].x, &p[i].y);
	memset(valid, true, sizeof(valid));
	for (i = 1; i <= m; ++i)
	{
		scanf("%d %d", &st, &ed);
		info[i].stt = st; info[i].des = ed; info[i].dis = getdis(p[st], p[ed]);
		if (ed == 1 || st == ed) valid[i] = false;
	}
	memset(val, 0, sizeof(val));
}

bool selectway()
{
	int i;
	memset(in, 0, sizeof(in));
	for (i = 1; i <= m; ++i)
		if (valid[i] && (!in[info[i].des] || info[i].dis < len[info[i].des])) { in[info[i].des] = i; len[info[i].des] = info[i].dis; }
	for (i = 2; i <= n; ++i) if (!in[i]) return false;
	return true;
}

void dfs(int x)
{
	int i; vst[x] = true;
	for (i = head[x]; i; i = way[i].next) if(!vst[info[way[i].idx].des]) dfs(info[way[i].idx].des);
	seq[++seq[0]] = x;
}

void dfs2(int x, int col)
{
	color[x] = col; vst[x] = true; if (x == 1) return;
	if (!vst[info[in[x]].stt]) dfs2(info[in[x]].stt, col);
}

bool checkcircle()
{
	int i, j;
	memset(head, 0, sizeof(head));
	for (i = 2; i <= n; ++i) { way[i].idx = in[i]; way[i].next = head[info[in[i]].stt]; head[info[in[i]].stt] = i; }
	seq[0] = 0; memset(vst, false, sizeof(vst));
	for (i = 1; i <= n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst));
	for (i = n, j = 0; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++j);
	if (n == j) return true;
	for (i = 1; i <= n; ++i) if (color[i] == 1) color[i] = color[1]; color[1] = 1;
	memset(tmp, 0, sizeof(tmp));
	for (i = 2; i <= n; ++i) tmp[color[i]] += val[i] + len[i];
	for (i = 1; i <= m; ++i) if (valid[i])
	{
		info[i].dis = info[i].dis - len[info[i].des];
		info[i].stt = color[info[i].stt];
		info[i].des = color[info[i].des];
		if (info[i].stt == info[i].des) valid[i] = false;
	}
	for (i = 1, n = j; i <= n; ++i) val[i] = tmp[i];
	return false;
}

void print()
{
	double ans = 0;
	int i;
	for (i = 2; i <= n; ++i) ans += val[i] + len[i];
	printf("%.2f\n", ans);
}

void conduct()
{
	while (true)
	{
		if (!selectway()) break;
		if (checkcircle()) { print(); return; }
	}
	printf("poor snoopy\n");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d %d", &n, &m) != EOF)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

