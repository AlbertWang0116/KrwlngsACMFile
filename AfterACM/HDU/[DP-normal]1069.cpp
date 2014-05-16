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

#define N 1100
int val[N], a[N], b[N], c[N], seq[N];
int n, m, cnt;

inline int getmax(int x, int y) { return x>y?x:y; }
int cmp1(const int &i, const int &j) { return b[i]<b[j]; }
int cmp2(const int &i, const int &j) { if (a[i]==a[j]) return b[i]>b[j]; return a[i]<a[j]; }

void seg_update(int id, int x, int y, int l, int r, int v1, int v2) {
	if (x>=l && y<=r) { val[id]=v1; return; }
	if (y<l || x>r) return;
	int mid=(x+y)>>1;
	seg_update(id*2+1, x, mid, l, r, v1, v2); seg_update(id*2+2, mid+1, y, l, r, v1, v2);
}

int seg_check(int id, int x, int y, int v) {
	if (x==y) return val[id];
	int mid=(x+y)>>1;
	if (v<=mid) return getmax(val[id], seg_check(id*2+1, x, mid, v));
	else return getmax(val[id], seg_check(id*2+2, mid+1, y, v));
}

int search(int x) {
	int lst, mst, mid;
	lst=0; mst=cnt;
	while (lst<mst) {
		mid=((lst+mst)>>1)+1;
		if (seg_check(0, 0, cnt, mid)>=x) mst=mid-1;
		else lst=mid;
	}
	return lst;
}

void conduct() {
	int i, j, k, l, s[3];
	for (i=0; i<m; ++i) { 
		scanf("%d%d%d", &s[0], &s[1], &s[2]); sort(s, s+3);
		a[i*3]=s[0]; b[i*3]=s[1]; c[i*3]=s[2];
		a[i*3+1]=s[0]; b[i*3+1]=s[2]; c[i*3+1]=s[1];
		a[i*3+2]=s[1]; b[i*3+2]=s[2]; c[i*3+2]=s[0];
	} n=m*3;
	for (i=0; i<n; ++i) seq[i]=i; sort(seq, seq+n, cmp1);
	map<int, int> dic; dic.clear();
	for (i=cnt=0; i<n; ++i) {
		dic.insert(pair<int, int>(b[seq[i]], cnt++));
		for (j=i; j+1<n && b[seq[j+1]]==b[seq[j]]; ++j); i=j;
	}
	sort(seq, seq+n, cmp2);
	memset(val, 0, sizeof(val));
	for (i=0; i<n; ++i) {
		j=dic.find(b[seq[i]])->second;
		l=seg_check(0, 0, cnt, j)+c[seq[i]];
		k=search(l);
		if (k>j) seg_update(0, 0, cnt, j+1, k, l, i);
	}
	/*for (i=0; i<n; ++i) {
		val[i]=c[seq[i]];
		for (j=i-1; ~j; --j) if (b[seq[j]]<b[seq[i]]) val[i]=getmax(val[i], val[j]+c[seq[i]]);
	}*/
	printf("%d\n", seg_check(0, 0, cnt, cnt));
	//printf("%d\n", val[n-1]);
}

int main() {
	int time=0;
	while (scanf("%d", &m)!=EOF && m) {
		printf("Case %d: maximum height = ", ++time);
		conduct();
	}
	return 0;
}
