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

double n;
const double eps = 1e-9;

void conduct() {
	while (n - 18.0 > eps) n/=18.0;
	if (n - 9.0 < eps) printf("Stan wins.\n");
	else printf("Ollie wins.\n");
}

int main() {
	while (scanf("%lf", &n) != EOF) conduct();
	return 0;
}
