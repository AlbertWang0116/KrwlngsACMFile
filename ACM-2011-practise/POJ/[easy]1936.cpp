#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 100010
char pat[N], mat[N];

void conduct()
{
	int i, j;
	j = 0;
	for (i = 0; i < strlen(mat) && j < strlen(pat); ++i)
		if (mat[i] == pat[j]) ++j;
	if (j == strlen(pat)) cout << "Yes" << endl;
	else cout << "No" << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while (scanf("%s %s", pat, mat) != EOF) conduct();
	//fclose(stdin);
	//fclose(stdout);
}

