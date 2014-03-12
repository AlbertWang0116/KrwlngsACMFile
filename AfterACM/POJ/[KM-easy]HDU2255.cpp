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

#define N 310
int w[N][N], pre[N], vst[N], que[N];
int tx[N], ty[N], lst[N];
int n, head, tail;
const int inf = 1000000000;

inline int getmin(int x, int y) { return x<y?x:y; }
inline int getmax(int x, int y) { return x>y?x:y; }

inline void km_update(int i, int j, int &k, int w) { lst[j]=w; vst[j]=i; if (!w) { que[++tail]=j; k=!~pre[j]?j:k; } }
int km(int n, int m) {
	int i, j, k, u, v;
	int ret;
	memset(pre, -1, sizeof(pre)); memset(ty, 0, sizeof(ty));
	for (i=0; i<n; ++i) for (tx[i]=w[i][0], j=1; j<m; ++j) tx[i]=getmax(tx[i], w[i][j]);
	for (i=0; i<n; ++i) {
		memset(vst, -1, sizeof(vst)); head=0; tail=k=-1;
		for (j=0; j<m; ++j) km_update(-1, j, k, tx[i]+ty[j]-w[i][j]);
		while (!~k) {
			while (head<=tail && !~k) {
				v=que[head++]; u=pre[v]; 
				for (j=0; j<m; ++j) if (tx[u]+ty[j]-w[u][j]<lst[j]) km_update(v, j, k, tx[u]+ty[j]-w[u][j]);
			} if (~k) break;
			for (ret=inf, j=0; j<m; ++j) if(lst[j]) ret=getmin(ret, lst[j]);
			for (j=0; j<=tail; ++j) { ty[que[j]]+=ret; tx[pre[que[j]]]-=ret; } tx[i]-=ret;
			for (j=0; j<m; ++j) if (lst[j]) km_update(vst[j], j, k, lst[j]-ret);
		}
		while (~vst[k]) { pre[k]=pre[vst[k]]; k=vst[k]; } pre[k]=i;
	}
	for (ret=i=0; i<n; ++i) ret+=tx[i]; for (j=0; j<m; ++j) ret+=ty[j]; return ret;
}

void conduct() {
	int i, j;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) scanf("%d", &w[i][j]);
	printf("%d\n", km(n, n));
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
