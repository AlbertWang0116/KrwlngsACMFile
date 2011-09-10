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

struct node { int des, next; };
#define N 10010
#define M 1000010
node way[M];
int rd[N], a[N], b[N], seq[N], col[N], cpn[N];
bool vst[N];
int n, m, rc, cnt;

bool judge(int x, int y)
{
	bool tag1, tag2;
	if (a[x] >= a[y] && a[x] <= b[y]) tag1 = true; else tag1 = false;
	if (b[x] >= a[y] && b[x] <= b[y]) tag2 = true; else tag2 = false;
	return (tag1 ^ tag2);
}

void input()
{
	int i, j, tmp;
	scanf("%d %d", &n, &m); rc = 0;
	for (i = 1; i <= m; ++i) {
		scanf("%d %d", &a[i], &b[i]);
		if (a[i] > b[i]) { tmp = a[i]; a[i] = b[i]; b[i] = tmp; }
	}
	for (i = 1; i <= m; ++i) { cpn[i*2-1] = i*2; cpn[i*2] = i*2-1; }
	memset(rd, 0, sizeof(rd));
	for (i = 1; i <= m; ++i) for (j = i+1; j <= m; ++j) if (judge(i, j))
	{
		way[++rc].des = i*2-1; way[rc].next = rd[j*2]; rd[j*2] = rc;
		way[++rc].des = i*2; way[rc].next = rd[j*2-1]; rd[j*2-1] = rc;
		way[++rc].des = j*2-1; way[rc].next = rd[i*2]; rd[i*2] = rc;
		way[++rc].des = j*2; way[rc].next = rd[i*2-1]; rd[i*2-1] = rc;
	}
}

void dfs(int x)
{
	int i;
	vst[x] = true;
	for (i = rd[x]; i; i = way[i].next) if (!vst[way[i].des]) dfs(way[i].des);
	seq[++cnt] = x;
}

void dfs2(int x, int c)
{
	int i, j;
	vst[x] = true; col[x] = c;
	for (i = rd[cpn[x]]; i; i = way[i].next) {
		j = cpn[way[i].des];
		if (!vst[j]) dfs2(j, c);
	}
}

void conduct()
{
	int i;
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 1; i <= m*2; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = m*2; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
	for (i = 1; i <= m; ++i) if (col[i*2] == col[i*2-1]) break;
	if (i <= m) printf("the evil panda is lying again\n");
	else printf("panda is telling the truth...\n");
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

