#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 10010
int seq[N];
int n;

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%d", &seq[i]);
}

void conduct()
{
	std::sort(seq, seq+n);
	cout << seq[n/2];
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	input();
	conduct();
	//fclose(stdin);
	//fclose(stdout);
}

