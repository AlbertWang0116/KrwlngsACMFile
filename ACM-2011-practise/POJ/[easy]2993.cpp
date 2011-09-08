#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define N 9
char map[N][N];

void insert_map(char* cmd, int id)
{
	int x, y;
	int trs = 'a' - 'A';
	if (strlen(cmd) == 2)
	{
		x = cmd[0] - 'a';
		y = '8' - cmd[1];
		map[y][x] = 'P' + trs * id;
	}
	else
	{
		x = cmd[1] - 'a';
		y = '8' - cmd[2];
		map[y][x] = cmd[0] + trs * id;
	}
}

void input()
{
	int i, j;
	char st[100];
	char* pnt;
	for (i = 0; i < 8; ++i)
		for (j = 0; j < 8; ++j)
			if ((i + j) % 2) map[i][j] = ':';
			else map[i][j] = '.';
	for (i = 0; i < 2; ++i)
	{
		scanf("%s", st);
		if (strcmp(st, "White:") == 0) j = 0;
		else j = 1;
		scanf("%s", st);
		pnt = strtok(st, ",");
		insert_map(pnt, j);
		while ((pnt = strtok(NULL, ",")) != NULL) insert_map(pnt, j);
	}
}

void print_line()
{
	int i;
	for (i = 0; i < 8; ++i) cout << "+---";
	cout << "+" << endl;
}

void output()
{
	int i, j;
	int trs = ':' - '.';
	for (i = 0; i < 8; ++i)
	{
		print_line();
		for (j = 0; j < 8; ++j) cout << "|" << (char)('.' + ((i+j)%2) * trs) << map[i][j] << (char)('.' + ((i+j)%2) * trs);
		cout << "|" << endl;
	}
	print_line();
}	

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	input();
	output();
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
