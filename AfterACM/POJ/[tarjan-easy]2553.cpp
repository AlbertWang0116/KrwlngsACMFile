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
#define N 5100
#define M 5100000
edge e[M];
int hd[N], vst[N], stk[N], d[N], h[N], hh[N];
int id, top;
int a[N];
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
	if (h[x]!=x || p!=d[x]) vst[x]=1;
	else do { top--; vst[stk[top]]=2; hh[stk[top]]=x; } while (stk[top]!=x);
	return p;
}

void tarjan(int n) {
	memset(vst, -1, sizeof(vst)); id=top=0;
	for (int i=0; i<n; ++i) if (!~vst[i]) tarjan_dfs(i);
}

void conduct() {
	int i, j, k;
	scanf("%d", &m);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d", &j, &k);
		insert(j-1, k-1);
	}
	tarjan(n);
	memset(a, 0, sizeof(a));
	for (i=1; i<=cnt; ++i) if (hh[e[i].src]!=hh[e[i].des]) a[hh[e[i].src]]++;
	for (i=0; i<n; ++i) if (!a[hh[i]]) printf("%d ", i+1);
	printf("\n");
}

int main() {
	while (scanf("%d", &n)!=EOF && n) conduct();
	return 0;
}
