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

#define N 210000
long long a[N];
int n;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j, k, ans, pre;
	long long sum;
	for (i=0; i<n; ++i) {
		scanf("%d%d", &j, &k);
		a[i]=j-k;
	}
	memcpy(a+n, a, n*sizeof(long long)); n*=2;
	for (ans=pre=sum=i=0; i<n; ++i) {
		sum+=a[i];
		if (sum<0) { pre=i+1; sum=0; }
		else ans=getmax(ans, i-pre+1);
	}
	if (ans>n/2) ans=n/2;
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n)!=EOF && n) conduct();
	return 0;
}
