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

long long n, m;

int gcd(long long x, long long y) { if (y == 0) return x; else return gcd(y, x%y); }

void input()
{
	scanf("%lld%lld", &n, &m);
}

void conduct()
{
	long long k, j, val;
	val = m; k = 1;
	while (val < n) { val *= m; k++; }
	j = gcd(k*val, n);
	printf("%lld/%lld\n", k*val/j, n/j);
}


int main()
{
	int time;
	scanf("%d", &time);
	for (int i = 1; i <= time; ++i) {
		printf("Case %d: ", i);
		input(); conduct();
	}
}
