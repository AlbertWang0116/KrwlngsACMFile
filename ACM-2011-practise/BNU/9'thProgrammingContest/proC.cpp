#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time, n, m;
	scanf("%d", &time);
	while (time--)
	{
		scanf("%d %d", &n, &m);
		if (n == 1 && m == 1) printf("Alice\n");
		else printf("Bob\n");
	}
//	fclose(stdin);
//	fclose(stdout);
}

