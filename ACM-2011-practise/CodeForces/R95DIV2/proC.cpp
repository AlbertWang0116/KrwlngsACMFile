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

long long n, m, tot;

long long cal(long long base, long long val) {
	long long ret, i;
	if (base-val < val) val = base-val;
	for (ret = i = 1; i <= val; ++i) ret = ret * (base-i+1) / i;
	return ret;
}

void conduct() {
	long long ret, i, j, k;
	for (ret = i = 0; i < n; ++i)
		for (j = i+3; j < n; ++j)
			for (k = 0; k < m; ++k) if (n+m-k-j+3 >= tot) 
				ret += cal(j-i-1, 2) * cal(n+m-k-j-2, tot-5);
	cout << ret << endl;
}

int main() {
	while (scanf("%lld%lld%lld", &n, &m, &tot) != EOF) conduct();
	return 0;
}
