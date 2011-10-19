#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;

char str1[1010], str2[1010];

int cmp(char a, char b) {
	if (a >= 'a') a -= 'a' - 'A';
	if (b >= 'a') b -= 'a' - 'A';
	if (a > b) return 1; else if (a < b) return -1;
	return 0;
}

int main()
{
	int i, ret;
	while (scanf("%s", str1) != EOF) {
		scanf("%s", str2);
		for (i = 0; i < strlen(str1); ++i) if (ret = cmp(str1[i], str2[i])) break;
		printf("%d\n", ret);
	} return 0;
}
