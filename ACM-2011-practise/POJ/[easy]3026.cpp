#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define N 110
#define M 60
#define MAX 100
struct Queue
{
	int x, y, dis;
};

int n, m, num;
Queue queue[M*M];
int dis[N][N], dis2[N], m2p[M][M], p2m[N];
char map[M][M];
bool vst[M][M], vst2[N];

void input()
{
	int i, j;
	char row[M];
	scanf("%d %d", &m, &n);
	gets(row);
	for (i = 0; i < n; ++i)
	{
		gets(row);
		for (j = 0; j < m; ++j) map[i][j] = row[j];
	}
//	for (i = 0; i < n; ++i)
//	{
//		for (j = 0; j < m; ++j) printf("%c", map[i][j]);
//		printf("\n");
//	}
//	printf("\n");
}

void scan_map()
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j) m2p[i][j] = -1;
	num = 0;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
			if (map[i][j] == 'S' || map[i][j] == 'A')
			{
				m2p[i][j] = num;
				p2m[num] = i*m+j;
				num++;
			}
}

bool try_walk(int x, int y)
{
	if (vst[y][x]) return false;
	if (map[y][x] == '#') return false;
	return true;
}

void add_queue(int x, int y, int tmp_dis, int tail, int index)
{
	if (m2p[y][x] >= 0) dis[index][m2p[y][x]] = tmp_dis;
	queue[tail].x = x;
	queue[tail].y = y;
	queue[tail].dis = tmp_dis;
	vst[y][x] = true;
}

void search(int y, int x, int index)
{
	int i, j;
	int head, tail;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j) vst[i][j] = false;
	dis[index][index] = 0;
	vst[y][x] = true;
	queue[0].x = x;
	queue[0].y = y;
	queue[0].dis = 0;
	head = 0; tail = 0;
	while (head <= tail)
	{
		if (try_walk(queue[head].x-1, queue[head].y)) add_queue(queue[head].x-1, queue[head].y, queue[head].dis+1, ++tail, index);
		if (try_walk(queue[head].x+1, queue[head].y)) add_queue(queue[head].x+1, queue[head].y, queue[head].dis+1, ++tail, index);
		if (try_walk(queue[head].x, queue[head].y-1)) add_queue(queue[head].x, queue[head].y-1, queue[head].dis+1, ++tail, index);
		if (try_walk(queue[head].x, queue[head].y+1)) add_queue(queue[head].x, queue[head].y+1, queue[head].dis+1, ++tail, index);
		++head;
	}
}

void search_way()
{
	int i, j;
	for (i = 0; i < num; ++i)
		search(p2m[i] / m, p2m[i] % m, i);
//	for (i = 0; i < n; ++i)
//	{
//		for (j = 0; j < m; ++j) 
//			if (m2p[i][j] < 0 || m2p[i][j] > 9) printf("%d ", m2p[i][j]);
//			else printf(" %d ", m2p[i][j]);
//		printf("\n");
//	}
//	printf("\n");
//	for (i = 0; i < num; ++i)
//	{
//		for (j = 0; j < num; ++j) printf("%d", dis[i][j]);
//		printf("\n");
//	}
//	printf("\n");
}
		
void connect()
{
	int i, j;
	int lst, index, ans;
	for (i = 0; i < num; ++i) dis2[i] = dis[0][i];
	for (i = 0; i < num; ++i) vst2[i] = true;
	vst2[0] = false;
	for (i = 1; i < num; ++i)
	{
		lst = MAX;
		for (j = 1; j < num; ++j)
			if (vst2[j] && dis2[j] < lst) {index = j; lst = dis2[j]; }
		vst2[index] = false;
		for (j = 1; j < num; ++j)
			if (vst2[j] && dis2[j] > dis[index][j]) dis2[j] = dis[index][j];
	}
	ans = 0;
	for (i = 1; i < num; ++i) ans += dis2[i];
	//for (i = 1; i < num; ++i) printf("dis2[%d]=%d\n", i, dis2[i]);
	cout << ans << endl;
}

void conduct()
{
	scan_map();
	search_way();
	connect();
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

