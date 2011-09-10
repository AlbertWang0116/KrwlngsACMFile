#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

#define N 20
int st[N][N];
char map[N][N];
int n, m, cl;

void input()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) st[i][j] = -1;
	for (int i = 1; i <= n; ++i)
	{
		getchar();
		for (int j = 1; j <= m; ++j) scanf("%c", &map[i][j]);
	}
}

void conduct()
{
	//for (int i = 1; i <= n; ++i)
		//for (int j = 1; j <= m; ++j) printf("%c", map[i][j]);
	int cur, x, y;
	cur = 0;
	x = cl; y = 1;
	while (true)
	{
		//printf("x=%d y=%d cur=%d\n", x, y, cur);
		if (x < 1 || x > m || y < 1 || y > n)
		{
			cout << cur << " step(s) to exit" << endl;
			break;
		}
		if (st[y][x] >= 0)
		{
			cout << st[y][x] << " step(s) before a loop of " << cur - st[y][x] << " step(s)" << endl;
			break;
		}
		st[y][x] = cur;
		//printf("map[%d][%d]=%c\n", y, x, map[y][x]);
		switch(map[y][x])
		{
		case 'N':
			y--;
			break;
		case 'E':
			x++;
			break;
		case 'S':
			y++;
			break;
		case 'W':
			x--;
			break;
		}
		cur++;
	}
}

int main()
{
	do
	{
		scanf("%d %d %d", &n, &m, &cl);
		if (n == 0 && m == 0 && cl == 0) break;
		input();
		conduct();
	}while (true);
	return 0;
}
