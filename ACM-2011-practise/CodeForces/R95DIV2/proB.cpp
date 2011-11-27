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

#define N 100010
#define M 110
int a[N];
long long val[M];
int n;

void conduct() {
	int i; long long ret;
	memset(val, 0, sizeof(val));
	for (i = 0; i < n; ++i) { scanf("%d", &a[i]); val[a[i]+10]++; }
	for (ret = i = 0; i < n; ++i) ret += val[10-a[i]]-(!a[i]?1:0);
	cout << ret/2 << endl;
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
