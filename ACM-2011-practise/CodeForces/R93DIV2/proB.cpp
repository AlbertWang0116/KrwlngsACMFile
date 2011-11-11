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

#define N 10010
int a[N];
int n;

void conduct() {
	int i, cnt;
	for (i = 0; i < n; ++i) scanf("%d", &a[i]); sort(a, a+n);
	for (cnt = i = 0; i < n-1; ++i) if (a[i] == a[i+1]) { cnt++; i++; }
	printf("%d\n", cnt/2);
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
