#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<map>
using namespace std;

struct edge { int des, nxt; };
#define N 11000
edge e[N];
int hd[N], f[N][2], a[N], pre[N];
int n, cnt;

inline int getmax(int x, int y) { return x>y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

void dp(int x) {
	int i;
	f[x][0]=f[x][1]=0; f[x][1]+=a[x];
	for (i=hd[x]; i; i=e[i].nxt) {
		dp(e[i].des);
		f[x][0]+=getmax(f[e[i].des][0], f[e[i].des][1]);
		f[x][1]+=f[e[i].des][0];
	}
}

void conduct() {
	int i, j, k, ans;
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	memset(pre, 0, sizeof(pre));
	memset(hd, 0, sizeof(hd)); cnt=0;
	while (scanf("%d%d", &j, &k)!=EOF && (j||k)) {
		--j; --k;
		insert(k, j); pre[j]++;
	}
	for (ans=i=0; i<n; ++i) if (!pre[i]) {
		dp(i);
		ans+=getmax(f[i][0], f[i][1]);
	}
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
