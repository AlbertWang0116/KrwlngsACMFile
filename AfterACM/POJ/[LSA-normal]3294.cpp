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

#define N 110000
int val[N], rk[3*N+101], sa[2*N], col[N], *ht=sa+N, *pe=rk+3*N+100, *seq=rk+N, *que=rk+2*N, cnt[1100];
char str[2100];
int n, m;

inline int neq(int *rk, int x, int y) { return rk[x]^rk[y] || rk[x+1]^rk[y+1] || rk[x+2]^rk[y+2]; }
inline int cmp1(int *x1, int *x2, int y1, int y2) { return *x1<*x2 || *x1==*x2 && y1<y2; }
inline int cmp2(int *x1, int *x2, int y1, int y2) { return *x1<*x2 || *x1==*x2 && cmp1(x1+1, x2+1, y1, y2); }
inline int REF(int x, int nl, int sl, int sr) { return (x-sr)%3?(x-sl)/3:(x-sr)/3+nl; }
inline int ATI(int x, int nl, int sl, int sr) { return x<nl?sl+x*3:sr+(x-nl)*3; }

void beam(int *val, int *a, int *b, int n, int m) {
	int *pos=pe-m; memset(pos, 0, m*sizeof(int));
	for (int i=0; i<n; ++i) pos[val[a[i]]+1]++;
	for (int i=0; i<m; ++i) pos[i+1]+=pos[i];
	for (int i=0; i<n; ++i) b[pos[val[a[i]]]++]=a[i];
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
						cmp1(rk+say[j], rk+sl+sax[k]*3, rkx[(say[j]+1-sl)/3], rkx[sax[k]+nr]):
						cmp2(rk+say[j], rk+sr+(sax[k]-nl)*3, rkx[(say[j]+2-sr)/3+nl], rkx[sax[k]-nr+1])))) sa[i]=say[j++];
		else sa[i]=ATI(sax[k++], nl, sl, sr);
	for (i=0; i<n; ++i) rk[sa[i]]=i;
}

void lcpinit(int *val, int *sa, int *rk, int n) {
	int i, j, k;
	for (i=k=0; i<n; ht[rk[i++]]=k, k?k--:0) if (rk[i])
		for (j=sa[rk[i]-1]; val[i+k]==val[j+k]; ++k);
}

void print(int x, int l) { for (int i=0; i<l; ++i) printf("%c", val[x+i]); printf("\n"); }

void conduct() {
	int i, j, k, ans, tag, tot;
	for (i=n=0; i<m; ++i) {
		scanf("%s", str); k=strlen(str);
		for (j=0; j<=k; ++j) { val[n+j]=str[j]; col[n+j]=i; }
		val[n+k]=-i-1; n+=k+1;
	}
	if (m==1) { printf("%s\n", str); return; }
	memcpy(rk, val, n*sizeof(int));
	for (i=0; i<n; ++i) rk[i]+=m;
	sufixarray(rk, sa, sa+n, n, 255);
	lcpinit(val, sa, rk, n);
	memset(cnt, 0, m*sizeof(int)); que[0]=2; que[1]=1;
	cnt[col[sa[0]]]=1; tot=1;
	for (i=1, j=ans=seq[0]=tag=0; i<n; ++i) {
		if (!cnt[col[sa[i]]]) tot++; cnt[col[sa[i]]]++;
		while (que[1]>=que[0] && ht[i]<=ht[que[que[1]]]) --que[1]; 
		if (que[1]<que[0] && ht[i]<ht[que[que[0]]]) tag=1; que[++que[1]]=i;
		while (j<i && (tot>m/2+1 || cnt[col[sa[j]]]>1)) {
			cnt[col[sa[j]]]--; if (!cnt[col[sa[j]]]) tot--;
			if (que[que[0]]==j+1) ++que[0]; ++j;
		}
		if (tot>m/2) {
			if (ht[que[que[0]]]>ans) { ans=ht[que[que[0]]]; seq[0]=0; tag=1; }
			if (ht[que[que[0]]]==ans && tag) { seq[++seq[0]]=sa[i]; tag=0; }
		}
	}
	if (!ans) printf("?\n");
	else for (i=1; i<=seq[0]; ++i) print(seq[i], ans);
}

int main() {
	while (scanf("%d", &m)!=EOF && m) {
		conduct();
		printf("\n");
	}
	return 0;
}
