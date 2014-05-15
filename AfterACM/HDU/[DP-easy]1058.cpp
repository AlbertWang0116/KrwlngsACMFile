#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<string>
using namespace std;

#define N 5842
int ret[N];
int n;
const char *th="th", *st="st", *nd="nd", *rd="rd";

const char* get_str(int x) {
	if (x%10<1 || x%10>3 || (x%100/10==1)) return th;
	if (x%10==1) return st;
	if (x%10==2) return nd;
	if (x%10==3) return rd;
}

void conduct() {
	int i;
	long long j;
	set<long long> dic; dic.clear(); dic.insert(1LL);
	set<long long>::iterator it;
	for (i=0; i<N; ++i) {
		it=dic.begin(); j=*it; dic.erase(it);
		if (dic.find(j*2)==dic.end()) dic.insert(j*2);
		if (dic.find(j*3)==dic.end()) dic.insert(j*3);
		if (dic.find(j*5)==dic.end()) dic.insert(j*5);
		if (dic.find(j*7)==dic.end()) dic.insert(j*7);
		ret[i]=j;
	}
}

int main() {
	conduct();
	while (scanf("%d", &n)!=EOF && n) {
		printf("The %d%s humble number is %d.\n", n, get_str(n), ret[n-1]);
	}
	return 0;
}
