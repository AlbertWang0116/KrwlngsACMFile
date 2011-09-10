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

#define N 100
bool e[N][N];
int a[N], seq[N];
int n;

int cmp(const int &x, const int &y) { return a[x] > a[y]; }

bool judge()
{
	int i;
	for (i = 1; i <= a[seq[0]]; ++i)
	{
		if (!a[seq[i]]) return false;
		e[seq[i]][seq[0]] = e[seq[0]][seq[i]] = true;
		a[seq[i]]--;
	}
	a[seq[0]] = 0;
	return true;
}

int main()
{
	int i, j, time;
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	scanf("%d", &time);
	while (time--)
	{
		scanf("%d", &n);
		for (i = 0; i < n; ++i) scanf("%d", &a[i]);
		for (i = 0; i < n; ++i) seq[i] = i;
		std::sort(seq, seq+n, cmp);
		memset(e, false, sizeof(e));
		while (a[seq[0]])
		{
			if (!judge()) { printf("NO\n"); break; }
			std::sort(seq, seq+n, cmp);
//			printf("! "); for (i = 0; i < n; ++i) printf("%d ", a[seq[i]]); printf("\n");
		}
		if (!a[seq[0]])
		{
			printf("YES\n");
			for (i = 0; i < n; ++i)
			{
				printf("%d", e[i][0]); for (j = 1; j < n; ++j) printf(" %d", e[i][j]);
				printf("\n");
			}
		}
		if (time) printf("\n");
	}
//	fclose(stdin);
//	fclose(stdout);
}

