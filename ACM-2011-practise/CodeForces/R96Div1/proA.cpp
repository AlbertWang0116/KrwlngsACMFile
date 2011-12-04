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

char str[1010];

int reverse(int x) {
	int ret, i;
	for (ret = i = 0; i < 8; ++i)
		if (x & (1 << i)) ret |= (1 << (7-i));
	return ret;
}

void conduct() {
	int i, j, ret, n, m;
	gets(str); n = strlen(str); m = 127;
	for (i = j = 0; i < n; ++i) {
		ret = j - reverse(str[i]);
		if (ret < 0) ret += 256;
		printf("%d\n", ret); j = reverse(str[i]);
	}
}

int main() {
	conduct();
	return 0;
}
