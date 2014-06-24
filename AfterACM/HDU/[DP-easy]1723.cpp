#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

#define N 110
long long f[N];
int n, m;

void conduct() {
	int i, j;
	memset(f, 0, sizeof(f)); f[0]=1;
	for (i=0; i<n; ++i) for (j=1; j<=m; ++j) if (i+j<n) f[i+j]+=f[i];
	cout << f[n-1] << endl;
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && (n||m) ) conduct();
	return 0;
}
