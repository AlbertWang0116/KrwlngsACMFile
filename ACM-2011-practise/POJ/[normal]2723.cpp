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
node way[N];
int rd[N], id[N], cpn[N], chs[N], opp[N], seq[N], col[N]; 
bool vst[N];
int n, m, cnt;

void input()
{
	int i;
	for (i = 0; i < n; ++i)
	{
		scanf("%d %d", &id[2*i], &id[2*i+1]);
		opp[id[2*i]] = id[2*i+1]; opp[id[2*i+1]] = id[2*i];
	}
	memset(rd, 0, sizeof(rd));
	for (i = 0; i < m; ++i)
	{
		cpn[2*i] = 2*i+1; cpn[2*i+1] = 2*i;
		scanf("%d %d", &chs[2*i], &chs[2*i+1]);
		way[2*i+1].des = 2*i+1; way[2*i+1].next = rd[opp[chs[2*i]]]; rd[opp[chs[2*i]]] = 2*i+1;
		way[2*i+2].des = 2*i; way[2*i+2].next = rd[opp[chs[2*i+1]]]; rd[opp[chs[2*i+1]]] = 2*i+2;
	}
//	for (i = 0; i < 2*n ; ++i) { printf("%d: ", i); for (int j = rd[i]; j; j = way[j].next) printf("[%d] ", way[j].des); printf("\n"); }
//	for (i = 0; i < 2*m ; ++i) printf("cpn[%d]=[%d]\n", i, cpn[i]);
}

void dfs(int x)
{
	int i;
	vst[x] = true;
	for (i = rd[chs[x]]; i; i = way[i].next) if (way[i].des < m && !vst[way[i].des]) dfs(way[i].des);
	seq[++cnt] = x;
}

void dfs2(int x, int c)
{
	int i, des;
	vst[x] = true; col[x] = c;
	for (i = rd[chs[cpn[x]]]; i; i = way[i].next) { 
		des = cpn[way[i].des];
		if (des < m && !vst[des]) dfs2(des, c);
	}
}

bool judge(int upper)
{
	int i;
	m = upper * 2;
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 0; i < m; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = m; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
//	printf("upper:%d\n", upper); for (i = 0; i < m; ++i) printf("col[%d]=%d\n", i, col[i]);
	for (i = 0; i < upper; ++i) if (col[i*2] == col[i*2+1]) return false;
	return true;
}

void conduct()
{
	int lst, mst, mid;
	lst = 0; mst = m;
	while (lst != mst)
	{
		mid = (lst + mst) / 2 + 1;
		if (judge(mid)) lst = mid; else mst = mid-1;
	}
	printf("%d\n", lst);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d %d", &n, &m) != EOF && (n || m))
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

