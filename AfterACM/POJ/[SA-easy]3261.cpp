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

#define N 100010
#define bit(x) (1<<(x))
int val[N], sa[N], rk[N], pos[N], tsa[N], ht[N], rmq[N][20], sb[N];
int n, m;

int cmp(const int &i, const int &j) { return val[i]<val[j]; }
int neq(int i, int j, int l) { return rk[i]-rk[j] || rk[i+l]-rk[j+l]; }
int getmin(int x, int y) { return x < y ? x : y; }
int getmax(int x, int y) { return x > y ? x : y; }

void sufixarray(int *val, int n) {
	int i, j, k, l;
	for (i=0; i<n; ++i) sa[i]=i; sort(sa, sa+n, cmp);
	for (i=k=pos[0]=0; i<n; ++i) { if (i&&val[sa[i]]-val[sa[i-1]]) k++; rk[sa[i]]=k; pos[k+1]=i+1; }
	for (l=1; n-k-1; l<<=1) {
		for (i=0; i<n; ++i) tsa[pos[rk[j=(sa[i]-l+n)%n]]++] = j;
		for (i=k=pos[0]=0; i<n; ++i) { if (i&&neq(tsa[i], tsa[i-1], l)) k++; sa[tsa[i]]=k; pos[k+1]=i+1; }
		memcpy(rk, sa, n*sizeof(int)); memcpy(sa, tsa, n*sizeof(int));
	}
}

void lcpinit(int *val, int *sa, int *rk, int n) {
	int i, j, k;
	for (i=k=0; i<n; ht[rk[i++]]=k, k?k--:0) if (rk[i]) 
		for (j=sa[rk[i]-1]; val[i+k]==val[j+k]; ++k);
}

void rmqinit(int *val, int n) {
	int i, j, k;
	for (i=k=0; i<n; ++i) { if (bit(k+1)==i) k++; sb[i]=k; }
	for (i=0; i<n; ++i) rmq[i][0]=val[i];
	for (j=1; j<=k; ++j) for (i=0; i<n-bit(j); ++i) rmq[i][j]=getmin(rmq[i][j-1], rmq[i+bit(j-1)][j-1]);
}

int rmquery(int x, int y) { return getmin(rmq[x][sb[y-x]], rmq[y-bit(sb[y-x])+1][sb[y-x]]); }

void conduct() {
	int i, ans;
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) scanf("%d", &val[i]); val[n++]=-1;
	sufixarray(val, n); lcpinit(val, sa, rk, n); rmqinit(ht, n);
	for (ans=i=0; i<n-m+2; ++i) ans=getmax(ans, rmquery(i, i+m-2));
	printf("%d\n", ans);
}

int main() {
	conduct();
	return 0;
}
