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
#define N 110000
#define M 1100000
edge e[M];
int hd[N], stk[N], vst[N], d[N], h[N], hh[N];
int top, id;
int up[N];
int n, m, cnt, ans;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

inline void tarjan_up(int x, int y) { h[y]=!vst[x]&&d[x]<d[h[y]]?x:h[y]; }
int tarjan_dfs(int x, int pa) {
	int i, j, v, p;
	j=0; vst[x]=0; d[x]=id++; stk[top++]=x; h[x]=x; p=d[x]; up[x]=pa;
	for (i=hd[x]; i; i=e[i].nxt) if (e[i].des!=pa || j++)
		if (!~vst[v=e[i].des]) { p=getmin(p, tarjan_dfs(v, x)); tarjan_up(h[v], x); }
		else if (vst[v]==1) { p=getmin(p, d[v]); tarjan_up(h[v], x); }
		else tarjan_up(v, x);
	if (x!=h[x] || p!=d[x]) vst[x]=1;
	else do { --top; vst[stk[top]]=2; hh[stk[top]]=x; } while (stk[top]!=x);
	return p;
}

void tarjan(int n) {
	memset(vst, -1, sizeof(vst)); top=id=0;
	for (int i=0; i<n; ++i) if (!~vst[i]) tarjan_dfs(i, -1);
}

int get_root(int x) { if (hh[x]!=x) return hh[x]=get_root(hh[x]); else return x; }
int merge(int i, int j) {
	int k;
	if (d[i]==d[j]) return hh[i]=hh[j]=get_root(i);
	if (d[i]<d[j]) { k=i; i=j; j=k; }
	if (get_root(i)!=i) hh[i]=hh[j]=merge(hh[i], j);
	else { hh[i]=hh[j]=merge(up[i], j); ans--; }
	return hh[i];
}

void conduct() {
	int i, j, k;
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d", &j, &k); --j; --k;
		insert(j, k); insert(k, j);
	}
	tarjan(n);
	for (ans=0, i=1; i<n; ++i) if (hh[i]==i) ans++;
	scanf("%d", &k);
	while (k--) {
		scanf("%d%d", &i, &j); --i; --j;
		merge(i, j);
		printf("%d\n", ans);
	}
	printf("\n");
}

int main() {
	int time=0;
	while (scanf("%d%d", &n, &m)!=EOF && (n||m)) {
		printf("Case %d:\n", ++time);
		conduct();
	}
	return 0;
}
