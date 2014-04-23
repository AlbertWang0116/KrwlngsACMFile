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

#define N 1100
int e[N][N];
int s[N], a[N], b[N], que[N], h[N], stk[N], d[N], vst[N], root[N];
int n, m, cnt, id, top;

inline void tarjan_up(int x, int y) { h[y]=d[x]<d[h[y]]?x:h[y]; }
void tarjan_dfs(int x, int pa) {
	vst[x]=0; d[x]=id++; stk[top++]=x; h[x]=x;
	for (int i=0; i<n; ++i) if (e[x][i]) 
		if (!~vst[i]) { tarjan_dfs(i, x); tarjan_up(h[i], x); }
		else tarjan_up(i, x);
	if (h[x]!=pa) return;
	do { top--; s[stk[top]]=cnt; } while (stk[top]!=x); root[cnt++]=pa;
}

void tarjan(int n) {
	memset(vst, -1, sizeof(vst)); top=id=0;
	for (int i=0; i<n; ++i) if (!~vst[i]) tarjan_dfs(i, i);
}

int bfs(int id, int x) {
	int i, u, head, tail;
	b[x]=0; tail=head=0; que[0]=x;
	while (head<=tail) {
		u=que[head++];
		for (i=0; i<n; ++i) if (s[i]==id && e[u][i])
			if (!vst[i]) { b[i]=b[u]+1; vst[i]=1; que[++tail]=i; }
			else if (b[i]==b[u]) { return 1; }
	}
	return 0;
}

void conduct() {
	int i, j, k, ans;
	memset(e, -1, sizeof(e));
	for (i=0; i<n; ++i) e[i][i]=0;
	for (i=0; i<m; ++i) {
		scanf("%d%d", &j, &k); --j; --k;
		e[j][k]=e[k][j]=0;
	}
	cnt=0;
	tarjan(n);
	memset(vst, 0, sizeof(vst));
	for (i=0; i<cnt; ++i) if (bfs(i, root[i])) {   a[i]=1; } else { a[i]=0; }
	for (i=0; i<n; ++i) if (a[s[i]]) b[i]=1; else b[i]=0;
	for (i=0; i<cnt; ++i) if (a[i]) b[root[i]]=1;
	for (ans=i=0; i<n; ++i) if (!b[i]) ans++;
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && (n||m)) conduct();
	return 0;
}
