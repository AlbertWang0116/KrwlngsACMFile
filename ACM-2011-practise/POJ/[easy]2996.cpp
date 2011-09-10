#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;

#define N 10
int bk[N], bq[N], br[N], bb[N], bp[N], wk[N], wq[N], wr[N], wb[N], wp[N], wn[N], bn[N];
bool fst;

void white_insert(int* tp, int rw, int cl)
{
	//printf("tp[0]=%d\n", tp[0]);
	int pos = (7 - rw) * 8 + cl;
	int i;
	for (i = ++tp[0]; i > 1; --i)
		if (pos < tp[i-1]) tp[i] = tp[i-1];
		else break;
	tp[i] = pos;
}

void black_insert(int* tp, int rw, int cl)
{
	int i;
	int pos = rw * 8 + cl;
	for (i = ++tp[0]; i > 1; --i)
		if (pos < tp[i-1]) tp[i] = tp[i-1];
		else break;
	tp[i] = pos;
}

void white_output(int pos)
{
	cout << (char)(pos % 8 + 'a');
	cout << pos/8 + 1;
}

void black_output(int pos)
{
	cout << (char)(pos % 8 + 'a');
	cout << (8 - pos / 8);
}

void head(const char* tp)
{
	if (!fst) cout << "," << tp;
	else cout << tp;
	fst = false;
}

void input()
{
	memset(wk, 0, sizeof(wk));
	memset(wq, 0, sizeof(wq));
	memset(wr, 0, sizeof(wr));
	memset(wb, 0, sizeof(wb));
	memset(wn, 0, sizeof(wn));
	memset(wp, 0, sizeof(wp));
	memset(bk, 0, sizeof(bk));
	memset(bq, 0, sizeof(bq));
	memset(br, 0, sizeof(br));
	memset(bn, 0, sizeof(bn));
	memset(bb, 0, sizeof(bb));
	memset(bp, 0, sizeof(bp));
}

void conduct()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
			for (int k = 0; k < 4; ++k) getchar();
		getchar();	getchar();
		for (int j = 0; j < 8; ++j)
		{
			getchar();	getchar();
			char nt = getchar();
			//printf("i=%d, j=%d, nt=%c\n", i, j, nt);
			switch(nt)
			{
			case 'K':
				white_insert(wk, i, j);
				break;
			case 'Q':
				white_insert(wq, i, j);
				break;
			case 'R':
				white_insert(wr, i, j);
				break;
			case 'B':
				white_insert(wb, i, j);
				break;
			case 'N':
				white_insert(wn, i, j);
				break;
			case 'P':
				white_insert(wp, i, j);
				break;
			case 'k':
				black_insert(bk, i, j);
				break;
			case 'q':
				black_insert(bq, i, j);
				break;
			case 'r':
				black_insert(br, i, j);
				break;
			case 'b':
				black_insert(bb, i, j);
				break;
			case 'n':
				black_insert(bn, i, j);
				break;
			case 'p':
				black_insert(bp, i, j);
				break;
			}
			getchar();
		}
		getchar(); getchar();
	}
}

void output()
{
	int i;
	cout << "White: ";
	fst = true;
	for (i = 1; i <= wk[0]; ++i) {head("K"); white_output(wk[i]);}
	for (i = 1; i <= wq[0]; ++i) {head("Q"); white_output(wq[i]);}
	for (i = 1; i <= wr[0]; ++i) {head("R"); white_output(wr[i]);}
	for (i = 1; i <= wb[0]; ++i) {head("B"); white_output(wb[i]);}
	for (i = 1; i <= wn[0]; ++i) {head("N"); white_output(wn[i]);}
	for (i = 1; i <= wp[0]; ++i) {head(""); white_output(wp[i]);}
	cout << endl;
	cout << "Black: ";
	fst = true;
	for (i = 1; i <= bk[0]; ++i) {head("K"); black_output(bk[i]);}
	for (i = 1; i <= bq[0]; ++i) {head("Q"); black_output(bq[i]);}
	for (i = 1; i <= br[0]; ++i) {head("R"); black_output(br[i]);}
	for (i = 1; i <= bb[0]; ++i) {head("B"); black_output(bb[i]);}
	for (i = 1; i <= bn[0]; ++i) {head("N"); black_output(bn[i]);}
	for (i = 1; i <= bp[0]; ++i) {head(""); black_output(bp[i]);}
	cout << endl;
}

int main()

{
	input();
	conduct();
	output();
	return 0;
}
