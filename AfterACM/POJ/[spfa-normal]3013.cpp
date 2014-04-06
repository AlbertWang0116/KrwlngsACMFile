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

struct edge { int des, nxt; long long len; };
#define N 50010
#define M 200010
edge e[M];
int hd[N], vst[N], pre[N], que[N], val[N];
long long dis[N];
int n, m, cnt;

void insert(int i, int j, int k) {
	++cnt; e[cnt].nxt=hd[i]; e[cnt].des=j; e[cnt].len=k; hd[i]=cnt;
}

#define next(x, n) ((x)=(x)?(x)-1:(n))
void spfa(int s, int n) {
	int i, u, v, head, tail, cnt;
	memset(dis, 0x7f, sizeof(dis)); memset(pre, -1, sizeof(pre)); memset(vst, 0, sizeof(vst));
	for (head=tail=dis[u=s]=cnt=0; ~cnt--; vst[u=que[next(head, n)]]--)
		for (i=hd[u]; i; i=e[i].nxt) if (dis[v=e[i].des]>dis[u]+e[i].len) {
			dis[v]=dis[u]+e[i].len; pre[v]=u;
			if (!vst[v]) { vst[v]++; cnt++; que[next(tail, n)]=v; }
		}
}

void conduct() {
	int i, j, k, l;
	long long ans;
	scanf("%d%d", &n, &m);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=1; i<=n; ++i) scanf("%d", &val[i]);
	for (i=0; i<m; ++i) {
		scanf("%d%d%d", &j, &k, &l);
		insert(j, k, l); insert(k, j, l);
	}
	spfa(1, n); pre[1]=0;
	for (i=1; i<=n; ++i) if (!~pre[i]) { printf("No Answer\n"); return; }
	for (ans=0, i=1; i<=n; ++i) ans+=dis[i]*val[i];
	cout << ans << endl;
}

int main() {
	int time; scanf("%d", &time);
	while(time--) conduct();
	return 0;
}
