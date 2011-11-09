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

int n, m, a, b;

void conduct() {
	int r, ca, cb;
	a--; b--;
	r = b/m-a/m+1; ca = a%m; cb = b%m;
	if (b == n-1) cb = m-1;
	if (r==1) { printf("1\n"); return; }
	if (r==2) {
		if (ca==0 && cb == m-1) printf("1\n");
		else printf("2\n"); return;
	} if (ca==0 && cb == m-1) printf("1\n");
	else if (cb == ca-1 || ca == 0 || cb == m-1) printf("2\n"); else printf("3\n");
}

int main() {
	while (scanf("%d%d%d%d", &n, &m, &a, &b) != EOF) conduct();
	return 0;
}
