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

int a[110], b[110][110];
int p[5];
map<int, int> acc[5];

void full(int idx)
{
	int i, des;
	map<int, int>::iterator l, k;
	for (i = -50; i <= 50; ++i) if (i != 0) acc[idx].insert(pair<int, int>(b[p[idx]+50][i+50], 1));
	for (l = acc[idx].begin(); l != acc[idx].end(); ++l)
		for (i = -50; i <= 50; ++i) if (i != 0)
		{
			des = l->first + b[p[idx+1]+50][i+50];
			k = acc[idx+1].find(des);
			if (k != acc[idx+1].end()) k->second += l->second;
			else acc[idx+1].insert(pair<int, int>(des, l->second));
		}
}

int main()
{
	int i, j, des, ans;
	map<int, int>::iterator k, l;
	for (i = 0; i <= 100; ++i) a[i] = (i-50)*(i-50)*(i-50);
	for (i = 0; i <= 100; ++i) for (j = 0; j <= 100; ++j) b[i][j] = (i - 50) * a[j];
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	for (i = 0; i < 5; ++i) scanf("%d", &p[i]);
	full(0); full(2); ans = 0;
	for (l = acc[3].begin(); l != acc[3].end(); ++l)
		for (i = -50; i <= 50; ++i) if (i != 0)
		{
			des = l->first + b[p[4]+50][i+50];
			k = acc[1].find(-des);
			if (k != acc[1].end()) ans += l->second * k->second;
		}
	cout <<ans << endl;
//	fclose(stdin);
//	fclose(stdout);
}

