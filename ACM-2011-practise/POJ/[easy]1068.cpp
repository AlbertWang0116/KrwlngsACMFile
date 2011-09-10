#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
using namespace std;

#define N 100
int top, length, idx[N], cnt[N], pre[N], fwd[N];

void push(int value, int index)
{
	cnt[top] = value;
	idx[top] = index;
	top++;
}

int pop(int index)
{
	int ret = index - idx[top-1] + 1;
	cnt[top-1]--;
	if (cnt[top-1] == 0) --top;
	return ret;
}

void input()
{
	scanf("%d", &length);
	for (int i = 0; i < length; ++i) scanf("%d", &pre[i]);
}

void conduct()
{
	int cur, stt;
	top = 0;
	cur = 0;
	for (int i = 0; i < length; ++i)
	{
		stt = pre[i] - cur - 1;
		cur = pre[i];
		//printf("index:%d stt:%d\n", i, stt);
		if (stt == -1) fwd[i] = pop(i);
		else if (stt == 0) fwd[i] = 1;
		else
		{
			fwd[i] = 1;
			push(stt, i);
		}
	}
}	

void output()
{
	for (int i = 0; i < length; ++i) cout << fwd[i] << ' ';
	cout << endl;
}

int main()
{
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
		output();
	}
	return 0;
}
