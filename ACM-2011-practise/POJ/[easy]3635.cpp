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

struct node { int des, len, next; };
struct node1 { int st, ed, len; };
struct node2 { int idx, cap; };
#define N 1010
#define M 20010
#define L 110
const int MAX = 1000000000;
int unt[N];
node way[M];
node1 road[M];
node2 hp[N*L];
int dis[N][L], ati[N][L], rd[N];
int n, m, cnt, st, ed, cap;

int cmp(const node1 &p1, const node1 &p2) { return (p1.len > p2.len); }

void input()
{
	int i;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; ++i) scanf("%d", &unt[i]);
	for (i = 1; i <= m; ++i) scanf("%d %d %d", &road[i].st, &road[i].ed, &road[i].len);
	std::sort(road+1, road+m+1, cmp);
	memset(rd, 0, sizeof(rd));
	for (i = 1; i <= m; ++i)
	{
		way[i*2-1].des = road[i].ed; way[i*2-1].next = rd[road[i].st]; rd[road[i].st] = i*2-1;
		way[i*2].des = road[i].st; way[i*2].next = rd[road[i].ed]; rd[road[i].ed] = i*2;
		way[i*2-1].len = way[i*2].len = road[i].len;
	}
}

node2 getele()
{
	int i, j;
	node2 ret = hp[1]; ati[ret.idx][ret.cap] = 0;
	node2 e = hp[cnt--]; if (!cnt) return ret;
	for (i = 1, j = (i << 1); j <= cnt; i = j, j = (i << 1))
	{
		if (j < cnt && dis[hp[j+1].idx][hp[j+1].cap] < dis[hp[j].idx][hp[j].cap]) ++j;
		if (dis[e.idx][e.cap] > dis[hp[j].idx][hp[j].cap]) { hp[i].idx = hp[j].idx; hp[i].cap = hp[j].cap; ati[hp[i].idx][hp[i].cap] = i; } else break;
	}
	hp[i].idx = e.idx; hp[i].cap = e.cap; ati[hp[i].idx][hp[i].cap] = i;
	return ret;
}

void update(int pos)
{
	int i, j;
	node2 e = hp[pos];
	for (i = pos, j = (i >> 1); j; i = j, j = (i >> 1))
		if (dis[hp[j].idx][hp[j].cap] > dis[e.idx][e.cap]) { hp[i].idx = hp[j].idx; hp[i].cap = hp[j].cap; ati[hp[i].idx][hp[i].cap] = i; } else break;
	hp[i].idx = e.idx; hp[i].cap = e.cap; ati[hp[i].idx][hp[i].cap] = i;
}

void dijkstra()
{
	int i, j, k;
	node2 ele;
	for (i = 0; i < n; ++i) for (j = 0; j <= cap; ++j) dis[i][j] = MAX; dis[st][0] = 0;
	hp[cnt=1].idx = st; hp[1].cap = 0;
	memset(ati, 0, sizeof(ati)); ati[st][0] = 1;
	while (cnt)
	{
		ele = getele(); if (ele.idx == ed) { printf("%d\n", dis[ele.idx][ele.cap]); return; }
//		printf("[%d][%d][%d]\n", ele.idx, ele.cap, dis[ele.idx][ele.cap]);
		if (ele.cap < cap && dis[ele.idx][ele.cap+1] > dis[ele.idx][ele.cap] + unt[ele.idx])
		{
			dis[ele.idx][ele.cap+1] = dis[ele.idx][ele.cap] + unt[ele.idx];
			if (!ati[ele.idx][ele.cap+1]) { ++cnt; hp[cnt].idx = ele.idx; hp[cnt].cap = ele.cap+1; ati[ele.idx][ele.cap+1] = cnt; }
			update(ati[ele.idx][ele.cap+1]);
		}
		for (i = rd[ele.idx]; i; i = way[i].next)
		{
			j = way[i].des; k = ele.cap - way[i].len; if (k < 0) break;
			if (dis[j][k] > dis[ele.idx][ele.cap])
			{
				dis[j][k] = dis[ele.idx][ele.cap];
				if (!ati[j][k]) { ++cnt; hp[cnt].idx = j; hp[cnt].cap = k; ati[j][k] = cnt; }
				update(ati[j][k]);
			}
		}
	}
	printf("impossible\n");
}

void conduct()
{
	int req;
	scanf("%d", &req);
	while (req--)
	{
		scanf("%d %d %d", &cap, &st, &ed);
		dijkstra();
	}
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

