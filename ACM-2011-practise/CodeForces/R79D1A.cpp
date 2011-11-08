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

#define N 200010
int seq[N], cnt[N], use[N];
char str[N];
int k;

int cmp(const int &i, const int &j) { return cnt[i] < cnt[j]; }

void conduct()
{
	int i, n, ret;
	n = strlen(str); memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < n; ++i) cnt[str[i]-'a']++;
	for (i = 0; i < 26; ++i) seq[i] = i; sort(seq, seq+26, cmp);
	memset(use, 1, sizeof(use));
	for (i = 0; i < 26; ++i) if (cnt[seq[i]] <= k) { use[seq[i]] = 0; k -= cnt[seq[i]]; } else break;
	ret = 0; for (i = 0; i < 26; ++i) if (use[i] && cnt[i]) ret++; printf("%d\n", ret);
	for (i = 0; i < n; ++i) if (use[str[i]-'a']) printf("%c", str[i]); printf("\n");
}

int main()
{
	while (scanf("%s%d", str, &k) != EOF) conduct();
	return 0;
}
