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
#define N 200010
#define M 4000010
int val[N], sa[N], rk[N], pos[N], tsa[N], ht[N], lst[N][20], mst[M], bit[N];
char str[N];
int n, len, ans, st;

int getmax(int x, int y) { return x>y?x:y; }
int getmin(int x, int y) { return x<y?x:y; }

void insert(int id, int x, int y, int pos, int val) {
	mst[id]=getmax(mst[id], val);
	int mid=(x+y)/2; if (x>=y) return;
	if (pos<=mid) insert(id*2, x, mid, pos, val);
	else insert(id*2+1, mid+1, y, pos, val);
}

int query(int id, int x, int y, int lt, int rt) {
	if (lt>y || rt<x) return -1;
	if (x>=lt && y<=rt) return mst[id];
	int mid=(x+y)/2;
	return getmax(query(id*2, x, mid, lt, rt), query(id*2+1, mid+1, y, lt, rt));
}

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

void rmqinit(int *ht, int n) {
	int i, k;
	for (i=k=0; i<n; ++i) { if (pw(k+1)==i) k++; bit[i]=k; }
	for (i=0; i<n; ++i) lst[i][0]=ht[i];
	for (k=1; pw(k)<n; ++k)
		for (i=0; i<n-pw(k); ++i) lst[i][k]=getmin(lst[i][k-1], lst[i+pw(k-1)][k-1]);
}

int rmquery(int x, int y) { return getmin(lst[x][bit[y-x]], lst[y-pw(bit[y-x])+1][bit[y-x]]); }

void judge(int x, int l, int base, int flag) {
	int y, tmp;
	insert(1, 0, n-1, sa[x], base+flag*x);
	if (!l) return;
	y=query(1, 0, n-1, sa[x]+1, sa[x]+l); 
	if (y<0) return; else y=base+flag*y;	
	tmp=rmquery(getmin(x, y)+1, getmax(x, y));
	if (abs(sa[x]-sa[y])>tmp) return;
	tmp=tmp/abs(sa[x]-sa[y])+1;
	if (tmp>ans || (tmp==ans && x<st)) {
		ans=tmp; st=x; len=abs(sa[x]-sa[y])*tmp;
	}
}

void print(int x, int l) {
	for (int i=x; i<x+l; ++i) printf("%c", val[i]); printf("\n");
}

void conduct() {
	int i;
	n=strlen(str);
	for (i=0; i<n; ++i) val[i]=str[i]; val[n++] = -1;
	sufixarray(val, n); lcpinit(val, sa, rk, n); rmqinit(ht, n);
	memset(mst, -1, sizeof(mst)); 
	insert(1, 0, n-1, sa[0], 0);
	for (ans=0, i=1; i<n; ++i) judge(i, ht[i], 0, 1);
	memset(mst, -1, sizeof(mst));
	insert(1, 0, n-1, sa[n-1], 0);
	for (i=1; i<n; ++i) judge(n-1-i, ht[n-i], n-1, -1);
	if (!ans) printf("%c\n", val[sa[1]]);
	else print(sa[st], len);
}

int main() {
	int time=0;
	while (scanf("%s", str)!=EOF && str[0]!='#') {
		printf("Case %d: ", ++time);
		conduct();
	}
	return 0;
}
