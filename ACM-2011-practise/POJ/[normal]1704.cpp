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

int cmp(const int &x, const int &y) { return x > y; }

void conduct() {
	int i, state;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%d", &a[i]); sort(a, a+n, cmp);
	for (i = 0; i < n-1; ++i) a[i] = a[i]-a[i+1]-1; a[n-1]--;
	state = 0; for (i = 0; i < n; i += 2) state = state ^ a[i];
	if (state) printf("Georgia will win\n"); else printf("Bob will win\n");
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
