#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define N 2010
#define MAX 10
int n;
char pnt[N][7];
int dis[N][N], dis2[N];
bool vst[N];

int get_dis(int x, int y)
{
	int i;
	int ret = 0;
	for (i = 0; i < 7; ++i)
		if (pnt[x][i] != pnt[y][i]) ret++;
	return ret;
}

void input()
{
	int i, j;
	for (i = 0; i < n; ++i) scanf("%s", pnt[i]);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			dis[i][j] = get_dis(i, j);
	for (i = 0; i < n; ++i) dis2[i] = dis[0][i];
	for (i = 0; i < n; ++i) vst[i] = true;
	vst[0] = false;
}

void conduct()
{
	int i, j;
	int index, lst, ans;
	for (i = 1; i < n; ++i)
	{
		lst = MAX;
		for (j = 1; j < n; ++j)
			if (vst[j] && dis2[j] < lst) { index = j; lst = dis2[j];}
		vst[index] = false;
		for (j = 1; j < n; ++j)
			if (vst[j] && dis2[j] > dis[index][j]) dis2[j] = dis[index][j];
	}
	ans = 0;
	for (i = 1; i < n; ++i) ans += dis2[i];
	cout << "The highest possible quality is 1/" << ans << "." << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while (cin >> n && n)
	{
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

