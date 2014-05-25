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

#define N 70
#define M 12
double f[M][N], p[M];
int n;
const int lst[] = { 5, 12, 22, 29, 33, 38, 42, 46, 50, 55 };

void conduct() {
	int i, j, k;
	double sum;
	for (i=1; i<=6; ++i) scanf("%lf", &p[i]);
	memset(f, 0, sizeof(f)); f[0][0]=1.0;
	for (i=0; i<10; ++i) for (j=0; j<=54; ++j) for (k=1; k<=6; ++k) f[i+1][j+k]+=f[i][j]*p[k];
	for (i=0; i<10; ++i) {
		for (sum=j=0; j<=10; ++j) sum+=f[j][lst[i]];
		printf("%d: %.1f%%\n", lst[i], sum*100.0);
	}
}

int main() {
	int time; scanf("%d", &time);
	while (time--) {
		conduct();
		if (time) printf("\n");
	}
}
