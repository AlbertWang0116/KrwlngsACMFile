#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;

#define N 1100000

int a[N];
int n;

void conduct() {
	int i, ans, tmp, st, ed, pre;
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	ans=a[0]; st=0; ed=0; pre=0; tmp=ans;
	for (i=1; i<n; ++i) {
		if (tmp<0) { tmp=0; pre=i; }
		tmp+=a[i];
		if (tmp>ans) { ans=tmp; st=pre; ed=i; }
	}
	printf("%d %d %d\n", ans, st+1, ed+1);
}

int main() {
	int time; scanf("%d", &time);
	for (int i=1; i<=time; ++i) {
		printf("Case %d:\n", i);
		conduct();
		if (i<time) printf("\n");
	}
	return 0;
}
