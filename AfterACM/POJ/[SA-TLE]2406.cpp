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

#define N 1000010
int val[N], sa[N], rk[N], tsa[N], pos[N], ht[N];
char str[N];
int n;

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

void lcpinit(int *val, int *sa, int *rk, int n) {
	int i, j, k;
	for (i=k=0; i<n; ht[rk[i++]]=k, k?k--:0) if (rk[i])
		for (j=sa[rk[i]-1]; val[i+k]==val[j+k]; ++k);
}

void conduct() {
	int i;
	n=strlen(str);
	for (i=0; i<n; ++i) val[i]=str[i]; val[n++]=-1;
	sufixarray(val, n); lcpinit(val, sa, rk, n);
	if (ht[rk[0]] && !((n-1)%(n-1-ht[rk[0]]))) printf("%d\n", (n-1)/(n-1-ht[rk[0]]));
	else printf("1\n");
}

int main() {
	while (scanf("%s", str)!= EOF && strcmp(str, ".")) conduct();
	return 0;
}
