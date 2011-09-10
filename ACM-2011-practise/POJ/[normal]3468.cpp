#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

#define N 2000010
long long sum[N], ele[N], ans;
int n, m;

int getmax(int x, int y) { return x > y ? x : y; }
int getmin(int x, int y) { return x < y ? x : y; }

void st_insert(int seg, int x, int y, int lft, int rit, long long val)
{
	int mid, lmst, rmst, inc; 
	if (rit < x || lft > y) return;
	if (x >= lft && y <= rit) { ele[seg] += val; return; }
	mid = (x + y) >> 1;
	if (ele[seg]) { 
		st_insert(seg*2, x, mid, 1, n, ele[seg]); st_insert(seg*2+1, mid+1, y, 1, n, ele[seg]);
		sum[seg] += ele[seg] * (y-x+1); ele[seg] = 0;
	}
	lmst = getmin(lft, x); rmst = getmax(rit, y); 
	inc = rit + y + lmst - lft - x - rmst + 1; sum[seg] += val * inc;
	st_insert(seg*2, x, mid, lft, rit, val); st_insert(seg*2+1, mid+1, y, lft, rit, val);
}

void st_search(int seg, int x, int y, int lft, int rit)
{
	int mid;
	if (rit < x || lft > y) return;
	if (x >= lft && y <= rit) { ans += sum[seg] + ele[seg] * (y-x+1); return; }
	mid = (x + y) >> 1;
	if (ele[seg]) {
		st_insert(seg*2, x, mid, 1, n, ele[seg]); st_insert(seg*2+1, mid+1, y, 1, n, ele[seg]);
		sum[seg] += ele[seg] * (y-x+1); ele[seg] = 0;
	}
	st_search(seg*2, x, mid, lft, rit); st_search(seg*2+1, mid+1, y, lft, rit);
}

void input()
{
	int i; long long val;
	scanf("%d %d", &n, &m);
	memset(sum, 0, sizeof(sum)); memset(ele, 0, sizeof(ele));
	for (i = 1; i <= n; ++i) {
		scanf("%lld", &val);
		st_insert(1, 1, n, i, i, val);
	}
}

void conduct()
{
	char cmd[10];
	int lft, rit; long long val;
	while (m--) {
		scanf("%s", cmd);
		switch (cmd[0]) {
			case 'C': scanf("%d %d %lld", &lft, &rit, &val); st_insert(1, 1, n, lft, rit, val); break;
			case 'Q': scanf("%d %d", &lft, &rit); ans = 0; st_search(1, 1, n, lft, rit); printf("%lld\n", ans); break;
		}
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

