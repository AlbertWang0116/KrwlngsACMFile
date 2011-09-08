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

struct node { int des, len, next; };
#define N 30010
#define M 150010
node way[M];
int rd[N], dis[N], hp[N], ati[N];
bool vst[N];
int n, m, rc, cnt;
const int MAX = LONG_MAX;

void input()
{
	int i, st, ed, len;
	scanf("%d%d", &n, &m);
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%d", &st, &ed, &len);
		++rc; way[rc].des = ed; way[rc].len = len;
		way[rc].next = rd[st]; rd[st] = rc;
	}
}

int getele()
{
	int i, j, ele;
	int ret = hp[1];
	ati[ret] = 0; ele = hp[cnt--]; if (!cnt) return ret;
	for (i = 1, j = (i << 1); j <= cnt; i = j, j = (i << 1)) {
		if (j < cnt && dis[hp[j+1]] < dis[hp[j]]) j++;
		if (dis[hp[j]] < dis[ele]) { hp[i] = hp[j]; ati[hp[i]] = i; } else break;
	}
	ati[ele] = i; hp[i] = ele; return ret;
}

void update(int pos)
{
	int i, j, ele;
	ele = hp[pos];
	for (i = pos, j = (i >> 1); j; i = j, j = (i >> 1))
		if (dis[ele] < dis[hp[j]]) { hp[i] = hp[j]; ati[hp[i]] = i; } else break;
	ati[ele] = i; hp[i] = ele;
}

void conduct()
{
	int i, u, v;
	for (i = 1; i <= n; ++i) dis[i] = MAX; dis[1] = 0;
	memset(vst, 0, sizeof(vst)); 
	memset(ati, 0, sizeof(ati)); hp[cnt = 1] = 1; ati[1] = 1;
	while (cnt) {
		u = getele(); vst[u] = true;
		for (i = rd[u]; i; i = way[i].next) if (!vst[way[i].des] && dis[way[i].des] > dis[u] + way[i].len) {
			v = way[i].des; if (!ati[v]) hp[ati[v] = ++cnt] = v;
			dis[v] = dis[u] + way[i].len; update(ati[v]);
		}
	}
	printf("%d\n", dis[n]);
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

