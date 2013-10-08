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

#define N 1000010
int val[N], sa[N], rk[N], tsa[N], pos[N], ht[N];
char str[N];
int n, m;

int cmp(const int &i, const int &j) { return val[i]<val[j]; }
inline int eq(const int &i, const int &j, const int &l) { return rk[i]==rk[j] && rk[i+l]==rk[j+l]; }
void sufixarray(int *val, int n) {
	int i, j, k, l;
	for (i=0; i<n; ++i) sa[i]=i; sort(sa, sa+n, cmp);
	for (i=k=pos[0]=0; i<n; ++i) { if (i&&val[sa[i]]-val[sa[i-1]]) k++; rk[sa[i]]=k; pos[k+1]=i+1; }
	for (l=1; n-rk[sa[n-1]]-1; l<<=1) {
		for (i=0; i<n; ++i) tsa[pos[rk[j=(sa[i]-l+n)%n]]++] = j;
		for (i=k=pos[0]=0; i<n; ++i) { if (i&&!eq(tsa[i], tsa[i-1], l)) k++; sa[tsa[i]]=k; pos[k+1]=i+1; }
		memcpy(rk, sa, n*sizeof(int)), memcpy(sa, tsa, n*sizeof(int));
	}
}

void lcpinit(int *val, int *sa, int *rk, int n) {
	int i, j, k;
	for (i=k=0; i<n; ht[rk[i++]]=k) if (rk[i])
		for (k?k--:0, j=sa[rk[i]-1]; val[i+k]==val[j+k]; ++k);
}


void conduct() {
	int i, ans;
	scanf("%s", str); m=strlen(str);
	for (i=0; i<m; ++i) val[i]=str[i]; val[i]=-1;
	scanf("%s", str); n=m+strlen(str)+1;
	for (i=m+1; i<n; ++i) val[i]=str[i-m-1]; val[n++]=-2; 
	sufixarray(val, n); lcpinit(val, sa, rk, n);
	for (ans=i=0; i<n; ++i) if (ht[i]>ans) 
		if ((sa[i]>m && sa[i-1]<m) || (sa[i]<m && sa[i-1]>m)) ans=ht[i];
	printf("%d\n", ans);
}

int main() {
	conduct();
	return 0;
}
