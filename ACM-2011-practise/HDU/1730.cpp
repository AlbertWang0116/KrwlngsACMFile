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

int n, m;

void conduct() {
	int i, j, a, b;
	for (j = i = 0; i < n; ++i) {
		scanf("%d%d", &a, &b);
		j = j ^ (abs(a-b)-1);
	} if (j) printf("I WIN!\n"); else printf("BAD LUCK!\n");
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) conduct();
	return 0;
}
