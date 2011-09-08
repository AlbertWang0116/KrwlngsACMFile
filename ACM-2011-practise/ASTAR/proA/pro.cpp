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

struct node { int posx, posy, ori, verse; bool put; };

int dx[4]{ 0, 1, 0 ,-1};
int dy[4]{ 1, 0, -1, 0};
int dia[20][20];
int way[100][100], ori[100][100], sign[100][100];
node ele[100];
int n, ans;

void input()
{
	int i, j;
	char tmp[10];
	for (i = 0; i < n; ++i)
	{
		scanf("%s", tmp);
		for (j = 0; j < 4; ++j) sign[i][j] = tmp[j] - 'A';
	}
	memset(way, 0, sizeof(way));
	for (i = 0; i < n; ++i)
		for (j = 0; j < 4; ++j) { way[sign[i][j]][0]++; way[sign[i][j]][way[sign[i][j]][0]] = i; ori[sign[i][j]][way[sign[i][j]][0]] = j; }
	for (i = 0; i < n; ++i) ele[i].put = false;
	for (i = 0; i < 20; ++i) for (j = 0; j < 20; ++j) dia[i][j] = -1;
}

bool judge(int idx, int posx, int posy, int ori, int verse)
{
	int i, tmp, idx2;
	for (i = 0; i < 4; ++i)
	{
		tmp = (ori + i) % 4; idx2 = dia[posx+dx[tmp]][posy+dy[tmp]]; if (idx2 == -1) continue;
		tmp = (tmp + 6 - ele[idx2].ori) % 4; if (sign[idx][i] != sign[idx2][tmp]) return false;
	}
	return true;
}

void tryput(int lst, int dpt)
{
	int idx, tmp;
	int i, j, k;
	int tori, posx, posy, verse;
	if (ans < dpt) ans = dpt; if (ans == n) return;
	for (i = lst; i < n; ++i) if (ele[i].put)
		for (j = 0; j < 4; ++j)
		{
			posx = ele[i].posx + dx[(ele[i].ori + j * ele[i].verse + 4) % 4];
			posy = ele[i].posy + dy[(ele[i].ori + j * ele[i].verse + 4) % 4];
			if (dia[posx][posy] >= 0) continue;
			tmp = sign[i][j];
			for (k = 1; k <= way[tmp][0]; ++k) if (way[tmp][k] >= lst && !ele[way[tmp][k]].put)
			{
				idx = way[tmp][k];
				tori = (ele[i].ori + j * ele[i].verse - ori[tmp][k] + 10) % 4;
				verse = 1;
				if (judge(idx, posx, posy, tori, verse))
				{
					ele[idx].put = true; ele[idx].posx = posx; ele[idx].posy = posy; ele[idx].verse = verse; ele[idx].ori = tori; dia[posx][posy] = idx;
					tryput(lst, dpt+1);
					ele[idx].put = false; dia[posx][posy] = -1;
				}
				verse = -1; if (tori % 2 == 1) tori = (tori + 2) % 4;
				if (judge(idx, posx, posy, tori, verse))
				{
					ele[idx].put = true; ele[idx].posx = posx; ele[idx].posy = posy; ele[idx].verse = verse; ele[idx].ori = tori; dia[posx][posy] = idx;
					tryput(lst, dpt+1);
					ele[idx].put = false; dia[posx][posy] = -1;
				}
			}
		}
}

void conduct()
{
	int i;
	ans = 1;
	for (i = 0; i < n; ++i)
	{
		ele[i].put = true; ele[i].posx = 10; ele[i].posy = 10; ele[i].verse = 1; ele[i].ori = 0; dia[10][10] = i;
		tryput(i, 1);
		ele[i].put = false; dia[10][10] = -1;
	}
	printf("%d\n", ans);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF && n)
	{
		input();
		conduct();
	}
	fclose(stdin);
	fclose(stdout);
}

