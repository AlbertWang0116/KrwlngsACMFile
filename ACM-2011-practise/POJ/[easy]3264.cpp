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
int mst[N], lst[N];
int n, m, maxval, minval, lft, rit;
const int MST = LONG_MAX, LST = LONG_MIN;

int getmax(int x, int y) { return x > y ? x : y; }
int getmin(int x, int y) { return x < y ? x : y; }

void st_insert(int seg, int x, int y, int idx, int val)
{
	int mid;
	if (idx < x || idx > y) return;
	mst[seg] = getmax(mst[seg], val); lst[seg] = getmin(lst[seg], val);
	if (x == y) return; mid = (x+y)>>1;
	st_insert(seg*2, x, mid, idx, val); st_insert(seg*2+1, mid+1, y, idx, val);
}

void st_search(int seg, int x, int y, int lft, int rit)
{
	int mid;
	if (lft > y || rit < x) return;
	if (x >= lft && y <= rit) { maxval = getmax(maxval, mst[seg]); minval = getmin(minval, lst[seg]); return; }
	mid = (x+y) >> 1;
	st_search(seg*2, x, mid, lft, rit); st_search(seg*2+1, mid+1, y, lft, rit);
}

void input()
{
	int i, val;
	scanf("%d %d", &n, &m);
	memset(mst, 0x80, sizeof(mst));
	memset(lst, 0x7f, sizeof(lst));
	for (i = 1; i <= n; ++i) { scanf("%d", &val); st_insert(1, 1, n, i, val); }
}

void conduct()
{
	while (m--) { 
		scanf("%d%d", &lft, &rit); 
		maxval = LST; minval = MST; 
		st_search(1, 1, n, lft, rit);
		printf("%d\n", maxval - minval);
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

