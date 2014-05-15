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

#define N 120000
int vst[N];
int a[6];

void conduct() {
	int i, j, k;
	memset(vst, 0, sizeof(vst)); vst[0]=1;
	for (i=0; i<6; ++i) 
		for (j=N; ~j; --j) if (vst[j])
			for (k=1; k<=a[i] && j+(i+1)*k<N && !vst[j+(i+1)*k]; ++k) vst[j+(i+1)*k]=1;
	for (j=i=0; i<6; ++i) j+=(i+1)*a[i];
	if ((j&1)==0 && vst[j/2]) printf("Can be divided.\n");
	else printf("Can't be divided.\n");
}

int main() {
	int time=0;
	while (scanf("%d%d%d%d%d%d", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5])!=EOF && (a[0]||a[1]||a[2]||a[3]||a[4]||a[5])) {
		printf("Collection #%d:\n", ++time);
		conduct();
		printf("\n");
	}
	return 0;
}
