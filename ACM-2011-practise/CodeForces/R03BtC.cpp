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

char pic[10][10];
int fc, sc, ft, fw, sw, fin;

void winner(char tag) {
	if (tag == 'X') fw = 1;
	if (tag == '0') sw = 1;
}

void conduct()
{
	int i, j;
	scanf("%s", pic[1]); scanf("%s", pic[2]);
	for (fc = sc = i = 0; i < 3; ++i) for (j = 0; j < 3; ++j) {
		if (pic[i][j] == 'X') fc++;
		if (pic[i][j] == '0') sc++;
	} if (fc-sc > 1 || fc-sc < 0) { printf("illegal\n"); return; }
	ft = sc+1-fc; if (fc+sc == 9) fin = 1;
	if (pic[0][0] == pic[0][1] && pic[0][1] == pic[0][2]) winner(pic[0][0]);
	if (pic[1][0] == pic[1][1] && pic[1][1] == pic[1][2]) winner(pic[1][0]);
	if (pic[2][0] == pic[2][1] && pic[2][1] == pic[2][2]) winner(pic[2][0]);
	if (pic[0][0] == pic[1][0] && pic[1][0] == pic[2][0]) winner(pic[0][0]);
	if (pic[0][1] == pic[1][1] && pic[1][1] == pic[2][1]) winner(pic[0][1]);
	if (pic[0][2] == pic[1][2] && pic[1][2] == pic[2][2]) winner(pic[0][2]);
	if (pic[0][0] == pic[1][1] && pic[1][1] == pic[2][2]) winner(pic[0][0]);
	if (pic[0][2] == pic[1][1] && pic[1][1] == pic[2][0]) winner(pic[0][2]);
	if (fw && sw) printf("illegal\n");
	else if (fw && ft) printf("illegal\n");
	else if (sw && !ft) printf("illegal\n");
	else if (fw) printf("the first player won\n");
	else if (sw) printf("the second player won\n");
	else if (fin) printf("draw\n");
	else if (ft) printf("first\n"); else printf("second\n");
}

int main()
{
//	while (scanf("%s", pic[0]) != EOF) conduct();
	scanf("%s", pic[0]); conduct();
	return 0;
}
