#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 110
#define MAX 10010
int n, m, nx, ny;
bool tx[N], ty[N];
int mx[N][N], my[N][N], vx[N], vy[N], val[N][N], ry[N];

void input()
{
	int i, j, k, l;
	char info[N];
	nx = 0;
	ny = 0;
	for (i = 0; i < n; ++i)
	{
		scanf("%s", info);
		for (j = 0; j < m; ++j)
		{
			if (info[j] == 'H') my[i][j] = ++ny;
			else my[i][j] = 0;
			if (info[j] == 'm') mx[i][j] = ++nx;
			else mx[i][j] = 0;
		}
	}
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
			if (mx[i][j])
				for (k = 0; k < n; ++k)
					for (l = 0; l < m; ++l)
						if (my[k][l]) val[mx[i][j]][my[k][l]] = abs(k-i)+abs(l-j);
	/*for (i = 0; i < n; ++i)
	{
		for (j = 0; j < m; ++j) printf("%d ", mx[i][j]);
		printf("\n");
	}
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < m; ++j) printf("%d ", my[i][j]);
		printf("\n");
	}
	printf("nx=%d ny=%d\n", nx, ny);
	for (i = 1; i <= nx; ++i)
		for (j = 1; j <= ny; ++j) printf("val[%d][%d]=%d\n", i, j, val[i][j]);*/
}

bool match(int x)
{
	int i;
	tx[x] = true;
	for (i = 1; i <= ny; ++i)
		if (vx[x] + vy[i] == val[x][i] && !ty[i])
		{
			ty[i] = true;
			if (!ry[i] || match(ry[i]))
			{
				ry[i] = x;
				return true;
			}
		}
	return false;
}

void conduct()
{
	int i, j, k;
	int lst, ans;
	for (i = 1; i <= nx; ++i) vx[i] = MAX;
	memset(vy, 0, sizeof(vy));
	for (i = 1; i <= nx; ++i)
		for (j = 1; j <= ny; ++j)
			if (val[i][j] < vx[i]) vx[i] = val[i][j];
	memset(ry, 0, sizeof(ry));
	for (k = 1; k <= nx; ++k)
	{
		memset(tx, false, sizeof(tx));
		memset(ty, false, sizeof(ty));
		while (!match(k))
		{
			lst = MAX;
			for (i = 1; i <= nx; ++i)
				if (tx[i])
					for (j = 1; j <= ny; ++j)
						if (!ty[j] && val[i][j] - vx[i] - vy[j]< lst) lst = val[i][j] - vx[i] - vy[j];
			/*printf("k=%d, lst=%d\n", k, lst);
			for (i = 1; i <= nx; ++i) printf("tx[%d]=%d", i, tx[i]);
			printf("\n");
			for (i = 1; i <= nx; ++i) printf("vx[%d]=%d", i, vx[i]);
			printf("\n");
			for (i = 1; i <= ny; ++i) printf("ty[%d]=%d", i, ty[i]);
			printf("\n");
			for (i = 1; i <= nx; ++i) printf("vy[%d]=%d", i, vy[i]);
			printf("\n");*/
			for (i = 1; i <= nx; ++i)
				if (tx[i]) {tx[i] = false; vx[i] += lst;}
			for (i = 1; i <= ny; ++i)
				if (ty[i]) {ty[i] = false; vy[i] -= lst;}
		}
	}
	ans = 0;
	for (i = 1; i <= nx; ++i) ans += vx[i];
	for (i = 1; i <= ny; ++i) ans += vy[i];
	//for (i = 1; i <= ny; ++i) printf("vy[%d]=%d ry[%d]=%d vx[%d]=%d val[%d][%d]=%d\n", i, vy[i], i, ry[i], ry[i], vx[ry[i]], ry[i], i, val[ry[i]][i]);
	cout << ans << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while (scanf("%d %d", &n, &m) != EOF && (n || m))
	{
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

