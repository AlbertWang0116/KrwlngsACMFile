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

const int md[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int ld[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int mnext[12] = { 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31 };
const int lnext[12] = { 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31 };
int yd[210];
#define N 50010
int f[N];

int getindex(int y, int m, int d) {
	int i, ret; ret = 0;
	if (y == 101) {
		if (m == 10) return 4-d;
		for (i = m+1; i < 10; ++i) ret += md[i];
		ret += 3; ret += md[m]-d+1; return ret;
	} for (i = y+1; i < 102; ++i) ret += yd[i];
	for (i = m+1; i < 12; ++i) ret += (yd[y]==366?ld[i]:md[i]);
	ret += (yd[y]==366?ld[m]:md[m])-d+1; return ret;
}

bool leap(int y) {
	if (y % 400 == 0) return 1;
	if (y % 100 == 0) return 0;
	return y % 4 == 0;
}

void init() {
	int i, y, m, d, nd, index;
	for (i = 0; i < 102; ++i) if (leap(1900+i)) yd[i] = 366; else yd[i] = 365; yd[101] = 307;
	for (y = 101; y >= 0; --y) {
		for (m = 11; m >= 0; --m) for (d = (yd[y]==366?ld[m]:md[m]); d > 0; --d) {
			nd = (yd[y]==366?lnext[m]:mnext[m]); index = getindex(y, m, d);
			f[index] = 0; if (d <= nd && index-31 >= 0) f[index] |= (1-f[index-(yd[y]==366?ld[m]:md[m])]);
			if (index > 0) f[index] |= (1-f[index-1]);
		}
	}
}

void conduct() {
	int y, m, d, index;
	scanf("%d%d%d", &y, &m, &d); y -= 1900; m--;
	index = getindex(y, m, d);
	if (f[index]) printf("YES\n"); else printf("NO\n");
}

int main() {
	int time; scanf("%d", &time);
	init();
	while (time--) conduct();
}
