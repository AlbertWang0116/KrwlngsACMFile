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

#define N 200010
int rk[3*N+101], sa[2*N], val[N], *ht=sa+N, *pe=rk+3*N+100;
char str[N];
int n, m;

inline int getmin(int x, int y) { return x<y?x:y; }
inline int neq(int *rk, int x, int y) { return rk[x]^rk[y] || rk[x+1]^rk[y+1] || rk[x+2]^rk[y+2]; }
inline int cmp1(int *x1, int *x2, int y1, int y2) { return *x1<*x2 || *x1==*x2 && y1<y2; }
inline int cmp2(int *x1, int *x2, int y1, int y2) { return *x1<*x2 || *x1==*x2 && cmp1(x1+1, x2+1, y1, y2); }
inline int REF(int x, int nl, int sl, int sr) { return (x-sr)%3?(x-sl)/3:(x-sr)/3+nl; }
inline int ATI(int x, int nl, int sl, int sr) { return x<nl?x*3+sl:(x-nl)*3+sr; }

void beam(int *val, int *a, int *b, int n, int m) {
	int *pos=pe-m; memset(pos, 0, m*sizeof(int));
	for (int i=0; i<n; ++i) pos[val[a[i]]+1]++;
	for (int i=0; i<m; ++i) pos[i+1]+=pos[i];
	for (int i=0; i<n; ++i) b[pos[val[a[i]]]++]=a[i];
}

void serial(int *val, int *s1, int *s2, int *rk, int n) {
	int i, j, k, l, *a=s1, *b=s2, *c;
	for (i=j=0; i<n; ++i) j=getmin(j, val[i]);
	for (i=0; i<n; ++i) val[i]-=j;
	for (i=0; i<n; ++i) a[i]=i;
	for (j=0, l=(1<<16)-1; l; l<<=16, j+=16) {
		for (i=0; i<n; ++i) rk[i]=(val[i]&l)>>j;
		beam(rk, a, b, n, 1<<16);
		c=a; a=b; b=c;
	}
	for (i=k=0; i<n; ++i) { if (i&&val[a[i]]-val[a[i-1]]) k++; rk[a[i]]=k; }
}

void sufixarray(int *rk, int *sa, int *sax, int n, int m) {
	int i, j, k, nx=n-n/3, ny=n/3, nl=(n+1)/3, nr=(n+2)/3, sl=(n+1)%3, sr=(n+2)%3, *say=sax+nx, *rkx=rk+n;
	for (i=n-1, k=0; i>=0; i-=3) { sa[k++]=i; sa[k++]=i-1; }
	rk[n]=rk[n+1]=0;
	beam(rk+2, sa, sax, nx, m);
	beam(rk+1, sax, sa, nx, m);
	beam(rk, sa, sax, nx, m);
	for (i=k=0; i<nx; ++i) { if (i&&neq(rk, sax[i], sax[i-1])) k++; rkx[REF(sax[i], nl, sl, sr)]=k; }
	if (nx-k-1) sufixarray(rkx, sax, sa, nx, k+1);
	else for (i=0; i<nx; ++i) sax[rkx[i]]=i;
	for (i=k=0; i<nx; ++i) if (sax[i]<nl && (j=sl+sax[i]*3)) sa[k++]=j-1;
	beam(rk, sa, say, ny, m);
	for (i=j=k=0; i<n; ++i) 
		if (j<ny && (k==nx || (sax[k]<nl?
					cmp1(rk+say[j], rk+sl+sax[k]*3, rkx[(say[j]+1-sl)/3], rkx[sax[k]+nr]) :
					cmp2(rk+say[j], rk+sr+(sax[k]-nl)*3, rkx[(say[j]+2-sr)/3+nl], rkx[sax[k]-nr+1])))) sa[i]=say[j++];
		else sa[i]=ATI(sax[k++], nl, sl, sr);
	for (i=0; i<n; ++i) rk[sa[i]]=i;
}

void lcpinit(int *val, int *sa, int *rk, int n) {
	int i, j, k;
	for (i=k=0; i<n; ht[rk[i++]]=k, k?k--:0) if (rk[i])
		for (j=sa[rk[i]-1]; val[i+k]==val[j+k]; ++k);
}

void conduct() {
	int i, ans;
	scanf("%s", str); m=strlen(str);
	for (i=0; i<m; ++i) val[i]=str[i]; val[m]=1;
	scanf("%s", str); n=strlen(str);
	for (i=0; i<n; ++i) val[m+1+i]=str[i]; n+=m+1; val[n++]=0;
	for (i=0; i<n; ++i) rk[i]=val[i];
	//serial(val, sa, sa+n, rk, n);
	sufixarray(rk, sa, sa+n, n, 255);
	lcpinit(val, sa, rk, n);
	for (i=ans=0; i<n; ++i) if (ht[i]>ans)
		if (sa[i]<m && sa[i-1]>m || sa[i]>m && sa[i-1]<m) ans=ht[i];
	printf("%d\n", ans);
}

int main() {
	conduct();
	return 0;
}
