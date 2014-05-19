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

#define N 30
int f[N][N][N], vst[N][N][N];

int w(int a, int b, int c) {
	if (a<=0 || b<=0 || c<=0) return 1;
	if (a>20 || b>20 || c>20) return w(20, 20, 20);
	if (vst[a][b][c]) return f[a][b][c]; vst[a][b][c]=1;
	if (a<b && a<c) f[a][b][c]=w(a, b, c-1)+w(a, b-1, c-1)-w(a, b-1, c);
	else f[a][b][c]=w(a-1, b, c)+w(a-1, b-1, c)+w(a-1, b, c-1)-w(a-1, b-1, c-1);
	return f[a][b][c];
}

int main() {
	int a, b, c;
	memset(vst, 0, sizeof(vst));
	while (scanf("%d%d%d", &a, &b, &c)!=EOF && (~a||~b||~c))
		printf("w(%d, %d, %d) = %d\n", a, b, c, w(a, b, c));
	return 0;
}
