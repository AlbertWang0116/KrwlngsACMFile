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
	int n, m, q;
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		if (n % (m+q) <= m && n % (m+q) > 0) printf("LOST\n");
		else printf("WIN\n");
	} return 0;
}
