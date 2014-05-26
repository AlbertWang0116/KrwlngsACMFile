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

#define N 2100000
#define L (1<<24)
#define M 10
int que[N];
char f[L];
int s[M][M];
int off[M], len[M], a[M];
char str[M];
int n;
const char dic[] = { 'A', 'C', 'G', 'T' };

inline int getmin(int x, int y) { return x<y?x:y; }

int get_id(char x) {
	for (int i=0; i<4; ++i) if (x==dic[i]) return i;
}

void conduct() {
	int i, j, k, status[4], head, tail, es;
	scanf("%d", &n);
	for (i=0; i<n; ++i) {
		scanf("%s", str); len[i]=strlen(str);
		for (j=0; j<len[i]; ++j) s[i][j]=get_id(str[j]);
	}
	for (off[0]=0, i=1; i<n; ++i) off[i]=off[i-1]+3;
	for (i=es=0; i<n; ++i) es+=(len[i]<<off[i]);
	f[0]=1;	
	for (que[0]=head=tail=0; head<=tail; ++head) {
		i=que[head]; if (es==i) break;
		for (j=0; j<n; ++j) a[j]=(7&(i>>off[j]));
		for (k=0; k<4; ++k) status[k]=i;
		for (j=0; j<n; ++j) if (a[j]<len[j]) status[s[j][a[j]]]+=(1<<off[j]);
		for (k=0; k<4; ++k) if (!f[status[k]]) { f[status[k]]=f[i]+1; que[++tail]=status[k]; }
	}
	printf("%d\n", f[es]-1);
	for (i=0; i<=tail; ++i) f[que[i]]=0;
}

int main() {
	memset(f, 0, sizeof(f));
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
