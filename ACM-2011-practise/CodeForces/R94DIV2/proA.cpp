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
int a[N];
int n;

void conduct() {
	int i, tot, ret;
	for (i = 0; i < n; ++i) scanf("%d", &a[i]);
	for (tot = i = 0; i < n; ++i) tot += a[i]; tot &= 1;
	for (ret = i = 0; i < n; ++i) if ((a[i]&1) == tot) ret++;
	printf("%d\n", ret);
}

int main() {
//	while (scanf("%d", &n) != EOF) conduct();
	scanf("%d", &n); conduct();
	return 0;
}
