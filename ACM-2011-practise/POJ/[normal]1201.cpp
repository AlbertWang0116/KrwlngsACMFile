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

struct node { int des, next, len; };
#define N 50010
#define M 200010
int seq[N], rd[N], dis[N];
bool vst[N];
node way[M];
int n, rc, m;

void input()
{
	int i, st, ed, len;
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 0; i < N; ++i) {
		if (i > 0) { rc++; way[rc].des = i-1; way[rc].len = -1; way[rc].next = rd[i]; rd[i] = rc; }
		if (i < N-1) { rc++; way[rc].des = i+1; way[rc].len = 0; way[rc].next = rd[i]; rd[i] = rc; }
	}
	scanf("%d", &m);
	for (i = 0; i < m; ++i) {
		scanf("%d%d%d", &st, &ed, &len);
		rc++; way[rc].des = ed+1; way[rc].len = len; way[rc].next = rd[st]; rd[st] = rc; 
	}
}

void conduct()
{
	int i, cnt, head, tail;
	memset(dis, 0x80, sizeof(dis)); memset(vst, 0, sizeof(vst)); cnt = 1; dis[0] = 0;
	for (seq[head = tail = 0] = 0; cnt; cnt--, head = (head+1) % N) {
		vst[seq[head]] = 0;
//		printf("%d len:%d\n", seq[head], dis[seq[head]]);
		for (i = rd[seq[head]]; i; i = way[i].next) 
			if (dis[way[i].des] < dis[seq[head]] + way[i].len) {
				if (!vst[way[i].des]) { vst[way[i].des] = true; ++cnt; seq[tail = (tail+1)%N] = way[i].des; }
				dis[way[i].des] = dis[seq[head]] + way[i].len;
			}
	}
	printf("%d\n", dis[N-1]);
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

