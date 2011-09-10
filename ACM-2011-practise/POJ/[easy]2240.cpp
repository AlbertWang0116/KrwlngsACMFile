#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define MINDIS -1
#define M 100
#define N 40
char name[N][M];
int way[N][N], brch[N];
int n;
double len[N][N], dis[N];

int get_index(char *checked)
{
	int i;
	for (i = 0; i < n; ++i)
		if (strcmp(name[i], checked) == 0) return i;
}

void input()
{
	int i, m;
	char stt[M], des[M];
	double len2;
	int sttnum, desnum;
	for (i = 0; i < n; ++i) scanf("%s", name[i]);
	for (i = 0; i < n; ++i) brch[i] = 0;
	scanf("%d", &m);
	for (i = 0; i < m; ++i)
	{
		scanf("%s %lf %s", stt, &len2, des);
		sttnum = get_index(stt);
		desnum = get_index(des);
		way[sttnum][brch[sttnum]] = desnum;
		len[sttnum][brch[sttnum]] = len2;
		++brch[sttnum];
	}
}

void conduct()
{
	int i, j, k, des;
	bool change;
	for (i = 0; i < n; ++i) dis[i] = MINDIS;
	for (i = 0; i < brch[0]; ++i)
		if (dis[way[0][i]] < len[0][i]) dis[way[0][i]] = len[0][i];
	for (i = 0; i < n; ++i)
	{
		change = false;
		for (j = 0; j < n; ++j)
		{
			if (dis[j] < 0) continue;
			for (k = 0; k < brch[j]; ++k)
			{
				des = way[j][k];
				if (dis[des] < dis[j] * len[j][k])
				{
					change = true;
					dis[des] = dis[j] * len[j][k];
				}
			}
		}
		if (!change) break;
	}
	if (i == n) cout << "Yes" << endl;
	else cout << "No" << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int test_num = 0;
	while (cin >> n && n)
	{
		cout << "Case " << ++test_num << ": ";
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

