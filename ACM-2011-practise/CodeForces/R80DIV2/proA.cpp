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

int a[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			 4, 4, 4, 4, 4, 4, 4, 4, 4, 15,
			 4, 0, 0, 0, 0 };

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) printf("%d\n", a[n-1]);
}
