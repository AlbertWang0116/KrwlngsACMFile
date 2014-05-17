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
#define N 40
#define M 11000
int a[N][N];
int hd[M], pre[M], que[M];
long long f[M];
edge e[M];
int n, m, cnt;
char str[N];

void insert(int x, int y) {
	++cnt; e[cnt].des=y; e[cnt].nxt=hd[x]; hd[x]=cnt; ++pre[y];
}

inline int valid(int r, int c, int tr, int tc) {
	if (tr==r && tc==c) return 0;
	else if (tr>=n || tc>=n) return 0;
	else return 1;
}

void conduct() {
	int i, j, u, v, head, tail;
	for (i=0; i<n; ++i) {
		scanf("%s", str);
		for (j=0; j<n; ++j) a[i][j]=str[j]-'0';
	}
	memset(hd, 0, sizeof(hd)); memset(pre, 0, sizeof(pre)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) {
		if (valid(i, j, i+a[i][j], j)) insert(i*n+j, (i+a[i][j])*n+j);
		if (valid(i, j, i, j+a[i][j])) insert(i*n+j, i*n+j+a[i][j]);
	}
	n*=n; head=tail=0; memset(f, 0, sizeof(f)); f[0]=1LL;
	for (i=0; i<n; ++i) if (!pre[i]) que[tail++]=i;
	while (head<tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt) {
			pre[v=e[i].des]--; f[v]+=f[u]; if (!pre[v]) que[tail++]=v;
		}
	}
	cout << f[n-1] << endl;
}

int main() {
	while (scanf("%d", &n)!=EOF && ~n) conduct();
	return 0;
}
