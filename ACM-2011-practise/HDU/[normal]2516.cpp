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

#define N 10010
long long pos[N];
const long long MAX = 1LL<<32;
int next[N];
int cnt;
long long n;

void init() {
	long long val; int i;
	cnt = pos[1] = next[1] = 1;
	while (pos[cnt] <= MAX) {
		pos[cnt+1] = pos[cnt] + pos[next[cnt]];
		next[cnt+1] = next[cnt]; val = (pos[cnt+1]-1) / 2;
		while (pos[next[cnt+1]] <= val) next[cnt+1]++;
		cnt++;
	}
}

void conduct() {
	int i;
	for (i = 1; i <= cnt; ++i) if (pos[i] >= n) break;
	if (pos[i] == n) printf("Second win\n");
	else printf("First win\n");
}

int main() {
	init();
	while (scanf("%I64d", &n) != EOF && n) conduct();
	return 0;
}
