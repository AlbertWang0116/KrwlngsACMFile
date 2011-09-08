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

int main()
{
	map<int, int> trymap;
	trymap.insert(pair<int, int>(1, 1));
	trymap.insert(pair<int, int>(2, 2));
	trymap.insert(pair<int, int>(3, 3));
	map<int, int>::iterator i;
	i = trymap.find(1);
	cout << i - trymap.begin() << endl;
	return 0;
}
