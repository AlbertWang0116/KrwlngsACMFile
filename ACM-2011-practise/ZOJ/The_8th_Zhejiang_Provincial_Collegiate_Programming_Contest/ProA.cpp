#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

int n, m;

void input()
{
	scanf("%d", &n);
}

void conduct()
{
	while (n--)
	{
		scanf("%d", &m);
		if (m % 100 / 10 == 1)
		{
			cout << m << "th" << endl;
			continue;
		}
		if (m % 10 == 1) cout << m << "st" << endl;
		else if (m % 10 == 2) cout << m << "nd" << endl;
		else if (m % 10 == 3) cout << m << "rd" << endl;
		else cout << m << "th" << endl;
	}
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

