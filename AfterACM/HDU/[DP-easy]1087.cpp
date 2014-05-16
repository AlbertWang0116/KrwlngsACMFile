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
#define M 1100000
#define N 1100
edge e[M];
int f[N], que[N], pre[N], hd[N], a[N];
int n, cnt;

inline int getmax(int x, int y) { return x>y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt; pre[y]++;
}

void conduct() {
	int i, j, u, v, head, tail, ans;
	for (i=1; i<=n; ++i) scanf("%d", &a[i]);
	memset(hd, 0, sizeof(hd)); memset(f, 0x80, sizeof(f)); memset(pre, 0, sizeof(pre)); cnt=0;
	for (i=1; i<=n; ++i) insert(0, i);
	for (i=1; i<=n; ++i) for (j=i+1; j<=n; ++j) if (a[i]<a[j]) insert(i, j);
	f[0]=0; head=tail=0;
	for (i=0; i<=n; ++i) if (!pre[i]) que[tail++]=i;
	while (head<tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt) {
			pre[v=e[i].des]--;
			f[v]=getmax(f[v], f[u]+a[v]);
			if (!pre[v]) que[tail++]=v;
		}
	}
	for (ans=i=0; i<=n; ++i) ans=getmax(ans, f[i]);
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n)!=EOF && n) conduct();
	return 0;
}
