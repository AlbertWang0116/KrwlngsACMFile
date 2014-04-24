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
#define N 5100
#define M 51000
edge e[M];
int hd[N], vst[N], stk[N], d[N], h[N], hh[N];
int top, id;
int a[N];
int n, m, cnt;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

inline void tarjan_up(int x, int y) { h[y]=!vst[x]&&d[x]<d[h[y]]?x:h[y]; }
int tarjan_dfs(int x, int pa) {
	int i, j, v, p;
	j=0; vst[x]=0; d[x]=id++; stk[top++]=x; h[x]=x; p=d[x];
	for (i=hd[x]; i; i=e[i].nxt) if (e[i].des!=pa || j++)
		if (!~vst[v=e[i].des]) { p=getmin(p, tarjan_dfs(v, x)); tarjan_up(h[v], x); }
		else if (vst[v]==1) { p=getmin(p, d[v]); tarjan_up(h[v], x); }
		else tarjan_up(v, x);
	if (x!=h[x] || p!=d[x]) vst[x]=1;
	else do { top--; vst[stk[top]]=2; hh[stk[top]]=x; } while (stk[top]!=x);
	return p;
}

void tarjan(int n) {
	memset(vst, -1, sizeof(vst)); top=id=0;
	for (int i=0; i<n; ++i) if (!~vst[i]) tarjan_dfs(i, -1);
}

void conduct() {
	int i, j, k, ans;
	scanf("%d%d", &n, &m);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d", &j, &k); --j; --k;
		insert(j, k); insert(k, j);
	}
	tarjan(n);
	memset(a, 0, sizeof(a));
	for (i=0; i<n; ++i)
		for (j=hd[i]; j; j=e[j].nxt) if (hh[i]!=hh[e[j].des]) a[hh[i]]++;
	for (ans=i=0; i<n; ++i) if (i==hh[i] && a[hh[i]]==1) ans++;
	printf("%d\n", (ans+1)/2);
}

int main() {
	conduct();
	return 0;
}
