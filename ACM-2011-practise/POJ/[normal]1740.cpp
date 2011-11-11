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
	int i;
	for (i = 0; i < n; ++i) scanf("%d", &a[i]); sort(a, a+n);
	for (i = 0; i < n; i += 2) if (a[i] != a[i+1]) break;
	if (n%2 || i < n) printf("1\n"); else printf("0\n");
}

int main() {
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
