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

long long a[110];

int main()
{
	int i, n; long long ans;
	while (scanf("%d", &n) != EOF) {
		for (i = 0; i < n; ++i) cin >> a[i];
		for (ans = i = 0; i < n; ++i) {
			ans += (a[i]-1) * (i+1) + 1;
		} cout << ans << endl;
	} return 0;
}
