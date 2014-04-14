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

struct edge { int src, des, nxt; };
#define M 21000
#define N 6100
edge e[M];
int hd[N], vst[N], stk[N], d[N], h[N], hh[N];
int id, top;
int que[N], a[N];
int n, m, cnt;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].src=x; e[cnt].des=y; e[cnt].nxt=hd[x]; hd[x]=cnt;
}

inline void tarjan_up(int x, int y) { h[y]=!vst[x]&&d[x]<d[h[y]]?x:h[y]; }
int tarjan_dfs(int x) {
	int i, p, v;
	vst[x]=0; d[x]=id++; stk[top++]=x; h[x]=x; p=d[x];
	for (i=hd[x]; i; i=e[i].nxt)
		if (!~vst[v=e[i].des]) { p=getmin(p, tarjan_dfs(v)); tarjan_up(h[v], x); }
		else if (vst[v]==1) { p=getmin(p, d[v]); tarjan_up(h[v], x); }
		else tarjan_up(v, x);
	if (x!=h[x] || p!=d[x]) vst[x]=1;
	else do { top--; vst[stk[top]]=2; hh[stk[top]]=x; } while (stk[top]!=x);
	return p;
}

void tarjan(int n) {
	memset(vst, -1, sizeof(vst)); top=id=0;
	for (int i=0; i<n; ++i) if (!~vst[i]) tarjan_dfs(i);
}

void conduct() {
	int i, j, k;
	scanf("%d%d", &n, &m);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d", &j, &k);
		insert(j-1, k-1);
	}
	tarjan(n);
	memset(hd, 0, sizeof(hd)); memset(a, 0, sizeof(a)); m=cnt;
	for (i=1; i<=m; ++i) if (hh[e[i].src]!=hh[e[i].des]) {
		insert(hh[e[i].src], hh[e[i].des]); a[hh[e[i].des]]++;
	}
	for (i=j=0; i<n; ++i) if (hh[i]==i && !a[i]) que[j++]=i;
	if (j>1) { printf("No\n"); return; }
	while (j) {
		k=que[j--];
		for (i=hd[k]; i; i=e[i].nxt) {
			a[e[i].des]--;
			if (!a[e[i].des]) que[j++]=e[i].des;
		}
		if (j>1) { printf("No\n"); return; }
	}
	printf("Yes\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
