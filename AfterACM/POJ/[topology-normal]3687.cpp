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
#define N 210
#define M 51000
edge e[M];
int hd[N], stk[N], vst[N], d[N], h[N], hh[N];
int top, id;
int a[N], que[N], pre[N];
int n, m, cnt;

inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

inline void tarjan_up(int x, int y) { h[y]=!vst[x]&&d[x]<d[h[y]]?x:h[y]; }
int tarjan_dfs(int x, int pa) {
	int i, j, v, p;
	j=1; vst[x]=0; d[x]=id++; stk[top++]=x; h[x]=x; p=d[x];
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

void topology() {
	int i, j, k, l, tail;
	memset(vst, 0, sizeof(vst)); tail=0;
	for (i=0; i<n; ++i) if (!pre[i]) que[tail++]=i;
	for (i=0; i<n; ++i) {
		for (j=0, k=-1; j<tail; ++j) if (!vst[j] && que[j]>k) { k=que[j]; l=j; }
		vst[l]=1; a[k]=n-i;
		for (j=hd[k]; j; j=e[j].nxt) {
			pre[e[j].des]--;
			if (!pre[e[j].des]) que[tail++]=e[j].des;
		}
	}
}

void conduct() {
	int i, j, k, l;
	scanf("%d%d", &n, &m);
	memset(hd, 0, sizeof(hd)); memset(pre, 0, sizeof(pre)); cnt=0;
	for (i=l=0; i<m; ++i) {
		scanf("%d%d", &j, &k); --j; --k;
		insert(k, j); pre[j]++;
		if (k==j) l=1;
	}
	if (l) { printf("-1\n"); return; }
	tarjan(n);
	for (i=0; i<n; ++i) if (hh[i]!=i) { printf("-1\n"); return; }
	topology();
	for (i=0; i<n; ++i) printf("%d ", a[i]); printf("\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
