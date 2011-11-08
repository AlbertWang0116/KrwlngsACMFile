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

bool e[7][7];
int seq[7], tot[3], epr[3], bit[10]; 
char name1[20], name2[20], tstr[20];
const char name[7][20] = { "Anka", "Chapay", "Cleo", "Troll", "Dracul", "Snowy", "Hexadecimal" };
const int MAX = LONG_MAX;
int n;

int getmax(int x, int y) { return x > y ? x : y; }
int getmin(int x, int y) { return x < y ? x : y; }

void transvert(int x) {
	for (int i = 0; i < 7; ++i, x /= 3) seq[i] = x % 3;
}

void conduct()
{
	int i, j, k, ret, val, tv, mst, lst;
	for (bit[0] = 1, i = 1; i <= 7; ++i) bit[i] = bit[i-1] * 3;
	memset(e, 0, sizeof(e));
	for (i = 0; i < n; ++i) {
		scanf("%s%s%s", name1, tstr, name2);
		for (j = 0; j < 7; ++j) if (!strcmp(name1, name[j])) break;
		for (k = 0; k < 7; ++k) if (!strcmp(name2, name[k])) break;
		e[j][k] = 1;
	} scanf("%d%d%d", &tot[0], &tot[1], &tot[2]); 
	for (ret = MAX, val = i = 0; i < bit[7]; ++i) {
		transvert(i); mst = -MAX; lst = MAX;
		memset(epr, 0, sizeof(epr)); tv = 0;
		for (j = 0; j < 7; ++j) epr[seq[j]]++;
		for (j = 0; j < 3; ++j) if (epr[j]) epr[j] = tot[j] / epr[j]; else break;
		if (j < 3) continue;
		for (j = 0; j < 3; ++j) { mst = getmax(mst, epr[j]); lst = getmin(lst, epr[j]); }
		if (mst - lst > ret) continue;
		for (j = 0; j < 7; ++j) for (k = 0; k < 7; ++k) if (seq[j] == seq[k] && e[j][k]) tv++;
		if (mst - lst < ret || tv > val) { ret = mst - lst; val = tv; }
	} printf("%d %d\n", ret, val);
}

int main()
{
//	while (scanf("%d", &n) != EOF) conduct();
	scanf("%d", &n); conduct();
	return 0;
}
