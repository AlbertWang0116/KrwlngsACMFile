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

struct node { int idx, tp; };
#define N 400010
node p[N];
int seq[N];
int n, nx, ny, len;

int cmp(const int &x, const int &y) { return p[x].idx < p[y].idx; }

void input()
{
	int i, st, ed;
	n = nx + ny; len++;
	for (i = 1; i <= nx; ++i) {
		scanf("%d %d", &st, &ed); ed++;
		p[i*2-1].idx = st; p[i*2].idx = ed;
		p[i*2-1].tp = p[i*2].tp = 0;
	}
	for (i = nx+1; i <= n; ++i)
	{
		scanf("%d %d", &st, &ed); ed++;
		p[i*2-1].idx = st; p[i*2].idx = ed;
		p[i*2-1].tp = p[i*2].tp = 1;
	}
	for (i = 1; i <= 2*n; ++i) seq[i] = i;
	std::sort(seq+1, seq+2*n+1, cmp);
//	for (i = 1; i <= 2*n; ++i) printf("%d idx:%d tp:%d\n", seq[i], p[seq[i]].idx, p[seq[i]].tp);
}

void conduct()
{
	int i, j, k;
	int ans, cur, pre, stt[2];
	ans = 0; cur = 0; pre = 0; stt[0] = 0; stt[1] = 0;
	for (i = 1; i <= 2*n; ++i)
	{
		j = i; k = p[seq[i]].idx;
		if ((stt[0] ^ stt[1])) cur += k - pre; else cur = 0;
		for (j; j <= 2*n && p[seq[j]].idx == k; ++j) stt[p[seq[j]].tp] = 1 - stt[p[seq[j]].tp];
		i = j-1; pre = k; if (cur > ans) ans = cur;
//		printf("k:%d 0:%d 1:%d cur:%d\n", k, stt[0], stt[1], cur);
	}
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d %d %d", &len, &nx, &ny) != EOF)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

