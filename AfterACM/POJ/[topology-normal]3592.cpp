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

struct edge { int des, nxt; };
#define N 2100
#define M 51000
#define L 50
edge e[M];
int hd[N], stk[N], vst[N], d[N], h[N], hh[N];
int top, id;
char g[L][L];
int que[N], a[N], val[N], pre[N], th[N];
int n, m, cnt, R, C;

inline int getmax(int x, int y) { return x>y?x:y; }
inline int getmin(int x, int y) { return x<y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

inline void tarjan_up(int x, int y) { h[y]=!vst[x]&&d[x]<d[h[y]]?x:h[y]; }
int tarjan_dfs(int x, int pa) {
	int i, j, v, p;
	vst[x]=0; stk[top++]=x; d[x]=id++; h[x]=x; p=d[x];
	for (i=hd[x]; i; i=e[i].nxt)
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

int topology() {
	int i, j, k, tail;
	memset(a, 0x80, sizeof(a)); a[hh[0]]=val[hh[0]]; tail=0;
	for (i=0; i<n; ++i) if (hh[i]==i && !pre[i]) que[tail++]=i;
	for (i=0; i<tail; ++i) {
		j=que[i];
		for (k=hd[j]; k; k=e[k].nxt) {
			a[e[k].des]=getmax(a[e[k].des], a[j]+val[e[k].des]);
			pre[e[k].des]--;
			if (!pre[e[k].des]) que[tail++]=e[k].des;
		}
	}
	for (i=j=0; i<n; ++i) if (hh[i]==i) j=getmax(j, a[i]);
	return j;
}

void conduct() {
	int i, j, k, tr, tc;
	scanf("%d%d", &R, &C);
	for (i=0; i<R; ++i) scanf("%s", g[i]);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=1; i<R; ++i) for (j=0; j<C; ++j) if (g[i][j]!='#' && g[i-1][j]!='#') insert((i-1)*C+j, i*C+j);
	for (i=0; i<R; ++i) for (j=1; j<C; ++j) if (g[i][j]!='#' && g[i][j-1]!='#') insert(i*C+j-1, i*C+j);
	for (i=0; i<R; ++i) for (j=0; j<C; ++j)
		if (g[i][j]!='*' && g[i][j]!='#') val[i*C+j]=g[i][j]-'0';
		else if (g[i][j]=='#') val[i*C+j]=0;
		else {
			val[i*C+j]=0;
			scanf("%d%d", &tr, &tc);
			insert(i*C+j, tr*C+tc);
		}
	n=R*C;
	tarjan(n);
	memset(pre, 0, sizeof(pre)); memcpy(th, hd, sizeof(th)); memset(hd, 0, sizeof(hd));
	for (i=0; i<n; ++i)
		for (j=th[i]; j; j=e[j].nxt) if (hh[i]!=hh[e[j].des]) { insert(hh[i], hh[e[j].des]); ++pre[hh[e[j].des]]; }
	for (i=0; i<n; ++i) if (hh[i]!=i) val[hh[i]]+=val[i];
	printf("%d\n", topology());
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
