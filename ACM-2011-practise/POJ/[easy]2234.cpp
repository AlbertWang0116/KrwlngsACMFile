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

#define N 110
int a[N];
int n;

void conduct() {
	int i, j;
	for (i = 0; i < n; ++i) scanf("%d", &a[i]);
	for (i = j = 0; i < n; ++i) j = j ^ a[i];
	if (j) printf("Yes\n"); else printf("No\n");
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
