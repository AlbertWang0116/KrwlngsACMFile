#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

char str[20], str2[20], trans[2];
int cnt;

void init()
{
	int i;
	cnt = 0;
	trans[0] = '(';
	trans[1] = ')';
	for (i = 0; i < strlen(str); ++i)
		if (str[i] == '?') cnt++;
}

bool judge()
{
	int i, lft;
	lft = 0;
	for (i = 0; i < strlen(str); ++i)
		if (str2[i] == '(') ++lft;
		else
		{
			--lft;
			if (lft < 0) return false;
		}
	if (lft > 0) return false;
//	cout << str2 << endl;
	return true;
}

void conduct()
{
	int i, j, k;
	int ans;
	ans = 0;
	for (i = 0; i < (1 << cnt); ++i)
	{
		k = 0;
		for (j = 0; j < strlen(str); ++j)
			if (str[j] == '?') str2[j] = trans[((i & (1 << k++)) > 0)];
			else str2[j] = str[j];
		if (judge()) ans++;
	}
	cout << ans << endl;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%s", str) != EOF)
	{
		init();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

