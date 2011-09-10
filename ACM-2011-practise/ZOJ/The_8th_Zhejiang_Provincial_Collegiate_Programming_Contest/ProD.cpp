#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 200
#define M 200
char itv[N][N];
int pos[N], lft[M], rit[10];
int n, m;

void init()
{
	int i;
	memset(lft, 0, sizeof(lft));
	for (i = '0'; i <= '9'; ++i) lft[i] = 1;
	for (i = 'A'; i <= 'Z'; ++i) lft[i] = 2;
	for (i = 'a'; i <= 'z'; ++i) lft[i] = 3;
	rit[1] = '1';
	rit[2] = 'A';
	rit[3] = 'a';
}

void input()
{
	char str[N];
	int i, j;
	scanf("%s", str);
	scanf("%d", &m);
	n = 0;
	for (i = strlen(str)-1; i >= 0; --i)
		if (lft[str[i]] > 0)
		{
			for (j = i + 1; j < strlen(str) && !lft[str[j]]; ++j) itv[n][j-i-1] = str[j];
			itv[n][j-i-1] = '\0';
			n++;
			pos[n] = str[i];
		}
	for (i = 0; i < strlen(str) && !lft[str[i]]; ++i) itv[n][i] = str[i];
	itv[n][i] = '\0';
}

void carry(int code)
{
	n++;
	pos[n] = rit[code];
	strcpy(itv[n], itv[n-1]);
	if (n == 1) itv[n][strlen(itv[n])-1] = '\0';
	if (n == 1 && pos[1] == '1') pos[1] = '0';
	itv[n-1][0] = '\0';
}

void print()
{
	int i;
	for (i = n; i > 0; --i)
	{
		cout << itv[i];
		cout << (char)pos[i];
	}
	cout << itv[0] << endl;
}

void conduct()
{
	int i;
	int add, pre;
	//printf("m=%d n=%d\n", m, n);
	while (m > 0)
	{
		//printf("m=%d n=%d\n", m, n);
		if (n > 0)
		{
			add = 1;
			for (i = 1; i <= n; ++i)
			{
				pre = lft[pos[i]];
				pos[i] += add;
				if (pre != lft[pos[i]])
				{
					pos[i] = rit[pre];
					if (pos[i] == '1') pos[i] = '0';
					add = 1;
				}
				else add = 0;
			}
			if (add) carry(lft[pos[n]]);
		}
		else
		{
			itv[0][strlen(itv[0])-1]++;
			if (lft[itv[0][strlen(itv[0])-1]] > 0) carry(lft[itv[0][strlen(itv[0])-1]]);
		}
		print();
		m--;
	}
	cout << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	init();
	int time;
	scanf("%d", &time);
	while (time > 0)
	{
		input();
		conduct();
		time--;
	}
	//fclose(stdin);
	//fclose(stdout);
}

