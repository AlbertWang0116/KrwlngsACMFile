#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 1010
char map[N][N];
int lft[N][N], rit[N][N], up[N][N], down[N][N], seq[N][N], next[N];
int n;

int getmin(int x, int y) { return x < y ? x : y; }
int getmax(int x, int y) { return x > y ? x : y; }

void input()
{
	int i, j;
	scanf("%d", &n);
	for (i = 0; i < n; ++i)
	{
		getchar();
		for (j = 0; j < n; ++j) map[i][j] = getchar();
	}
}

int find(int x)
{
	if (next[x] == x) return x;
	if (next[x] != next[next[x]]) next[x] = find(next[x]);
	return next[x];
}

void conduct()
{
	int i, j, k;
	int ans, ub;
	for (i = 0; i < n; ++i)
	{
		k = -1;
		for (j = 0; j < n; ++j) 
			if (map[i][j] == '0') { k = j; lft[i][j] = 0;}
			else lft[i][j] = j - k;
	}
	for (i = 0; i < n; ++i)
	{
		k = n;
		for (j = n-1; j >= 0; --j)
			if (map[i][j] == '0') { k = j; rit[i][j] = 0;}
			else rit[i][j] = k - j;
	}
	for (i = 0; i < n; ++i)
	{
		k = -1;
		for (j = 0; j < n; ++j)
			if (map[j][i] == '0') { k = j; up[j][i] = 0;}
			else up[j][i] = j - k;
	}
	for (i = 0; i < n; ++i)
	{
		k = n;
		for (j = n-1; j >= 0; --j)
			if (map[j][i] == '0') { k = j; down[j][i] = 0;}
			else down[j][i] = k - j;
	}
//	printf("rit:\n");
//	for (i = 0; i < n; ++i)
//	{
//		for (j = 0; j < n; ++j) printf("%d ", rit[i][j]);
//		printf("\n");
//	}
//	printf("lft:\n");
//	for (i = 0; i < n; ++i)
//	{
//		for (j = 0; j < n; ++j) printf("%d ", lft[i][j]);
//		printf("\n");
//	}
//	printf("up:\n");
//	for (i = 0; i < n; ++i)
//	{
//		for (j = 0; j < n; ++j) printf("%d ", up[i][j]);
//		printf("\n");
//	}
//	printf("down:\n");
//	for (i = 0; i < n; ++i)
//	{
//		for (j = 0; j < n; ++j) printf("%d ", down[i][j]);
//		printf("\n");
//	}
	ans = 0;
	for (i = 0; i < n; ++i)
	{
		ub = n - i;
		for (j = 0; j <= ub; ++j) { seq[j][0] = 0; next[j] = j;}
		for (j = 0; j < ub; ++j)
		{
			k = (down[i+j][j] < rit[i+j][j] ? down[i+j][j] : rit[i+j][j]);
//			k = getmin(down[i+j][j], rit[i+j][j]);
			seq[j+k][++seq[j+k][0]] = j;
		}
		for (j = 0; j < ub; ++j)
		{
			for (k = 1; k <= seq[j][0]; ++k) next[seq[j][k]] = find(seq[j][k]+1);
			k = (up[i+j][j] < lft[i+j][j] ? up[i+j][j] : lft[i+j][j]);
//			k = getmin(up[i+j][j], lft[i+j][j]);
			k = j - find(j-k+1) + 1;
			ans = (ans > k ? ans : k);
//			ans = getmax(ans, j-find(j-k+1)+1);
//			if (ans == 1)
//			{
//				printf("i=%d j=%d find(%d)=%d\n", i, j, j-k+1, find(j-k+1));
//				return;
//			}
		}
	}
	for (i = 1; i < n; ++i)
	{
		ub = n - i;
		for (j = 0; j <= ub; ++j) { seq[j][0] = 0; next[j] = j;}
		for (j = 0; j < ub; ++j)
		{
			k = (down[j][i+j] < rit[j][i+j] ? down[j][i+j] : rit[j][i+j]);
//			k = getmin(down[j][i+j], rit[j][i+j]);
			seq[j+k][++seq[j+k][0]] = j;
		}
		for (j = 0; j < ub; ++j)
		{
			for (k = 1; k <= seq[j][0]; ++k) next[seq[j][k]] = find(seq[j][k]+1);
			k = (up[j][i+j] < lft[j][i+j] ? up[j][i+j] : lft[j][i+j]);
//			k = getmin(up[j][i+j], lft[j][i+j]);
			k = j-find(j-k+1)+1;
			ans = (ans > k ? ans : k);
//			ans = getmax(ans, j-find(j-k+1)+1);
//			if (ans == 1)
//			{
//				printf("j=%d find(%d)=%d\n", j, j-k+1, find(j-k+1));
//				return;
//			}
		}
	}
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

