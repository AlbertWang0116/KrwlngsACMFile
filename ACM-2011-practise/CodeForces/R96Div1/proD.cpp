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

#define N 1000010
char str[N];
int a[N], val[N], st[N], len[N];
int n, m;

void conduct() {
	int i, j, ret, tag;
	for (i = strlen(str)-1, n = 0; i >= 0; --i) a[n++] = str[i]-'0';
	for (tag = -1, i = m = 0; i < n; ++i) {
		if (a[i] && tag < 0) tag = i;
		if (!a[i] && tag >= 0) { st[m] = tag; len[m] = i-tag; m++; tag = -1; }
	} if (tag >= 0) { st[m] = tag; len[m] = i-tag; m++; }
	memset(val, 0, sizeof(val));
//	for (i = 0; i < m; ++i) printf("i:%d st:%d len:%d\n", i, st[i], len[i]);
	for (ret = i = 0; i < m; ) {
		if (len[i] == 1) { val[st[i]] = 1; ++i; ++ret; continue; }
		for (j = i+1; j < m && st[j]-st[j-1] == len[j-1]+1; ++j);
		for (ret += j-i+1, val[st[i]] = -1; i < j; ++i) val[st[i]+len[i]] = -1;
		val[st[i-1]+len[i-1]] = 1;
	} printf("%d\n", ret);
	for (i = 0; i <= n; ++i) if (val[i] != 0) {
		if (val[i] > 0) printf("+"); else printf("-");
		printf("2^%d\n", i);
	}
}

int main() {
	while (scanf("%s", str) != EOF) conduct();
	return 0;
}
