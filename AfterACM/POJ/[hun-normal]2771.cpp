#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

struct edge { int nxt, des; };
struct pupil { int tall, sport, music; };
#define N 510
#define M 110000
#define L 110
edge e[M];
int hd[N], pre[N], vst[N];
pupil x[N], y[N];
char music[N][L], sport[N][L];
int n, m, cnt;

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

int hun_dfs(int x, int i=0, int u=0) {
	for (vst[x]=0, i=hd[x]; i; i=e[i].nxt)
		if (!~(u=pre[e[i].des])||(vst[u]&&hun_dfs(u))) break;
	if (i) pre[e[i].des]=x; return i;
}

int hungarian(int x, int i=0, int ret=0) {
	memset(pre, -1, sizeof(pre));
	for (i=0; i<n; ++i) { memset(vst, -1, sizeof(vst)); hun_dfs(i)?++ret:0; }
	return ret;
}

void conduct() {
	int i, j, tmp, cs, cm, *id;
	char str[256];
	pupil *p;
	scanf("%d", &tmp); n=m=cs=cm=0;
	while (tmp--) {
		scanf("%d%s", &i, str);
		if (!strcmp(str, "M")) { id=&n; p=x; }
		else { id=&m; p=y; }
		p[*id].tall = i;
		scanf("%s", str);
		for (i=0; i<cm; ++i) if (!strcmp(str, music[i])) break;
		if (i==cm) strcpy(music[cm++], str); p[*id].music=i;
		scanf("%s", str);
		for (i=0; i<cs; ++i) if (!strcmp(str, sport[i])) break;
		if (i==cs) strcpy(sport[cs++], str); p[*id].sport=i;
		(*id)++;
	}
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<m; ++j)
		if (abs(x[i].tall-y[j].tall)<=40 && x[i].music==y[j].music && x[i].sport!=y[j].sport) insert(i, j);
	printf("%d\n", n+m-hungarian(n));
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
