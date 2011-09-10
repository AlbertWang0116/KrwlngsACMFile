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

#define N 110
int c[N][N], f[N][N], seq[N], pre[N], mst[N];
bool vst[N];
const int MAX = 1000000000;
int n, m, m1, m2;

int getmin(int x, int y) { return x < y ? x : y; }

void input()
{
	char tmp1, tmp2, tmp3, str[20];
	int i, st, ed, len;
	++n; memset(c, 0, sizeof(c));
	for (i = 0; i < m; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d%c%d", &tmp1, &st, &tmp2, &ed, &tmp3, &len);
//		printf("st[%d]ed[%d]len[%d]\n", st, ed, len);
		c[++st][++ed] += len;
	}
	for (i = 0; i < m1; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d", &tmp1, &ed, &tmp2, &len); 
		c[0][++ed] += len;
	}
	for (i = 0; i < m2; ++i) {
		scanf("%s", str);
		sscanf(str, "%c%d%c%d", &tmp1, &st, &tmp2, &len);
		c[++st][n] += len;
	}
}

void conduct()
{
	int i, j, head, tail, flw;
	memset(f, 0, sizeof(f)); flw = 0;
	do {
		memset(vst, 0, sizeof(vst));
		vst[0] = true; mst[0] = MAX; pre[0] = 0; seq[0] = 0;
		for (head = tail = 0; head <= tail && !vst[n]; ++head) {
			i = seq[head];
			for (j = 0; j <= n; ++j) if (!vst[j] && c[i][j] > f[i][j]) {
				vst[j] = true; pre[j] = i; seq[++tail] = j; mst[j] = getmin(mst[i], c[i][j] - f[i][j]);
			}
		}
		for (i = n; vst[n] && i; i = pre[i]) { f[pre[i]][i] += mst[n]; f[i][pre[i]] -= mst[n]; }
		if (vst[n]) flw += mst[n];
	} while(vst[n]);
	printf("%d\n", flw);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d%d%d%d", &n, &m1, &m2, &m) != EOF)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

