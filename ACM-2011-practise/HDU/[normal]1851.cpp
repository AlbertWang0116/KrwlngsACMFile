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
	int n, i, ret, p, q;
	int time; scanf("%d", &time);
	while (time--) {
		scanf("%d", &n);
		for (i = ret = 0; i < n; ++i) {
			scanf("%d%d", &p, &q);
			ret ^= p%(q+1);
		} if (ret) printf("No\n");
		else printf("Yes\n");
	} return 0;
}
