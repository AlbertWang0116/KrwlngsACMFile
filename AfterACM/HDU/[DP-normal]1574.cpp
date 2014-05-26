#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<climits>
#include<string>
using namespace std;

#define OFF 15000
#define N 31000
int f[N], vst[N];
int n;

void conduct() {
	int i, j, k, l, ans;
	scanf("%d", &n);
	set<int> dic; dic.clear();
	memset(f, 0x80, sizeof(f)); memset(vst, 0, sizeof(vst)); f[OFF]=0; vst[OFF]=1; dic.insert(OFF);
	set<int>::iterator it;
	for (i=0; i<n; ++i) {
		scanf("%d%d%d", &j, &k, &l); k+=OFF;
		if (j>0) {
			it=dic.end();
			do {
				it--;
				if (*it<=k) 
					if (!vst[*it+j]) { f[*it+j]=f[*it]+l; vst[*it+j]=1; dic.insert(*it+j); }
					else if (f[*it+j]<f[*it]+l) f[*it+j]=f[*it]+l;
			} while (it!=dic.begin());
		} else if (j<0) {
			for (it=dic.begin(); it!=dic.end(); it++)
				if (*it>=k)
					if (!vst[*it+j]) { f[*it+j]=f[*it]+l; vst[*it+j]=1; dic.insert(*it+j); }
					else if (f[*it+j]<f[*it]+l) f[*it+j]=f[*it]+l;
		}
	}
	for (ans=i=0; i<N; ++i) if (f[i]>ans) ans=f[i];
	printf("%d\n", ans);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
