#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 100010
int ref[N], mat[N][6];
int n;

int* get_lst(int* seq1, int* seq2)
{
	int i;
	for (i = 0; i < 6; ++i)
	{
		if (seq1[i] < seq2[i]) return seq1;
		if (seq2[i] < seq1[i]) return seq2;
	}
	return seq1;
}

void input()
{
	int i, j;
	int seq[12], seq2[12];
	int *lst;
	scanf("%d", &n);
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < 6; ++j) scanf("%d", &seq[j]);
		for (j = 6; j < 12; ++j) seq[j] = seq[j-6];
		for (j = 0; j < 6; ++j) seq2[j] = seq[5-j];
		for (j = 6; j < 12; ++j) seq2[j] = seq2[j-6];
		lst = seq;
		for (j = 1; j < 6; ++j) lst = get_lst(lst, seq+j);
		for (j = 0; j < 6; ++j) lst = get_lst(lst, seq2+j);
		for (j = 0; j < 6; ++j) mat[i][j] = lst[j];
	}
	for (i = 0; i < n; ++i) ref[i] = i;
	//for (i = 0; i < n; ++i)
	//{
		//printf("mat[%d] = ", i);
		//for (j = 0; j < 6; ++j) printf("%d ", mat[i][j]);
		//printf("\n");
	//}
}

int cmp(int* seq1, int* seq2)
{
	int i;
	for (i = 0; i < 6; ++i)
	{
		if (seq1[i] < seq2[i]) return -1;
		if (seq1[i] > seq2[i]) return 1;
	}
	return 0;
}

void q_sort(int x, int y)
{
	if (x >= y) return;
	int i, j;
	int k;
	i = rand() % (y - x) + x;
	k = ref[i];
	ref[i] = ref[x];
	i = x;
	j = y;
	while (i < j)
	{
		while (i < j && cmp(mat[ref[j]], mat[k]) >= 0) --j;
		ref[i] = ref[j];
		while (i < j && cmp(mat[ref[i]], mat[k]) <= 0) ++i;
		ref[j] = ref[i];
	}
	ref[i] = k;
	q_sort(x, i-1);
	q_sort(j+1, y);
}

void conduct()
{
	int i;
	q_sort(0, n-1);
	//for (i = 0; i < n; ++i) printf("ref[%d] = %d\n", i, ref[i]);
	for (i = 0; i < n-1; ++i)
		if (!cmp(mat[ref[i]], mat[ref[i+1]])) break;
	if (i < n-1) cout << "Twin snowflakes found." << endl;
	else cout << "No two snowflakes are alike." << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	input();
	conduct();
	//fclose(stdin);
	//fclose(stdout);
}

