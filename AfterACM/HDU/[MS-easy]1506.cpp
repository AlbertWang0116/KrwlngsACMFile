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

#define N 110000
int a[N], id[N];
long long val[N];
int n;

inline long long getmax(long long x, long long y) { return x>y?x:y; }

void conduct() {
	int i, top;
	long long ans;
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	id[0]=-1; val[0]=-1; top=0;
	for (ans=i=0; i<n; ++i) {
		while (a[i]<=val[top]) {
			ans=getmax(ans, val[top]*(i-id[top-1]-1));
			top--;
		}
		++top; id[top]=i; val[top]=a[i];
	}
	while (top) { ans=getmax(ans, val[top]*(n-id[top-1]-1)); --top; }
	cout << ans << endl;
}

int main() {
	while (scanf("%d", &n)!=EOF && n) conduct();
	return 0;
}
