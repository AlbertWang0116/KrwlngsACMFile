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

struct edge { int des, len, nxt; };
#define M 110000
#define N 11000
#define L 60
int a[L][L], pre[N], que[N], vst[N], dis[N], hd[N];
long long f[N];
edge e[M];
int n, m, cnt;
const int dr[] = { 0, 0, 1, -1 };
const int dc[] = { 1, -1, 0, 0 };

void insert(int x, int y, int z) {
	++cnt; e[cnt].des=y; e[cnt].len=z; e[cnt].nxt=hd[x]; hd[x]=cnt; ++pre[y];
}

int valid(int r, int c) {
	if (r<0 || r>=n) return 0;
	if (c<0 || c>=n) return 0;
	return 1;
}

#define next(x, n) ((x)=(x)?(x)-1:(n))
void spfa(int x, int n) {
	int i, u, v, head, tail, cnt;
	memset(dis, 0x7f, sizeof(dis)); memset(vst, 0, sizeof(vst));
	for (head=tail=dis[u=x]=cnt=0; ~cnt--; vst[u=que[next(head, n)]]--)
		for (i=hd[u]; i; i=e[i].nxt) if (dis[v=e[i].des]>dis[u]+e[i].len) {
			dis[v]=dis[u]+e[i].len;
			if (!vst[v]) { vst[v]++; cnt++; que[next(tail, n)]=v; }
		}
}

void conduct() {
	int i, j, k, tr, tc, head, tail, u, v;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) scanf("%d", &a[i][j]);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) 
		for (k=0; k<4; ++k) {
			tr=i+dr[k]; tc=j+dc[k];
			if (!valid(tr, tc)) continue;
			insert(tr*n+tc, i*n+j, a[i][j]);
		}
	insert(n*n, n*n-1, a[n-1][n-1]);
	spfa(n*n, n*n);
//	for (i=0; i<n; ++i) {
//		for (j=0; j<n; ++j) printf("%d ", dis[i*n+j]);
//		printf("\n");
//	}
	memset(hd, 0, sizeof(hd)); memset(pre, 0, sizeof(pre)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j)
		for (k=0; k<4; ++k) {
			tr=i+dr[k]; tc=j+dc[k];
			if (!valid(tr, tc)) continue;
			if (dis[i*n+j]>dis[tr*n+tc]) insert(i*n+j, tr*n+tc, 0);
		}
	insert(n*n-1, n*n, 0);
	memset(f, 0, sizeof(f)); f[0]=1;
	for (head=tail=i=0; i<=n*n; ++i) if (!pre[i]) que[tail++]=i;
	while (head<tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt) {
			pre[v=e[i].des]--;
			f[v]+=f[u];
			if (!pre[v]) que[tail++]=v;
		}
	}
	cout << f[n*n] << endl;
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
