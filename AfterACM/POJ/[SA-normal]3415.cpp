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

#define N 300010
int val[N], sa[N], rk[N], pos[N], tsa[N], ht[N], thr[N], cnt[N][2], tc[2];
long long bs[N][2];
char str[N];
int n, len, m;

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
	int i, j, id, cur, top;
	long long ans;
	scanf("%s", str); m=strlen(str);
	for (i=0; i<m; ++i) val[i]=str[i]; val[m++]=-1;
	scanf("%s", str); n=strlen(str);
	for (i=0; i<n; ++i) val[m+i]=str[i]; n+=m; val[n++]=-2;
	sufixarray(val, n); lcpinit(val, sa, rk, n);
	cnt[0][0]=cnt[0][1]=bs[0][0]=bs[0][1]=0; thr[0]=len-1;
	for (ans=0, i=1; i<n; ++i) {
		id=(sa[i-1]<m?0:1); cur=(sa[i]<m?0:1);
		if (ht[i]<len) { top=0; continue; }
		for (tc[0]=tc[1]=0; top && ht[i]<=thr[top]; top--)
			for (j=0; j<2; ++j) tc[j]+=cnt[top][j];
		top++; tc[id]++; thr[top]=ht[i];
		for (j=0; j<2; ++j) { cnt[top][j]=tc[j]; bs[top][j]=bs[top-1][j]+(long long)tc[j]*(ht[i]-thr[0]); }
		ans += bs[top][1-cur];
	}
	printf("%lld\n", ans);
}

int main() {
	while (scanf("%d", &len)!=EOF && len) conduct();
	return 0;
}
