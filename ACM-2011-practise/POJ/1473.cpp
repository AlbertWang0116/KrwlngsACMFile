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

char str[1010];
const double dx[9] = { 0, -1, 1, 0, -sqrt(2)/2, sqrt(2)/2, 0, -sqrt(2)/2, sqrt(2)/2};
const double dy[9] = { 0, 0, 0, 1, sqrt(2)/2, sqrt(2)/2, -1, -sqrt(2)/2, -sqrt(2)/2};

bool input()
{
	scanf("%s", str);
	if (!strcmp(str, "END")) return false; return true;
}

void conduct()
{
	double px, py, len;
	int ori, i, j;
	px = 0; py = 0;
	for (i = 0; i < strlen(str); ++i) {
		for (len = ori = 0, j = i; j < strlen(str) && str[j] != '.' && str[j] != ','; ++j) {
			if (str[j] >= '0' && str[j] <= '9') len = len*10 + str[j] - '0';
			else switch(str[j]) {
			case 'W': ori += 1; break;
			case 'E': ori += 2; break;
			case 'N': ori += 3; break;
			case 'S': ori += 6; break;
			}
		} px += dx[ori] * len; py += dy[ori] * len;
		if (str[j] == '.') break; i = j;
	} printf("The treasure is located at (%.3f,%.3f).\n", px, py);
	printf("The distance to the treasure is %.3f.\n\n", sqrt(px*px+py*py));
}

int main()
{
	int time = 0;
	while (input()) {
		printf("Map #%d\n", ++time); conduct();
	} return 0;
}
