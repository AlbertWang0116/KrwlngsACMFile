#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

#define N 30
int vst[N][N][N];
long long f[N][N][N];
int a, b, c;

long long w(int a, int b, int c) {
	if (a<=0 || b<=0 || c<=0) return 1;
	if (a>20 || b>20 || c>20) return w(20, 20, 20);
	if (vst[a][b][c]) return f[a][b][c]; vst[a][b][c]=1;
	if (a<b && b<c) f[a][b][c]=w(a, b, c-1)+w(a, b-1, c-1)-w(a, b-1, c);
	else f[a][b][c]=w(a-1, b, c)+w(a-1, b-1, c)+w(a-1, b, c-1)-w(a-1, b-1, c-1);
	return f[a][b][c];
}

int main() {
	memset(vst, 0, sizeof(vst));
	while (scanf("%d%d%d", &a, &b, &c) && (~a || ~b || ~c)) {
		printf("w(%d, %d, %d) = ", a, b, c);
		cout << w(a, b, c) << endl;
	}
	return 0;
}
