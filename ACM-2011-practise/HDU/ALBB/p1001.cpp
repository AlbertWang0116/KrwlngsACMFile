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

int main()
{
	int n, k;
	int time;
	scanf("%d", &time);
	for (int i = 1; i <= time; ++i) {
		printf("Case %d: ", i);
		scanf("%d%d", &n, &k);
		if (k == 1) if (n % 2) printf("first\n"); else printf("second\n");
		else if (n <= k) printf("first\n"); else printf("second\n");
	}
}

