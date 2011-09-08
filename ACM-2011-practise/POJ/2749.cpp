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

void input()
{
	int i, id1, id2;
	scanf("%d %d %d", &n, &m1, &m2);
	scanf("%d %d %d %d", &pa.x, &pa.y, &pb.x, &pb.y);
	for (i = 1; i <= n; ++i) scanf("%d %d", &p[i].x, &p[i].y);
	for (i = 1; i <= n; ++i) { 
		cpn[2*i-1] = 2*i; cpn[2*i] = 2*i-1; 
		val[2*i-1] = getdis(p[i], pa);
		val[2*i] = getdis(p[i], pb);
	}
	memset(rd, 0, sizeof(rd));
	for (i = 1; i <= m1; ++i) {
		scanf("%d %d", &id1, &id2);
		way[i*4-3].des = 2*id1-1; way[i*4-3].next = rd[2*id2]; rd[2*id2] = i*4-3;
		way[i*4-2].des = 2*id1; way[i*4-2].next = rd[2*id2-1]; rd[2*id2-1] = i*4-2;
		way[i*4-1].des = 2*id2-1; way[i*4-1].next = rd[2*id1]; rd[2*id1] = i*4-1;
		way[i*4].des = 2*id2; way[i*4].next = rd[2*id1-1]; rd[2*id1-1] = i*4;
	}
	for (i = m1+1; i <= m1+m2; ++i) {
		scanf("%d %d", &id1, &id2);
		way[i*4-3].des = 2*id1-1; way[i*4-3].next = rd[2*id2-1]; rd[2*id2-1] = i*4-3;
		way[i*4-2].des = 2*id1; way[i*4-2].next = rd[2*id2]; rd[2*id2] = i*4-2;
		way[i*4-1].des = 2*id2-1; way[i*4-1].next = rd[2*id1-1]; rd[2*id1-1] = i*4-1;
		way[i*4].des = 2*id2; way[i*4].next = rd[2*id1]; rd[2*id1] = i*4;
	}
}

void conduct()
{
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 1; i <= 2*n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 2*n; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
	for (i = 1; i <= n; ++i) if (col[i*2-1] == col[i*2]) { printf("-1\n"); return; }


int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	input();
	conduct();
	fclose(stdin);
	fclose(stdout);
}

