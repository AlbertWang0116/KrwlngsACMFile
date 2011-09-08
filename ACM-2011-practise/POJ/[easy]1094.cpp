#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define N 30
int pre[N], pre2[N], fwd[N], way[N][N], queue[N];
bool vst[N];
int n, m;

int topology()
{
	int i, j;
	int cnt, index, ret;
	for (i = 0; i < n; ++i)	pre2[i] = pre[i];
	memset(vst, false, sizeof(vst));
	ret = 0;
	for (i = 0; i < n; ++i)
	{
		cnt = 0;
		for (j = 0; j < n; ++j)
			if (!vst[j] && !pre2[j]) {cnt++; index = j;}
		if (cnt == 0) return 0;
		if (cnt > 1) ret = -1;
		queue[i] = index;
		vst[index] = true;
		for (j = 0; j < fwd[index]; ++j) pre2[way[index][j]]--;
	}
	if (ret == 0) return 1;
	else return 2;
}

bool try_ans(int rlt)
{
	int i;
	int ret;
	ret = topology();
	//printf("ret=%d\n", ret);
	if (ret == 0) { cout << "Inconsistency found after " << rlt << " relations." << endl; return true;}
	else if (ret == 1) 
	{ 
		cout << "Sorted sequence determined after " << rlt << " relations: "; 
		for (i = 0; i < n; ++i) cout << (char)(queue[i]+'A');
		cout << "." << endl;
		return true;
	}
	return false;
}

void input()
{
	int i;
	int tpre, tfwd;
	char info[30];
	bool find;
	//printf("brefore input!\n");
	memset(pre, 0, sizeof(pre));
	memset(fwd, 0, sizeof(fwd));
	find = try_ans(0);
	gets(info);
	for (i = 0; i < m; ++i)
	{	
		gets(info);
		if (find) continue;
		tpre = info[0] - 'A';
		tfwd = info[2] - 'A';
		way[tpre][fwd[tpre]++] = tfwd;
		pre[tfwd]++;
		find = try_ans(i+1);
	}
	if (!find) cout << "Sorted sequence cannot be determined." << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while (cin >> n && cin >> m && (n || m)) input();
	//fclose(stdin);
	//fclose(stdout);
}

