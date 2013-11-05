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
int a[N], val[N], sa[N], rk[N], pos[N], tsa[N], ht[N];
int n;

int cmp(const int &i, const int &j) { return val[i]<val[j]; }
int neq(int i, int j, int l) { return rk[i]-rk[j] || rk[i+l]-rk[j+l]; }
int getmax(int x, int y) { return x>y?x:y; }
int getmin(int x, int y) { return x<y?x:y; }

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

int judge(int len) {
	int i, j, mst, lst;
	for (i=1; i<n; ++i) {
		if (ht[i]<len-1) continue;
		mst=getmax(sa[i-1], sa[i]); lst=getmin(sa[i-1], sa[i]);
		for (j=i+1; j<n && ht[j]>=len-1; ++j) {
			mst=getmax(mst, sa[j]); lst=getmin(lst, sa[j]);
		}
		if (mst-lst>=len) return 1; i=j-1;
	}
	return 0;
}

void conduct() {
	int i, lst, mst, mid;
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	if (n==1) { printf("0\n"); return; }
	for (i=0; i<n-1; ++i) val[i]=a[i+1]-a[i]+100; val[n-1]=-1; 
	sufixarray(val, n); lcpinit(val, sa, rk, n);
	lst=0; mst=n;
	while (lst<mst) {
		mid=(lst+mst)/2+1;
		if (judge(mid)) lst=mid; else mst=mid-1;
	}
	if (lst>=5) printf("%d\n", lst); else printf("0\n");
}

int main() {
	while (scanf("%d", &n)!=EOF && n) {
		conduct();
	}
	return 0;
}
