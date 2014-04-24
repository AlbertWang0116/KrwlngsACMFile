#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
#include<climits>
using namespace std;

struct edge { int des, nxt; };
#define N 110000
#define M 1100000
edge e[M];
int hd[N], f[N], val[N], que[N], pre[N];
int n, m, cnt;

inline int getmax(int x, int y) { return x>y?x:y; }

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

void conduct() {
	int i, j, k, tail, ans;
	for (i=0; i<n; ++i) scanf("%d", &val[i]);
	memset(hd, 0, sizeof(hd)); cnt=0;
	memset(pre, 0, sizeof(pre));
	for (i=0; i<m; ++i) {
		scanf("%d%d", &j, &k); --j; --k;
		insert(j, k); pre[k]++;
	}
	tail=0;
	for (i=0; i<n; ++i)
		if (pre[i]) f[i]=LONG_MIN;
		else { f[i]=val[i]; que[tail++]=i; }
	for (i=0; i<n; ++i) {
		j=que[i];
		for (k=hd[j]; k; k=e[k].nxt) {
			f[e[k].des]=getmax(f[e[k].des], f[j]+val[e[k].des]);
			--pre[e[k].des]; if (!pre[e[k].des]) que[tail++]=e[k].des;
		}
	}
	for (ans=LONG_MIN, i=0; i<n; ++i) if (!hd[i]) ans=getmax(ans, f[i]);
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF) conduct();
	return 0;
}
