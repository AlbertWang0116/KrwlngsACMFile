#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define N 110
#define MAX 100000000
int n;
int dis[N][N], dis2[N];
bool vst[N];

void input()
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) scanf("%d", &dis[i][j]);
	for (i = 0; i < n; ++i) dis2[i] = dis[0][i];
	for (i = 0; i < n; ++i) vst[i] = true;
	vst[0] = false;
}

void conduct()
{
	int i, j;
	int lst, index, ans;
	for (i = 1; i < n; ++i)
	{
		lst = MAX;
		for (j = 1; j < n; ++j)
			if (vst[j] && lst > dis2[j]) { lst = dis2[j]; index = j;}
		vst[index] = false;
		for (j = 1; j < n; ++j)
			if (vst[j] && dis2[j] > dis[index][j]) dis2[j] = dis[index][j];
	}
	ans = 0;
	for (i = 1; i < n; ++i) ans += dis2[i];
	//for (i = 1; i < n; ++i) printf("dis2[%d]=%d\n", i, dis2[i]);
	cout << ans << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while (cin >> n)
	{
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

