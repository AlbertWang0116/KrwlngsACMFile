#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 510
int rit[N], way[N][N];
int n, m;
bool vst[N];

void input()
{
	int i, j;
	int tr, tc, cnt;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; ++i) way[i][0] = 0;
	for (i = 0; i < m; ++i)
	{
		scanf("%d %d", &tr, &tc);
		--tr;
		--tc;
		way[tr][++way[tr][0]] = tc;
	}
	for (i = 0; i < n; ++i) std::sort(way[i]+1, way[i]+way[i][0]+1);
	cnt = 0;
//	for (i = 0; i < n; ++i)
//		for (j = 1; j <= way[i][0]; ++j) 
//		{
//			if (j != way[i][0] && way[i][j] >= way[i][j+1]) break;
//			printf("cnt=%d way[%d][%d]=%d\n", ++cnt, i, j, way[i][j]);
//		}
}

bool try_find(int tl, int tr)
{
	int tl2;
	bool find;
	int i;
	if (vst[tr]) return false;
	vst[tr] = true;
	if (rit[tr] == -1)
	{
		rit[tr] = tl;
		return true;
	}
	tl2 = rit[tr];
	find = false;
	for (i = 1; i <= way[tl2][0] && !find; ++i) find = try_find(tl2, way[tl2][i]);
	if (find) rit[tr] = tl;
	return find;
}

void conduct()
{
	int i, j;
	bool find;
	int ans;
	ans = 0;
	for (i = 0; i < n; ++i) rit[i] = -1;
	for (i = 0; i < n; ++i)
	{
		find = false;
		memset(vst, false, sizeof(vst));
		for (j = 1; j <= way[i][0] && !find; ++j) find = try_find(i, way[i][j]);
		if (find) ans++;
	}
	cout << ans;
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

