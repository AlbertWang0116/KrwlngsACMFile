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
#define N 110
#define M 11000
edge e[M];
int a[N], f[N], hd[N], pre[N], que[N], ff[N];
int n, m, cnt;

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt; pre[y]++;
}

void print(int x) {
	if (~x) print(ff[x]);
	else return;
	if (x!=n) printf("%d->", x+1);
	else printf("%d", 1);
}

void conduct() {
	int i, j, k, u, v, head, tail;
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%d", &a[i]); a[n]=0;
	memset(hd, 0, sizeof(hd)); memset(pre, 0, sizeof(pre)); cnt=0;
	scanf("%d", &m);
	for (i=0; i<m; ++i) {
		scanf("%d%d", &j, &k); --j; --k;
		if (j>k) insert(k, j); 
		else if (j<k) insert(j, k);
	}
	memset(f, 0x80, sizeof(f)); head=tail=0; f[0]=0; ff[0]=-1;
	for (i=0; i<=n; ++i) if (!pre[i]) que[tail++]=i;
	while (head<tail) {
		u=que[head++];
		for (i=hd[u]; i; i=e[i].nxt) {
			pre[v=e[i].des]--; 
			if (f[v]<f[u]+a[v]) { f[v]=f[u]+a[v]; ff[v]=u; }
			if (!pre[v]) que[tail++]=v;
		}
	}
	printf("points : %d\ncircuit : ", f[n]);
	print(n);
	printf("\n");
}

int main() {
	int time; scanf("%d", &time);
	for (int i=1; i<=time; ++i) {
		printf("CASE %d#\n", i);
		conduct();
		if (i<time) printf("\n");
	}
	return 0;
}
