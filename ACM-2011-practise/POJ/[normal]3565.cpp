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
#define MAX 1e14
#define eps 1e-6
int ry[N];
double mxx[N], mxy[N], myx[N], myy[N], vx[N], vy[N], val[N][N];
bool tx[N], ty[N];
int n;

void input()
{
	int i, j;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf %lf", &mxx[i], &mxy[i]);
	for (i = 0; i < n; ++i) scanf("%lf %lf", &myx[i], &myy[i]);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) val[i][j] = sqrt((mxx[i]-myx[j])*(mxx[i]-myx[j])+(mxy[i]-myy[j])*(mxy[i]-myy[j]));
}

bool match(int x)
{
	int i;
	tx[x] = true;
	for (i = 0; i < n; ++i) if (fabs(vx[x] + vy[i] - val[x][i]) < eps && !ty[i])
	{
		ty[i] = true;
		if (ry[i] == -1 || match(ry[i])) { ry[i] = x; return true;}
	}
	return false;
}

void conduct()
{
	int i, j, k;
	double lst, ans;
	for (i = 0; i < n; ++i) vy[i] = MAX; memset(vx, 0, sizeof(vx));
	for (i = 0; i < n; ++i) for (j = 0; j < n; ++j)
		if (val[i][j] < vy[j]) vy[j] = val[i][j];
	for (i = 0; i < n; ++i) ry[i] = -1;
	for (k = 0; k < n; ++k)
	{
		memset(tx, false, sizeof(tx)); memset(ty, false, sizeof(ty));
		while (!match(k))
		{
			lst = MAX;
			for (i = 0; i < n; ++i) if (tx[i])
				for (j = 0; j < n; ++j) if(!ty[j]) 
					if (val[i][j] - vx[i] - vy[j] - lst < -eps) lst = val[i][j] - vx[i] - vy[j];
			for (i = 0; i < n; ++i) if (tx[i]) { tx[i] = false; vx[i] += lst; }
			for (i = 0; i < n; ++i) if (ty[i]) { ty[i] = false; vy[i] -= lst; }
		}
	}
	//ans = 0;
	//for (i = 0; i < n; ++i) ans += vx[i] + vy[i];
	//printf("ans = %.3f\n", ans);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			if (ry[j] == i) { cout << j+1 << endl; break;}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	input();
	conduct();
	//fclose(stdin);
	//fclose(stdout);
}

