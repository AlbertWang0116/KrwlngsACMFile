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

int main() {
	int n, i, j, ret, cnt;
	while (scanf("%d", &n) != EOF) {
		if (n == 2) { printf("1\n1 2\n"); continue; }
		if (n == 1) { printf("0\n"); continue; }
		if (n == 3) { printf("2\n1 2\n2 3\n"); continue; }
		ret = (n-4)/2*(n/2); printf("%d\n", ret+n-n%2+n%2*n/2); cnt = (n-4)/2-1;
		for (i = 3; i < n-2; i += 2) printf("%d %d\n", 1, i+1);
		for (i = 1; i < n; ++i) for (j = i+3; j <= i+(cnt-(i-1)/2)*2+3; j += 2) printf("%d %d\n", i+1, j+1);
		for (i = 0; i < n-n%2-1; ++i) printf("%d %d\n", i+1, i+2); printf("%d %d\n", n-n%2, 1);
		if (n%2) { for (i = 0; i < n/2; ++i) printf("%d %d\n", n, i*2+1); }
	} return 0;
}
