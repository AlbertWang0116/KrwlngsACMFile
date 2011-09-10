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

#define N 1010
#define MAX 100000000
int seq[N];
int n, cs;

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%d", &seq[i]);
}

void conduct()
{
	int tot, judge, lst;
	int i;
	tot = 0; judge = 0; lst = MAX;
	for (i = 0; i < n; ++i)
	{
		if (seq[i] < lst) lst = seq[i];
		tot += seq[i];
		judge = (judge ^ seq[i]);
	}
	cout << "Case #" << cs << ": ";
	if (!judge) cout << tot - lst << endl;
	else cout << "NO" << endl;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	for (cs = 1; cs <= time; ++cs)
	{
		input();
		conduct();
	}
	fclose(stdin);
	fclose(stdout);
}

