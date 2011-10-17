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
	int i, n, ct, c4, c7;
	scanf("%d", &n); ct = 0; c4 = 0; c7 = 0;
	for (i = 0; i * 4 <= n; ++i) if ((n-i*4) % 7 == 0) {
		if (!ct || i+(n-i*4)/7 <= ct) { ct = i+(n-i*4)/7; c4 = i; c7 = (n-i*4)/7; }
	} if (ct) { for (i = 0; i < c4; ++i) printf("4"); for (i = 0; i < c7; ++i) printf("7"); printf("\n"); }
	else printf("-1\n");
}
