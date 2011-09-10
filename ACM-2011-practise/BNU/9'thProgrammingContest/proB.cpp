#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 20
#define M 60
char cha[M], name[N][M], str[N][M], cmd[M];
int n;

void input()
{
	int i;
	scanf("%s", cha); scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%s %s", str[i], name[i]);
	scanf("%s", cmd);
}

void conduct()
{
	int i, j;
	int ans;
	ans = -1;
	for (i = 0; i < strlen(cmd) && ans == -1; ++i)
		for (j = 0; j < n; ++j)
			if (strncmp(cmd+i, str[j], strlen(str[j])) == 0) {ans = j; break;}
	cout << cha << endl;
	if (ans >= 0) cout << name[ans] << endl;
	else cout << "Nothing Happened" << endl;
	cout << endl;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

