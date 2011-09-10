#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 210
int a[N][N], b[N][N], c[N][N];
int n, m;

void input()
{
	int i, j;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j) scanf("%d", &a[i][j]);
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j) scanf("%d", &b[i][j]);
}

void conduct()
{
	int i, j, up, dwn, lft, rit;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
			if (abs(a[i][j] - b[i][j]) < 6) c[i][j] = 0;
			else c[i][j] = 1;
	up = n; dwn = -1; lft = m; rit = -1;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j) if (c[i][j])
		{
			if (i < up) up = i;
			if (i > dwn) dwn = i;
			if (j < lft) lft = j;
			if (j > rit) rit = j;
		}
	if (up != n && dwn != -1 && lft != m && rit != -1)
		cout << up+1 << ' ' << lft+1 << ' ' << dwn+1 << ' ' << rit+1 << endl;
	else cout << -1 << endl;
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
