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

#define REF(x, sl, sr, nl) ((x-sr)%3?(x-sl)/3:(x-sr)/3+(nl))
#define BIT(x) (1<<(x))
#define N 200010
int val[N], sa[2*N], rk[3*N+100], *pe=rk+3*N+100, *ht=sa+N;
char str[N];
int n, m;

const int bits = 16;
inline int getmin(int x, int y) { return x<y?x:y; }
inline int neq(int *rk, int i, int j) { return rk[i]-rk[j] || rk[i+1]-rk[j+1] || rk[i+2]-rk[j+2]; }
inline int cmp2(int x1, int y1, int x2, int y2) {
	return (x1<y1 || (x1==y1 && x2<y2));
}
inline int cmp(int x1, int y1, int x2, int y2, int x3, int y3) {
	return (x1<y1 || (x1==y1 && cmp2(x2, y2, x3, y3)));
}

void beam(int *val, int *a, int *b, int n, int m) {
	int *pos=pe-m; memset(pos, 0, m*sizeof(int));
	for (int i=0; i<n; ++i) pos[val[a[i]]+1]++;
	for (int i=1; i<m; ++i) pos[i]+=pos[i-1];
	for (int i=0; i<n; ++i) b[pos[val[a[i]]]++]=a[i];
}
/*
void serial(int *val, int *sa, int *rk, int n, int m) {
	int i, j, k=BIT(bits), l=BIT(bits)-1, *a=sa, *b=tsa, *c;
	for (i=j=0; i<n; ++i) j=getmin(val[i], j);
	for (i=0; i<n; ++i) rk[i]=val[i]-j; m-=j;
	if (m<k && m<n) { for (i=0; i<n; ++i) rk[i]++; return; }
	for (i=0; i<n; ++i) a[i]=i;
	for (j=0; m; j+=bits, m>>=bits, l<<=bits) {
		for (i=0; i<n; ++i) rk[n+i]=((rk[i]&l)>>j);
		beam(rk+n, a, b, n, k);
		c=a; a=b; b=c;
	}
	for (i=k=rk[a[0]]=1; i<n; ++i) { if (val[a[i]]-val[a[i-1]]) k++; rk[a[i]]=k; }
}*/

void sufixarray(int *sa, int *san, int *rk, int n, int m) {
	int i, j, k, l, nr=(n+2)/3, sr=(n+2)%3, nl=(n+1)/3, sl=(n+1)%3, no=n/3, *tsa=san+nl+nr, *rkn=rk+n;
	for (i=n-1, l=0; i>=0; i-=3) { sa[l++]=i; sa[l++]=i-1; } if (sa[l-1]<0) l--;
	rk[n]=rk[n+1]=0;
	beam(rk+2, sa, san, l, m);
	beam(rk+1, san, sa, l, m);
	beam(rk, sa, san, l, m);
	for (i=k=0; i<l; ++i) { if (i&&neq(rk, san[i], san[i-1])) k++; rkn[REF(san[i], sl, sr, nl)]=k; }
	if (l-k-1) sufixarray(san, sa, rkn, l, k+1);
	else for (i=0; i<l; ++i) san[rkn[i]]=i;
	for (i=k=0; i<l; ++i) if (san[i]<nl && (san[i]||sl)) sa[k++]=sl+san[i]*3-1;
	beam(rk, sa, tsa, k, m);
	for (i=j=k=0; i<n; ++i) {
		int tmp=san[k]<nl?san[k]*3+sl:(san[k]-nl)*3+sr;
		if (j<no && (k==l || (san[k]<nl?cmp2(rk[tsa[j]], rk[tmp], rkn[(tsa[j]+1-sl)/3], rkn[san[k]+nr]):cmp(rk[tsa[j]], rk[tmp], rk[tsa[j]+1], rk[tmp+1], rkn[(tsa[j]+2-sr)/3+nl], rkn[san[k]-nr+1])))) { sa[i]=tsa[j]; j++; }
		else { sa[i]=tmp; k++; }
	}
	for (i=0; i<n; ++i) rk[sa[i]]=i;
}

void lcpinit(int *val, int *sa, int *rk, int n) {
	int i, j, k;
	for (i=k=0; i<n; ht[rk[i++]]=k, k?k--:0) if (rk[i])
		for (j=sa[rk[i]-1]; val[i+k]==val[j+k]; ++k);
}

void conduct() {
	int i, ans;
	scanf("%s", str);
	m=strlen(str); for (i=0; i<m; ++i) val[i]=str[i]; val[m++]=1;
	scanf("%s", str);
	n=strlen(str); for (i=0; i<n; ++i) val[i+m]=str[i]; n+=m; val[n++]=0;
	memcpy(rk, val, n*sizeof(int));
//	serial(val, sa, rk, n, 150);
	sufixarray(sa, sa+n, rk, n, 255);
	lcpinit(val, sa, rk, n);
	for (ans=i=0; i<n; ++i)
		if (ht[i]>ans && ((sa[i-1]<m && sa[i]>=m) || (sa[i-1]>=m && sa[i]<m))) ans=ht[i];
	printf("%d\n", ans);
}

int main() {
	conduct();
	return 0;
}
