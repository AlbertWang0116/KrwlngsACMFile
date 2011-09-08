#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

struct Node
{
	int idx, next;
};

#define N 100010
#define M 999997
#define L 30
#define MAX 1000000
int ss[30] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113};
int hash[M], stt[N][L], tot[L], seq[N];
Node node[N];
int n, m, nn;

int getmax(int x, int y) { return x > y ? x : y; }

int getpow(int x, int y)
{
	long long ret, base;
	ret = 0; base = 1;
	while (y > 0)
	{
		ret = (ret + base * (y % 2)) % M;
		y /= 2; base = (base * base) % M;
	}
	return (int)ret;
}

int get_hash()
{
	int ret;
	int i;
	ret = 0;
//	for (i = 0; i < m; ++i) ret = (ret + getpow(ss[i], tot[i])) % M;
	for (i = 0; i < m; ++i) ret = (ret + ss[i] * tot[i]) % M;
	return ret;
}

bool judge(int x)
{
	int i;
	for (i = 0; i < m; ++i)
		if (tot[i] != stt[x][i]) return false;
	return true;
}

bool all_zero()
{
	int i;
	for (i = 0; i < m; ++i)
		if (tot[i]) return false;
	return true;
}

void init()
{
	memset(tot, 0, sizeof(tot));
	memset(stt, 0, sizeof(stt));
	memset(hash, 0, sizeof(hash));
	nn = 1;
	node[1].idx = 0; node[1].next = 0;
}

void input()
{
	int i;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%d", &seq[i]);
	hash[get_hash()] = 1;
}

void conduct()
{
	int i, j;
	int lst, val, ans;
	ans = 0;
	for (i = 1; i <= n; ++i)
	{
		for (j = 0; j < m; ++j)
			if ((seq[i] & (1 << j)) > 0) tot[j]++;
		lst = MAX;
		for (j = 0; j < m; ++j)
			if (lst > tot[j]) lst = tot[j];
		if (lst > 0) for (j = 0; j < m; ++j) tot[j] -= lst;
		for (j = 0; j < m; ++j) stt[i][j] = tot[j];
		val = get_hash();
		for (j = hash[val]; j != 0; j = node[j].next)
			if (judge(node[j].idx)) { ans = getmax(ans, i - node[j].idx); break;}
		if (j == 0) { nn++; node[nn].idx = i; node[nn].next = hash[val]; hash[val] = nn;}
//		for (j = 0; j < m; ++j) printf("%d ", tot[j]);
//		printf("\n");
	}
	cout << ans << endl;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	init();
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

