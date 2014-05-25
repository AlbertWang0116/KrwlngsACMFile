#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<map>
using namespace std;

#define N 5010
int f[3][N];
int n;
char str[N];

inline int getmin(int x, int y) { return x<y?x:y; }

void conduct() {
	int i, j;
	int *a, *b, *c, *d;
	scanf("%s", str);
	memset(f, 0, sizeof(f)); a=f[0]; b=f[1]; c=f[2];
	for (i=1; i<n; ++i) {
		for (j=0; i+j<n; ++j) {
			c[j]=getmin(b[j]+1, b[j+1]+1);
			if (str[j]==str[i+j]) c[j]=getmin(c[j], a[j+1]);
		}
		d=a; a=b; b=c; c=d;
	}
	printf("%d\n", b[0]);
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
