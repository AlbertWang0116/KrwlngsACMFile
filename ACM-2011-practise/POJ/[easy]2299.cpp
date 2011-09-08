#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 500010
int seq[N], tseq[N];
int n;
long long ans;

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%d", &seq[i]);
	//printf("n=%d\n", n);
	//for (i = 0; i < n; ++i) printf("seq[i]=%d\n", seq[i]);
}

void m_sort(int x, int y)
{
	int i, j, k;
	int mid;
	if (x >= y) return;
	mid = (x + y) / 2;
	m_sort(x, mid);
	m_sort(mid+1, y);
	i = x;
	j = mid + 1;
	k = x;
	while (k <= y)
	{
		while (k <= y && i <= mid && (j > y || seq[i] <= seq[j])) tseq[k++] = seq[i++];
		ans += mid - i + 1;
		tseq[k++] = seq[j++];
	}
	for (i = x; i <= y; ++i) seq[i] = tseq[i];
}

void conduct()
{
	ans = 0;
	m_sort(0, n-1);
	cout << ans << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF && n)
	{
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

