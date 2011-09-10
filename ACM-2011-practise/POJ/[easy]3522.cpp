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

struct edge { int st, ed, len; };
#define N 110
#define M 10010
const int MAX = 1000000000;
int root[N];
edge e[M];
int n, m;

int cmp(const edge &e1, const edge &e2) { return e1.len < e2.len; }

void input()
{
	int i;
	for (i = 1; i <= m; ++i) scanf("%d %d %d", &e[i].st, &e[i].ed, &e[i].len);
	std::sort(e+1, e+m+1, cmp);
}

int getroot(int x) { if (root[x] == x) return x; else return (root[x] = getroot(root[x])); }

void conduct()
{
	int i, j, ans, mst, lst, cnt;
	ans = MAX;
	for (i = 1; i <= m - n + 2; ++i)
	{
		for (j = 1; j <= n; ++j) root[j] = j; cnt = 0;
		for (j = i; j <= m; ++j) if (getroot(e[j].st) != getroot(e[j].ed))
		{
			if (!cnt) lst = e[j].len; ++cnt; if (cnt == n-1) { mst = e[j].len; break; }
			root[root[e[j].st]] = root[e[j].ed];
		}
		if (cnt < n-1) break;
		if (ans > mst - lst) ans = mst - lst;
	}
	if (ans == MAX) printf("-1\n"); else printf("%d\n", ans);
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

