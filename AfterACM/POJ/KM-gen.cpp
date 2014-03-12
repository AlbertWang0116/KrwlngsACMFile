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

int main() {
	int i, j;
	printf("300\n");
	for (i=300; i; --i) {
		for (j=300; j>=i; --j) printf("%d ", i*j);
		for (; j; --j) printf("%d ", 0);
		printf("\n");
	}
}
