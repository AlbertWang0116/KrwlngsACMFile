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

#define N 500010
int val[N], sa[N], rk[N], tsa[N], pos[N], tag[N];
int n;

int getmin(int x, int y) { return x<y?x:y; }
int cmp(const int &i, const int &j) { return val[i]<val[j]; }
int neq(int i, int j, int l) { return rk[i]-rk[j] || rk[i+l]-rk[j+l]; }

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

void print(int x, int y) {
	for (int i=x; i<=y; ++i) printf("%d\n", val[i]);
}

void conduct() {
	int i, j, k; 
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%d", &val[i]);
	for (i=0; i<n/2; ++i) { j=val[i]; val[i]=val[n-i-1]; val[n-i-1]=j; }
	for (j=val[0], i=1; i<n; ++i) j=getmin(j, val[i]); val[n++] = j-1;
	sufixarray(val, n);
	for (i=1; i<n; ++i) if (sa[i]>1) { k=sa[i]; print(k, n-2); break; }
	for (i=0; i<k; ++i) val[i+k]=val[i]; n=k*2; val[n++]=j-1;
	sufixarray(val, n);
	for (i=0; i<n; ++i) if (sa[i]<k && sa[i]>0) { j=sa[i]; break; }
	print(j, j+k-1);
}

int main() {
	conduct();
	return 0;
}
