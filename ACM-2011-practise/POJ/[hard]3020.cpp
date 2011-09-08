#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 50
#define M 20
int map[N][M], rit[N*M], way[N*M][N*M];
bool vst[N*M];
int r, c, n;

void input()
{
	int i, j;
	char tr[M];
	scanf("%d %d", &r, &c);
	n = 0;
	for (i = 0; i < r; ++i)
	{
		scanf("%s", tr);
		for (j = 0; j < c; ++j)
			if (tr[j] == 'o') map[i][j] = -1;
			else map[i][j] = n++;
	}
//	for (i = 0; i < r; ++i)
//	{
//		for (j = 0; j < c; ++j)
//			if (map[i][j] < 0 || map[i][j] > 9) printf("%d ", map[i][j]);
//			else printf(" %d ", map[i][j]);
//		printf("\n");
//	}
}

void setup_graph()
{
	int i, j;
	memset(way, false, sizeof(way));
	for (i = 0; i < r; ++i)
		for (j = 0; j < c; ++j)
			if (map[i][j] >= 0)
			{
				if (i > 0 && map[i-1][j] >= 0) way[map[i][j]][map[i-1][j]] = true;
				if (i < r-1 && map[i+1][j] >= 0) way[map[i][j]][map[i+1][j]] = true;
				if (j > 0 && map[i][j-1] >= 0) way[map[i][j]][map[i][j-1]] = true;
				if (j < c-1 && map[i][j+1] >= 0) way[map[i][j]][map[i][j+1]] = true;
			}
}

bool try_insert(int tl, int tr)
{
	int i;
	int tl2;
	bool find;
	if (vst[tr]) return false;
	vst[tr] = true;
	if (rit[tr] == -1)
	{
		rit[tr] = tl;
		return true;
	}
	tl2 = rit[tr];
	find = false;
	for (i = 0; i < n && !find; ++i)
		if (way[tl2][i]) find = try_insert(tl2, i);
	if (find) rit[tr] = tl;
	return find;
}

void match()
{
	int i, j;
	int mat, ans;
	bool find;
	mat = 0;
	for (i = 0; i < n; ++i) rit[i] = -1;
	for (i = 0; i < n; ++i)
	{
		memset(vst, false, sizeof(vst));
		find = false;
		for (j = 0; j < n && !find; ++j)
			if (way[i][j]) find = try_insert(i, j);
		if (find) mat++;
	}
	ans = n - mat + mat / 2;
	cout << ans << endl;
}

void conduct()
{
	setup_graph();
	match();
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		//printf("time=%d\n", time);
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

