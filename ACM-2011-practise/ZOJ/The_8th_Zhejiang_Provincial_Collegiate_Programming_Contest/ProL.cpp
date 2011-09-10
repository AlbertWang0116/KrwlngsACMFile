#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

int n;
int bit[32];

void init()
{
	int i;
	for (i = 0; i <= 30; ++i) bit[i] = (1 << i);
}

void conduct()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i <= 30; ++i)
		if (n < bit[i])
		{
			cout << i << endl;
			return;
		}
	cout << 31 << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	init();
	int time;
	scanf("%d", &time);
	while (time--) conduct();
	//fclose(stdin);
	//fclose(stdout);
}

