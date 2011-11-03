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

long long n, m; int req;

void printout(long long n, long long k, long long pos) {
	if (!k) { printf("."); return; }
	if (n - k < k)
		if (pos > (n-k)*2) printf("X");
		else printout((n-k)*2, n-k, pos);
	else if (n%2)
		if (pos == n) printf("X");
		else printout(n-1, k-1, pos);
	else if (pos % 2 || n-k*2 >= pos) printf("."); else printf("X");
}

void conduct()
{
	long long pos;
	while (req--) {
		cin >> pos;
		printout(n, m, pos);
	} printf("\n");
}

int main()
{
//	while (scanf("%lld%lld%d", &n, &m, &req) != EOF) conduct();
	cin >> n >> m >> req; conduct();
	return 0;
}
