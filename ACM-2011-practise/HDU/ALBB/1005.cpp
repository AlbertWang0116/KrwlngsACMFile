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

#define col(x, y) (y)*2+(x)%2
struct node { int des, len, next; };
struct info { int rnd, e; };
#define N 10010
#define M 60010
#define L 210
int gd[L][L], cl[L][L], seq[N], rd[N];
bool zoc[L][L], vst[N];
node way[M];
info dis[N];
int c, rc, n, m, tot, r1, c1, r2, c2;
const int MAX = LONG_MAX;
const int dr[6] = {-1, 0, 1, 1, 0, -1};
const int dc[6] = {1, 2, 1, -1, -2, -1};
const int bd[6] = {16, 32, 64, 128, 256, 512};

void input()
{
	int i, j;
	scanf("%d%d%d", &n, &m, &tot); tot *= 4;
	memset(gd, 0, sizeof(gd));
	for (i = 0; i < n; ++i) for (j = 0; j < m; ++j) scanf("%d", &gd[i][col(i, j)]);
	scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
}

int findway(int st, int ed)
{
	int i, cnt, u, v, rnd, e, head, tail;
	memset(vst, 0, sizeof(vst)); cnt = 1;
	for (i = 1; i <= c; ++i) dis[i].rnd = MAX; dis[st].rnd = 0; dis[st].e = 0;
	for (seq[head = tail = 0] = st; cnt; cnt--, head = (head+1)%N) {
		u = seq[head]; vst[u] = false;
		for (i = rd[u]; i; i = way[i].next) {
			v = way[i].des; if (!dis[u].e) { rnd = dis[u].rnd+1; e = tot; }
			else { rnd = dis[u].rnd; e = dis[u].e; }
			e -= way[i].len; if (!way[i].len || e < 0) e = 0;
			if (dis[v].rnd > rnd || (dis[v].rnd == rnd && dis[v].e < e)) {
				if (!vst[v]) { vst[v] = true; seq[tail = (tail+1) % N] = v; ++cnt; }
				dis[v].rnd = rnd; dis[v].e = e;
			}
		}
	}
	if (dis[ed].rnd < MAX) return dis[ed].rnd; else return -1;
}

void conduct()
{
	int i, j, k;
	memset(zoc, false, sizeof(zoc));
	for (i = 0; i < n; ++i) for (j = 0; j < m; ++j) 
		if (gd[i][col(i, j)] & 8) for (k = 0; k < 6; ++k) {
			if (i+dr[k] < 0 || i+dr[k] >= n) continue;
			if (col(i, j)+dc[k] < 0 || col(i, j)+dc[k] >= 2*m) continue;	
			zoc[i+dr[k]][col(i, j)+dc[k]] = true;
		}
	for (c = i = 0; i < n; ++i) for (j = 0; j < m; ++j) cl[i][col(i, j)] = ++c;
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 0; i < n; ++i) for (j = 0; j < m; ++j) {
		if (gd[i][col(i, j)] & 8) continue;
		for (k = 0; k < 6; ++k) {
			if (gd[i+dr[k]][col(i, j)+dc[k]] & 8) continue;
			if (i+dr[k] < 0 || i+dr[k] >= n) continue;
			if (col(i, j)+dc[k] < 0 || col(i, j)+dc[k] >= 2*m) continue;	
			++rc; way[rc].des = cl[i+dr[k]][col(i, j)+dc[k]]; 
			way[rc].next = rd[cl[i][col(i, j)]]; rd[cl[i][col(i, j)]] = rc;
			if (zoc[i][col(i, j)] && zoc[i+dr[k]][col(i, j)+dc[k]]) { way[rc].len = 0; continue; }
			if ((gd[i][col(i, j)] & 4) && (gd[i+dr[k]][col(i, j)+dc[k]] & 4)) { way[rc].len = 1; continue; }
			if ((gd[i][col(i, j)] & bd[k]) || (gd[i+dr[k]][col(i, j)+dc[k]] & bd[(k+3)%6])) { way[rc].len = 0; continue; }
			if (gd[i+dr[k]][col(i, j)+dc[k]] & 2) way[rc].len = 8; else way[rc].len = 4;
		}
	}
//	for (i = 1; i <= c; ++i) {
//		printf("---%d---\n", i);
//		for (j = rd[i]; j; j = way[j].next) printf("des:%d len:%d\n", way[j].des, way[j].len);
//	}
	printf("%d\n", findway(cl[r1][col(r1, c1)], cl[r2][col(r2, c2)]));
}

int main()
{
	int time;
	scanf("%d", &time);
	for (int i = 1; i <= time; ++i) {
		printf("Case %d: ", i);
		input(); conduct();
	}
}

