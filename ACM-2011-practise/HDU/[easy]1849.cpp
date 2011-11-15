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
	int ret, i, n, m;
	while (scanf("%d", &n) != EOF && n) {
		for (ret = i = 0; i < n; ++i) {
			scanf("%d", &m); ret ^= m;
		} if (ret) printf("Rabbit Win!\n");
		else printf("Grass Win!\n");
	} return 0;
}
