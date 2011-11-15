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

int main() {
	int n, m;
	int time; scanf("%d", &time);
	while (time--) {
		scanf("%d%d", &n, &m);
		if (n%(m+1)) printf("Grass\n");
		else printf("Rabbit\n");
	} return 0;
}
