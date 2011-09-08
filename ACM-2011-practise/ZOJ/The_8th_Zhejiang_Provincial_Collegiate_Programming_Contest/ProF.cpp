#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 110
#define M 30
char name[N][M], frt[M];
int n, idx;

void input()
{
	int i;
	scanf("%d", &n);
	scanf("%s", frt);
	for (i = 0; i < n; ++i)
	{
		scanf("%s", name[i]);
		if (!strcmp(name[i], frt)) idx = i;
	}
}

void conduct()
{
	idx = (idx + n / 2) % n;
	cout << name[idx] << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}


