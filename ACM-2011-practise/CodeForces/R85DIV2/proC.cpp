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

#define square(x) (x)*(x)

int main()
{
	int i; long long n, a, b;
	while (scanf("%I64d%I64d%I64d", &n, &a, &b) != EOF) {
		if (b-n+1 > 0 && square(b-n+1) + n - 1 >= a) {
			for (i = 0; i < n-1; ++i) printf("1\n");
			cout << b-n+1 << endl;
		} else printf("-1\n");
	} return 0;
}
