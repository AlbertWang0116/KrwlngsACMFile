#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 600
int n, m;
double seq[N];

void input()
{
	scanf("%d", &m);
}

void conduct()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf", &seq[i]);
	//for (i = 0; i < n; ++i) printf("seq[%d]=%.3f\n", i, seq[i]);
	std::sort(seq, seq+n);
	if (n % 2) printf("%.3f\n", seq[n/2]);
	else printf("%.3f\n", (seq[n/2]+seq[n/2-1])/2);
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		//printf("time=%d\n", time);
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

