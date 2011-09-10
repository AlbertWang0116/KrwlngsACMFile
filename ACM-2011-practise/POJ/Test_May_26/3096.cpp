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

int main()
{
	int i, j;
	char str[1000];
	int n;
	bool hash[10010];
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%s", str) != EOF && strcmp(str, "*"))
	{
		n = strlen(str);
		for (i = 1; i < n; ++i)
		{
			memset(hash, false, sizeof(hash));
			for (j = 0; j < n-i; ++j) if (hash[(str[j]-'A')*26+str[i+j]]) break; else hash[(str[j]-'A')*26+str[i+j]] = true;
			if (j < n-i) break;
		}
		if (i < n) printf("%s is NOT surprising.\n", str);
		else printf("%s is surprising.\n", str);
	}
//	fclose(stdin);
//	fclose(stdout);
}

