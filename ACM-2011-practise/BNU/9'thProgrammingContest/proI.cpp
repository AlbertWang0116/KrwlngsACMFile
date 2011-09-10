#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 1000001
#define M 100000000
int a[N], f4[N], f13[N];
int n;
char str[N][9];

void init()
{
	int i, j, tmp;
	a[0] = 0; f4[0] = 0; f13[0] = 0;
	a[1] = 9; f4[1] = 9; f13[1] = 0;
	a[2] = 80; f4[2] = 81; f13[2] = 1;
	for (i = 3; i < N; ++i)
	{
		f4[i] = f4[i-1] * 9 % M;
		f13[i] = (a[i-2] + 9 * f13[i-1]) % M;
		a[i] = (f4[i] - f13[i]);
		if (a[i] < 0) a[i] += M;
	}
	for (i = 1; i < N; ++i)
	{
		str[i][8] = '\0';
		tmp = a[i];
		j = 7;
		while (tmp > 0)
		{
			str[i][j--] = (tmp % 10) + '0';
			tmp /= 10;
		}
		while (j >= 0) str[i][j--] = '0';
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	init();
	int time;
	scanf("%d", &time);
	while (time--)
	{
		scanf("%d", &n);
		printf("%s\n", str[n]);
	}
//	fclose(stdin);
//	fclose(stdout);
}

