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

#define N 1000010
int pos[N], next[N];
int n, k;

void conduct() {
	int cur, val;
	scanf("%d%d", &n, &k);
	pos[0] = pos[1] = 1; next[1] = 1;
	while (pos[pos[0]] < n) {
		pos[pos[0]+1] = pos[pos[0]]+pos[next[pos[0]]];
		val = (pos[pos[0]+1]-1) / k; next[pos[0]+1] = next[pos[0]];
		while (pos[next[pos[0]+1]] <= val) next[pos[0]+1]++;
		++pos[0];
	} if (pos[pos[0]] == n) { printf("lose\n"); return; } cur = pos[0];
//	printf("lose:"); for (cur = 1; cur <= pos[0]; ++cur) printf("%d ", pos[cur]); printf("\n"); 
	while (1) {
		while (pos[cur] > n) --cur;
		if (pos[cur] == n) { printf("%d\n", pos[cur]); return; }
		n -= pos[cur]; cur = next[cur];
	}
}

int main() {
	int time; scanf("%d", &time);
	for (int i = 1; i <= time; ++i) {
		printf("Case %d: ", i);
		conduct();
	} return 0;
}
