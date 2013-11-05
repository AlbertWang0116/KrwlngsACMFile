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

#define N 200010
int val[N], sa[N], rk[N], ht[N], lst[N][20], sb[N], id[N], acc[N], seq[N], pos[N], tsa[N];
char str[N];
int n, m;

int getmin(const int &x, const int &y) { return x<y?x:y; }

int strneq(const int &x, const int &y, const int &z) {
	for (int i=0; i<z; ++i) if (val[x+i]!=val[y+i]) return 1;
	return 0;
}

void print(const int &x, const int &z) {
	for (int i=0; i<z; ++i) printf("%c", val[x+i]);
	printf("\n");
}

int cmp(const int &i, const int &j) { return val[i]<val[j]; }
inline int neq(const int &i, const int &j, const int &l) { return rk[i]-rk[j]||rk[i+l]-rk[j+l]; }
void sufixarray(int *val, int n) {
	int i, j, k, l;
	for (i=0; i<n; ++i) sa[i]=i; sort(sa, sa+n, cmp);
	for (i=k=pos[0]=0; i<n; ++i) { if (i&&val[sa[i]]-val[sa[i-1]]) k++; rk[sa[i]]=k; pos[k+1]=i+1; }
	for (l=1; n-rk[sa[n-1]]-1; l<<=1) {
		for (i=0; i<n; ++i) tsa[pos[rk[j=(sa[i]-l+n)%n]]++] = j;
		for (i=k=pos[0]=0; i<n; ++i) { if (i&&neq(tsa[i], tsa[i-1], l)) k++; sa[tsa[i]]=k; pos[k+1]=i+1; }
		memcpy(rk, sa, n*sizeof(int)); memcpy(sa, tsa, n*sizeof(int));
	}
}

void lcpinit(int *val, int *sa, int *rk, int n) {
	int i, j, k;
	for (i=k=ht[0]=0; i<n; ht[rk[i++]]=k) if (rk[i])
		for (k?k--:0, j=sa[rk[i]-1]; val[i+k]==val[j+k]; ++k);
}

void rmqinit(int *val, int n) {
	int i, j, k;
	for (i=1, k=sb[0]=0; i<n; (1<<(k+1))==++i?k++:0) sb[i]=k;
	for (i=0; i<n; ++i) lst[i][0]=val[i];
	for (k=1; k<=sb[n-1]; ++k)
		for (i=0, j=n-(1<<k)+1; i<j; ++i) lst[i][k]=getmin(lst[i][k-1], lst[i+(1<<(k-1))][k-1]);
}

int rmquery(const int &i, const int &j) { return getmin(lst[i][sb[j-i]], lst[j-(1<<sb[j-i])+1][sb[j-i]]); }

void conduct() {
	int i, j, tmp, ans, top, cnt;
	for (i=tmp=0; i<n; ++i) {
		scanf("%s", str); m=tmp+strlen(str);
		for (j=tmp; j<m; ++j) val[j]=str[j-tmp]; val[m++]=-i-1;
		for (j=tmp; j<m; ++j) id[j]=i;
		tmp=m;
	}
	if (n==1) { print(0, m-1); return; }
	sufixarray(val, m); lcpinit(val, sa, rk, m); rmqinit(ht, m);
	memset(acc, 0, m*sizeof(int));
	for (ans=top=cnt=i=j=0; i<m; ++i) {
		if (!acc[id[sa[i]]]) cnt++;
		acc[id[sa[i]]]++;
		while (cnt>n/2+1 || acc[id[sa[j]]]>1) {  acc[id[sa[j]]]--; if (!acc[id[sa[j]]]) cnt--; j++; }
		if (cnt>n/2 && (tmp=rmquery(j+1, i))>=ans) {
			if (tmp>ans) { ans=tmp; top=0; }
			if (!top || strneq(seq[top-1], sa[j], ans)) seq[top++]=sa[j];
		}
	}
	if (ans) for (i=0; i<top; ++i) print(seq[i], ans);
	else printf("?\n");
}

int main() {
	while (scanf("%d", &n)!=EOF && n) {
		conduct();
		printf("\n");
	}
	return 0;
}
