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
#define L 30
char str[N], vst[L];
int n, m;

void conduct()
{
	int i, j, cnt, r;
	scanf("%s", str); n = strlen(str); r = m;
	memset(vst, 0, sizeof(vst));
	for (cnt = i = 0; i < n/2+n%2; ++i) {
		if (str[i] != '?'&&str[n-i-1] != '?'&&str[i] != str[n-i-1])break;
		if ((str[i] != '?' && str[i]-'a' >= m) || (str[n-i-1] != '?' && str[n-i-1]-'a' >= m)) break;
		if (str[i] == '?' && str[n-i-1] == '?') { cnt++; continue; }
		if (str[i] == '?') str[i] = str[n-i-1];
		if (str[n-i-1] == '?') str[n-i-1] = str[i];
		if (!vst[str[i]-'a']) { vst[str[i]-'a'] = 1; r--; }
	} if (i < n/2+n%2 || cnt < r) { printf("IMPOSSIBLE\n"); return; }
	for (i = 0; i < n/2+n%2; ++i) if (str[i] == '?') {
		if (cnt > r) { str[i] = str[n-i-1] = 'a'; cnt--; }
		else for (j = 0; j < m; ++j) if (!vst[j]) { vst[j] = 1; str[i] = str[n-i-1] = 'a'+j; break; }
	} printf("%s\n", str);
}

int main()
{
	while (scanf("%d", &m) != EOF) conduct();
	return 0;
}
