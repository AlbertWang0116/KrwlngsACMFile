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
#define N 200
#define M 21000
edge e[M];
int hd[N], vst[N], stk[N], d[N], h[N], hh[N];
int a[N], b[N];
int n, m, cnt, top, id;

inline int getmin(int x, int y) { return x<y?x:y; }
inline int getmax(int x, int y) { return x>y?x:y; }

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
	else do { --top; vst[stk[top]]=2; hh[stk[top]]=x; } while (stk[top]!=x);
	return p;
}

void tarjan(int n) {
	memset(vst, -1, sizeof(vst)); top=0; id=0;
	for (int i=0; i<n; ++i) if (!~vst[i]) tarjan_dfs(i);
}

void conduct() {
	int i, j, k, l;
	scanf("%d", &n);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) {
		while (scanf("%d", &j) && j) insert(i, j-1);
	}
	tarjan(n);
	memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
	for (i=1; i<=cnt; ++i) if (hh[e[i].src]!=hh[e[i].des]) { a[hh[e[i].src]]++; b[hh[e[i].des]]++; }
	for (i=j=k=l=0; i<n; ++i) if (hh[i]==i) { 
		if (!a[i]) j++; if (!b[i]) k++; l++;
	}
	printf("%d\n", k);
	if (l==1) printf("0\n");
	else printf("%d\n", getmax(j, k));
}

int main() {
	conduct();
	return 0;
}
