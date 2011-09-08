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

struct edge { int next; };
#define N 10010
edge e[N];
int v[N], ans[N][3], cnt[N], rd[N];
int n, m;

void input()
{
	int i, pre;
	scanf("%d", &v[0]);
	memset(rd, 0, sizeof(rd));
	for (i = 1; i < n; ++i)
	{
		scanf("%d %d", &pre, &v[i]);
		e[i].next = rd[pre]; rd[pre] = i;
	}
}

void dfs(int x)
{
	int i, j, k, l, tmp;
	cnt[x] = 1; for (i = 0; i < 3; ++i) ans[x][i] = -1; ans[x][0] = v[x];
	for (i = rd[x]; i; i = e[i].next)
	{
		dfs(i);
		cnt[x] += cnt[i];
		for (j = 0; j < 3; ++j)
		{
			k = ans[i][j];
			for (l = 0; l < 3; ++l) if (ans[x][l] < k) { tmp = ans[x][l]; ans[x][l] = k; k = tmp; }
		}
	}
}

void conduct()
{
	int q, i;
	memset(cnt, 0, sizeof(cnt));
	dfs(0);
	scanf("%d", &q);
	while (q--) { 
		scanf("%d", &m);
		if (cnt[m] < 3) printf("-1\n");
		else { printf("%d", ans[m][0]); for (i = 1; i < 3; ++i) printf(" %d", ans[m][i]); printf("\n"); }
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

