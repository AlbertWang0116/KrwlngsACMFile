#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
#include<climits>
using namespace std;

#define N 110000
struct edge { int nxt, des; };
int a[N], b[N], c[N], add[N], hd[N];
edge e[N];
int n, m, cnt;

int search(int sum, int val, int lst, int mst) {
	int mid;
	while (lst<mst) {
		mid=((lst+mst)>>1)+1;
		if (sum-add[mid]>val) lst=mid;
		else mst=mid-1;
	}
	return lst;
}

void insert(int x, int y) {
	++cnt; e[cnt].nxt=hd[x]; e[cnt].des=y; hd[x]=cnt;
}

void conduct() {
	int i, j, sum, ans;
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%d%d%d", &a[i], &b[i], &c[i]);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (sum=i=0; i<n; ++i) {
		add[i]=sum;
		if (b[i]-a[i]<sum) {
			j=search(sum, b[i]-a[i], 0, i);
			insert(j, i);
		}
		sum+=a[i];
	}
	for (ans=LONG_MAX, sum=0, i=n-1; ~i; --i) {
		sum+=c[i];
		for (j=hd[i]; j; j=e[j].nxt) sum-=c[e[j].des];
		if (sum<ans) ans=sum;
	}
	printf("Need to use %d mana points.\n", ans);
}

int main() {
	int time; scanf("%d", &time);
	for (int i=1; i<=time; ++i) {
		printf("Case %d: ", i);
		conduct();
	}
	return 0;
}
