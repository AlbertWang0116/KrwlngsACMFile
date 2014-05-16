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
#define N 11000
#define M 2100000
#define L 110
edge e[M];
int a[L][L], hd[N], pre[N], val[N], que[N];
int n, m, cnt;
const int dr[] = { 0, 0, 1, -1 };
const int dc[] = { 1, -1, 0, 0 };

inline int getmax(int x, int y) { return x>y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].des=y; e[cnt].nxt=hd[x]; hd[x]=cnt; pre[y]++;
}

int valid(int tr, int tc) {
	if (tr<0 || tr>=n) return 0;
	if (tc<0 || tc>=n) return 0;
	return 1;
}

void conduct() {
	int i, j, k, l, tr, tc, head, tail, u, ans;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) scanf("%d", &a[i][j]);
	memset(hd, 0, sizeof(hd)); cnt=0; memset(pre, 0, sizeof(pre));
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) {
		for (k=0; k<4; ++k) for (l=1; l<=m; ++l) {
			tr=i+dr[k]*l; tc=j+dc[k]*l;
			if (!valid(tr, tc)) break;
			if (a[i][j]<a[tr][tc]) insert(i*n+j, tr*n+tc);
		}
	}
	memset(val, 0x80, sizeof(val)); val[0]=a[0][0]; m=n*n;
	for (i=head=tail=0; i<m; ++i) if (!pre[i]) que[tail++]=i;
	while (head<tail) {
		u=que[head++];
//		printf("u:%d %d\n", u, val[u]);
		for (i=hd[u]; i; i=e[i].nxt) {
			pre[e[i].des]--;
			val[e[i].des]=getmax(val[e[i].des], val[u]+a[e[i].des/n][e[i].des%n]);
			if (!pre[e[i].des]) que[tail++] = e[i].des;
		}
	}
	for (ans=i=0; i<m; ++i) ans=getmax(ans, val[i]);
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && (~n || ~m)) conduct();
	return 0;
}
