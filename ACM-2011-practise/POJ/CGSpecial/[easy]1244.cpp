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

struct pnt { double x, y; };
#define N 1010
pnt p[N];
char str[N];
int pos[26][10];
int n;
const double pi = acos(-1.0), eps = 1e-6;
const double dx1 = cos(pi*2/3), dy1 = sin(pi*2/3), dx2 = 1;

double getdis(pnt p1, pnt p2) { return (p2.x-p1.x) * (p2.x-p1.x) + (p2.y-p1.y) * (p2.y-p1.y); }

void init()
{
	int i, j, k;
//	printf("dx1=%.3f dx2=%.3f dy1=%.3f\n", dx1, dx2, dy1);
	p[0].x = 0; p[0].y = 0; k = 0;
	for (i = 1; i < 12; ++i) {
		++k; p[k].x = p[k-i].x + dx1; p[k].y = p[k-i].y + dy1;
		for (j = 1; j <= i; ++j) { ++k; p[k].x = p[k-1].x + dx2; p[k].y = p[k-1].y; }
	}
}

void input()
{
	int i;
	memset(pos, 0, sizeof(pos));
	scanf("%s", str);
//	printf("str:%s\n", str);
	for (i = 0; i < strlen(str); ++i) pos[str[i]-'a'][++pos[str[i]-'a'][0]] = i;
}

bool judge(int x, int y, int z)
{
	double a = getdis(p[x], p[y]), b = getdis(p[y], p[z]), c = getdis(p[z], p[x]);
	return (fabs(a-b) < eps && fabs(b-c) < eps);
}

void conduct()
{
	bool find; int i;
	find = false;
	for (i = 0; i < 26; ++i) 
		if (pos[i][0] == 3 && judge(pos[i][1], pos[i][2], pos[i][3])) { printf("%c", i+'a'); find = true; }
	if (!find) printf("LOOOOOOOOSER!");
	printf("\n");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	init();
	while (scanf("%d", &n) != EOF && n) { input(); conduct(); }
//	fclose(stdin);
//	fclose(stdout);
}

