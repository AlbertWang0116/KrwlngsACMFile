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

#define N 110
#define M 1000010
int prm[M], tag[M], a[N];
char str[N];
int upr;

void checkzero(int* a) { if (a[1] == 0 && a[0] == 1) a[0] = 0; }

void erase(int x, int id) {
	int upr = (M-1) / x, i;
	tag[x] = 1;
	for (i = id; i < prm[0] && prm[i] <= upr; ++i) erase(x * prm[i], i);
}

void init() {
	int i, cur;
	memset(tag, 0, sizeof(tag)); prm[0] = 0;
	for (i = 2; i < M; ++i) if (!tag[i]) {
		for (cur = 1; (M-1)/cur >= i; cur *= i) erase(cur*i, 1);
		prm[++prm[0]] = i;
	}
}

int input() {
	scanf("%s", str); scanf("%d", &upr);
	memset(a, 0, sizeof(a)); a[0] = (strlen(str)+2) / 3; int tmp = strlen(str)-1;
	for (int i = 0; i < strlen(str); ++i) a[(tmp-i)/3+1] = a[(tmp-i)/3+1]*10 + (str[i]-'0');
	checkzero(a);
	if (!a[0] && !upr) return 0; return 1;
}

int valid(int x) {
	int i, j;
	for (i = a[0], j = 0; i > 0; --i) j = (j*1000+a[i]) % x;
	return j;
}

void conduct() {
	for (int i = 1; i <= prm[0] && prm[i] < upr; ++i)
		if (!valid(prm[i])) { printf("BAD %d\n", prm[i]); return; }
	printf("GOOD\n");
}

int main() {
	init();
	while (input()) conduct();
	return 0;
}
