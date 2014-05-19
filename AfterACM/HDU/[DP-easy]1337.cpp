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

int f[110], vst[110];

void init() {
	int i, j;
	memset(vst, 0, sizeof(vst));
	for (i=1; i<=100; ++i) for (j=i; j<=100; j+=i) vst[j]=1-vst[j];
	memset(f, 0, sizeof(f));
	for (i=1; i<=100; ++i) f[i]=f[i-1]+vst[i];
}

int main() {
	int n;
	int time; scanf("%d", &time);
	init();
	while (time--) {
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
