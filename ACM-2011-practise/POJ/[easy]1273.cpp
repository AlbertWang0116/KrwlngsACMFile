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

#define N 300
int cap[N][N], flw[N][N], seq[N], pre[N], lst[N];
bool vst[N];
int n, m;
const int MAX = 1000000000;

int getmin(int x, int y) { return x < y ? x : y; }

void input()
{
	int i, st, ed, len;
	memset(cap, 0, sizeof(cap));
	for (i = 0; i < m; ++i) {
		scanf("%d %d %d", &st, &ed, &len);
		cap[st][ed] += len;
	}
}

void conduct()
{
	int i, j, head, tail;
	memset(flw, 0, sizeof(flw));;
	do {
		seq[0] = 1; memset(vst, false, sizeof(vst)); vst[1] = true; 
		memset(pre, 0, sizeof(pre)); lst[1] = MAX; lst[n] = 0;
		for (head = tail = 0; !vst[n] && head <= tail; ++head) {
			i = seq[head];
			for (j = 1; j <= n; ++j) if (!vst[j] && cap[i][j] - flw[i][j]) {
				vst[j] = true; seq[++tail] = j; lst[j] = getmin(lst[i], cap[i][j]-flw[i][j]); pre[j] = i;
			}
		}
		for (i = n; i; i = pre[i]) { flw[pre[i]][i] += lst[n]; flw[i][pre[i]] -= lst[n]; }
	} while (vst[n]);
	printf("%d\n", flw[0][1]);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d %d", &m, &n) != EOF)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

