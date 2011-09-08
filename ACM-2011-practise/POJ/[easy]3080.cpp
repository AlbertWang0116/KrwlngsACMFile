#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 20
#define M 70
char pat[N][M];
int com[N][M];
int n;

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%s", pat[i]);
	//for (i = 0; i < n; ++i) printf("%s\n", pat[i]);
}

void conduct()
{
	int i, j, k, l;
	int mst, index;
	for (i = 0; i < 60; ++i) com[0][i] = 60 - i;
	for (i = 1; i < n; ++i)
		for (j = 0; j < 60; ++j)
		{
			mst = 0;
			for (k = 0; k < 60; ++k)
			{
				for (l = 0; l < com[i-1][k]; ++l)
					if (pat[i][j+l] != pat[i-1][k+l]) break;
				if (mst < l) mst = l;
			}
			com[i][j] = mst;
		}
//	for (i = 0; i < n; ++i)
//	{
//		for (j = 0; j < 60; ++j) 
//			if (com[i][j] > 10) printf("%d ", com[i][j]);
//			else printf(" %d ", com[i][j]);
//		printf("\n");
//	}
	mst = 0;
	index = 0;
	for (i = 0; i < 60; ++i)
		if (mst < com[n-1][i] || (mst == com[n-1][i] && strncmp(pat[n-1]+index, pat[n-1]+i, mst) > 0)) { mst = com[n-1][i]; index = i;}
	if (mst < 3) cout << "no significant commonalities" << endl;
	else
	{
		//printf("mst=%d, index=%d\n", mst, index);
		for (i = 0; i < mst; ++i) cout << pat[n-1][index+i];
		cout << endl;
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

