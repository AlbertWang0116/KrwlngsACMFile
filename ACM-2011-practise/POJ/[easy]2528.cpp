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

#define N 20010
#define M 1000010
int seq[N], col[N], val[N];
bool cov[M];
int n, m, ans;

int cmp(const int &x, const int &y) { return val[x] < val[y]; }

bool st_insert(int seq, int x, int y, int lft, int rit)
{
	int mid;
//	printf("%d %d %d %d\n", x, y, lft, rit);
	if (lft > y || rit < x || cov[seq]) return false;
	if (x >= lft && y <= rit) { cov[seq] = true; return true; }
	mid = (x + y) >> 1; int k = 0;
	k |= st_insert(seq*2, x, mid, lft, rit);
	k |= st_insert(seq*2+1, mid+1, y, lft, rit);
	if (cov[seq*2] && cov[seq*2+1]) cov[seq] = true;
	return k;
}

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) scanf("%d%d", &val[2*i-1], &val[2*i]);
}

void conduct()
{
	int i;
	for (i = 1; i <= 2*n; ++i) seq[i] = i; std::sort(seq+1, seq+2*n+1, cmp); 
	col[seq[1]] = 1;
	for (m = 1, i = 2; i <= 2*n; ++i) if (val[seq[i-1]] == val[seq[i]]) col[seq[i]] = m; else col[seq[i]] = ++m;
//	for (i = 1; i <= n; ++i) printf("%d %d\n", col[i*2-1], col[i*2]);
	memset(cov, false, sizeof(cov)); ans = 0;
	for (i = n; i > 0; --i) if (st_insert(1, 1, m, col[2*i-1], col[2*i])) ans++;
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

