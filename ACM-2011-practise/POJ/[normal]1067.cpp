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

int a, b;

void conduct() {
	if (a == 0 && b == 0) { printf("0\n"); return; }
	if (a > b) { a = a ^ b; b = a ^ b; a = a ^ b; }
	double k = floor((double)a*2/(1.0+sqrt(5.0))) + 1;
	if ((int)(k*(1.0+sqrt(5.0))/2.0) != a) printf("1\n"); 
	else if (b != (int)(a+k)) printf("1\n"); else printf("0\n");
}

int main() {
	while (scanf("%d%d", &a, &b) != EOF) conduct();
	return 0;
}
