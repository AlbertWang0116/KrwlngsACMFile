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
	long long n; int cnt;
	scanf("%I64d", &n);
	for (cnt = 0; n; n /= 10) if (n % 10 == 7 || n % 10 == 4) cnt++;
	if (cnt != 7 && cnt != 4) printf("NO\n"); else printf("YES\n");
}
	
