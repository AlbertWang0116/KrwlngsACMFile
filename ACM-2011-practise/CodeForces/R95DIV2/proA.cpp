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

#define N 1010
char str[N];
int n;

bool check(char *str) {
	int i;
	for (i = 1; i < n; ++i) if (str[i] > 'Z') return 0;
	return 1;
}

void conduct() {
	int i;
	n = strlen(str);
	if (check(str)) for (i = 0; i < n; ++i) if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 'a'-'A'; else str[i] -= 'a'-'A';
	printf("%s\n", str);
}

int main() {
	while (scanf("%s", str) != EOF) conduct();
	return 0;
}
