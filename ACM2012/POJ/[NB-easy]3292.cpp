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

#define M 1000010
int tag[M], ans[M], prm[M];
int n;

void erase(int x, int id) {
	int i, upr;
	tag[x] = 1; upr = (M-1) / x;
	for (i = id; i <= prm[0] && prm[i] <= upr; ++i) erase(x*prm[i], i);
}

void init() {
	int i, j, cur;
	memset(ans, 0, sizeof(ans)); memset(tag, 0, sizeof(tag)); prm[0] = 0;
	for (i = 5; i < M; i += 4) if (!tag[i]) {
		for (cur = 1; (M-1) / cur >= i; cur *= i) erase(cur*i, 1);
		prm[++prm[0]] = i; for (j = 1; j <= prm[0]; ++j) if ((M-1) / i >= prm[j]) tag[i*prm[j]] = 2; else break;
	} for (i = 0; i < M; ++i) if (tag[i] == 2) ans[i] = ans[i-1]+1; else ans[i] = ans[i-1];
}

int main() {
	init();
	while (scanf("%d", &n) != EOF && n) printf("%d %d\n", n, ans[n]);
	return 0;
}
