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
int val[N], sa[N], rk[N], tsa[N], pos[N];
char str[100];
int n, m;

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

void conduct() {
	int i, j, k;
	scanf("%d", &n);
	for (i=0; i<n; ++i) { 
		scanf("%s", str);
		sscanf(str, "%c", &val[i]);
	}
	val[n]=-1; m=n+1;
	for (i=0; i<n; ++i) val[m+i]=val[n-1-i]; val[m+n]=-2; m+=n+1;
	sufixarray(val, m); j=0; k=n+1;
	for (i=0; i<n; ++i) {
		if (rk[j]<rk[k]) { printf("%c", val[j]); j++; }
		else { printf("%c", val[k]); k++; }
		if ((i+1)%80==0) printf("\n");
	}
}

int main() {
	conduct();
	return 0;
}
