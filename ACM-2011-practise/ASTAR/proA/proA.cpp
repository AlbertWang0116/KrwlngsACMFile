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

#define N 3010
long long mst[N];
int a[N], b[N];
int n;

int getmax(int x, int y) { return x > y ? x : y;}

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%d %d", &a[i], &b[i]);
}

void conduct()
{
	int i, j;
	long long tot1, tot2, k, l;
	mst[n] = 0; mst[n-1] = getmax(a[n-1], b[n-1]);
	for (i = n-2; i >= 0; --i)
	{
		k = 0; l = 0; mst[i] = 0; tot1 = 0; tot2 = 0;
		for (j = i; j < n; ++j) 
		{ 
			k += a[j]; l += b[j]; 
			tot1 += k; tot2 += l;
			mst[i] = getmax(mst[i], getmax(tot1, tot2) + mst[j+1]);
		}
	}
	printf("%lld\n", mst[0]);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

