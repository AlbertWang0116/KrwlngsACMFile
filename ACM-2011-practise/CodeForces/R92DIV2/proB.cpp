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

const int MAX = LONG_MAX, MIN = LONG_MIN;
int n, m, ret;
char str[10][10];
int  seq[10], val[10];

void judge() {
	int mst, lst, i, j;
	mst = MIN; lst = MAX;
	for (i = 0; i < m; ++i) {
		val[i] = 0; for (j = 0; j < n; ++j) {
			val[i] = val[i]*10+(str[i][seq[j]]-'0');
		}
		if (val[i] > mst) mst = val[i]; if (val[i] < lst) lst = val[i];
	} ret = min(ret, mst-lst);
}

void enum_per(int x) {
	int i, j, k;
	if (n-x > 1) enum_per(x+1); else { judge(); return; }
	for (i = x+1; i < n; ++i) {
		k = seq[x]; seq[x] = seq[n-i+x]; seq[n-i+x] = k;
		for (j = x+1; j <= x+(n-x-1)/2; ++j) { k = seq[j]; seq[j] = seq[n-j+x]; seq[n-j+x] = k; }
		enum_per(x+1);
	}
}


void conduct()
{
	for (int i = 0; i < m; ++i) scanf("%s", str[i]);
	for (int i = 0; i < n; ++i) seq[i] = i;
	ret = MAX; enum_per(0); printf("%d\n", ret);
}

int main()
{
//	while (scanf("%d%d", &m, &n) != EOF) conduct();
	scanf("%d%d", &m, &n); conduct();
	return 0;
}
