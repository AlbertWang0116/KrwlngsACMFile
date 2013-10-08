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

#define pw(x) (1<<(x))
#define N 60010
int val[N], sa[N], rk[N], tsa[N], pos[N], ht[N], lst[N][20], ref[N], ati[N], tag[N], nxt[N], bit[N];
char str[N];
int n, m;

int getmax(int x, int y) { return x>y?x:y; }
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

void lcpinit(int *val, int *sa, int *rk, int n) {
	int i, j, k;
	for (i=k=0; i<n; ht[rk[i++]]=k, k?k--:0) if (rk[i])
		for (j=sa[rk[i]-1]; val[i+k]==val[j+k]; ++k);
}

void rmqinit(int *val, int n) {
	int i, k;
	for (i=k=0; i<n; ++i) { if (pw(k+1)==i) k++; bit[i]=k; }
	for (i=0; i<n; ++i) lst[i][0]=val[i];
	for (k=1; pw(k)<n; ++k)
		for (i=0; i<=n-pw(k); ++i) lst[i][k]=getmin(lst[i][k-1], lst[i+pw(k-1)][k-1]);
}

int rmquery(int x, int y) { return getmin(lst[x][bit[y-x]], lst[y-pw(bit[y-x])+1][bit[y-x]]); }

int judge(int j, int k) {
	int l, ret;
	if (j==k) return n-j;
	l=getmin(nxt[j], nxt[k]);
	ret=rmquery(getmin(rk[ati[j]], rk[ati[k]])+1, getmax(rk[ati[j]], rk[ati[k]]));
	if (ret<l) return ret;
	for (ret=l; ret+j<n && ret+k<n && (!tag[j+ret] || !tag[k+ret]) && val[j+ret]==val[k+ret]; ++ret);
	if (ret+j==n || ret+k==n) return ret;
	if (val[j+ret]!=val[k+ret]) return ret;
	return ret+judge(j+ret, k+ret);
}

void conduct() {
	int i, j, k;
	char ch;
	scanf("%s", str); n=strlen(str);
	for (i=0; i<n; ++i) val[i]=str[i]; val[n]=-1;
	sufixarray(val, n+1); lcpinit(val, sa, rk, n+1); rmqinit(ht, n+1);
	for (i=0; i<n; ++i) { ref[i]=ati[i]=i; nxt[i]=N; tag[i]=1; }
	scanf("%d", &m);
	for (i=0; i<m; ++i) {
		scanf("%s", str);
		if (str[0]=='Q') {
			scanf("%d%d", &j, &k); j--; k--; 
			printf("%d\n", judge(ref[j], ref[k]));
		} else {
			cin >> ch; scanf("%d", &k);
			if (k>n) k=n+1; k--;
			for (j=n; j>k; --j) { val[j]=val[j-1]; ati[j]=ati[j-1]; nxt[j]=nxt[j-1]; tag[j]=tag[j-1]; ref[ati[j]]=j; }
			val[k]=ch; tag[k]=0; ati[k]=N-1; n++;
			for (--j; j>=0 && tag[j]; --j) nxt[j]=k-j;
		}
	}
}

int main() {
	conduct();
	return 0;
}
