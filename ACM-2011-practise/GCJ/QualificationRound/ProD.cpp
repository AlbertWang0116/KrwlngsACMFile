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
int seq[N];
int n, cs;
float ans;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int time;
	int i;
	scanf("%d", &time);
	for (cs = 1; cs <= time; ++cs)
	{
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) scanf("%d", &seq[i]);
		ans = 0;
		for (i = 1; i <= n; ++i) if (seq[i] != i) ans += 1;
		printf("Case #%d: %.6f\n", cs, ans);
	}
	fclose(stdin);
	fclose(stdout);
}

