#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<climits>
#include<string>
using namespace std;

//NOTE : cal1 and cal2 is O(N) time query. It can be reduced to
//O(logN) time, with O(NlogN) Init time using segment tree.

#define N 1100000
int a[N];
int n, m;

struct node { 
	long long val; int ori, head, tail, x, y; 
	int operator<(const node &x) const {
		return val<x.val;
	}
};

int cmp(const int &i, const int &j) { return i>j; }

node cal1(int head, int tail) {
	int i, pre; long long sum;
	node ret; ret.val=LONG_MIN; ret.ori=1; ret.head=head; ret.tail=tail;
	for (pre=sum=0, i=head; i<=tail; ++i) {
		if (sum<0) { pre=i; sum=0; }
		sum=sum+a[i];
		if (sum>ret.val) { ret.val=sum; ret.x=pre; ret.y=i; }
	}
	return ret;
}

node cal2(int head, int tail) {
	int i, pre; long long sum;
	node ret; ret.val=LONG_MIN; ret.ori=0; ret.head=head; ret.tail=tail;
	for (pre=sum=0, i=head; i<=tail; ++i) {
		if (sum<0) { pre=i; sum=0; }
		sum=sum-a[i];
		if (sum>ret.val) { ret.val=sum; ret.x=pre; ret.y=i; }
	}
	return ret;
}

void conduct2() {
	int i, j, head, tail; node it;
	long long ans;
	--n;
	priority_queue<node> que;
	que.push(cal1(0, n));
	for (ans=i=0; i<m; ++i) {
		it=que.top(); que.pop(); ans=ans+it.val;
		head=it.head; tail=it.tail;
		if (it.ori) {
			if (it.x-1>=head) que.push(cal1(it.head, it.x-1));
			que.push(cal2(it.x, it.y));
			if (it.y+1<=tail) que.push(cal1(it.y+1, it.tail));
		} else {
			if (it.x-1>=head) que.push(cal2(it.head, it.x-1));
			que.push(cal1(it.x, it.y));
			if (it.y+1<=tail) que.push(cal2(it.y+1, it.tail));
		}
	}
	cout << ans << endl;
}

void conduct() {
	int i, sum1, sum2, tag;
	long long tot, ans;
	for (i=0; i<n; ++i) scanf("%d", &a[i]);
	for (tot=sum1=sum2=tag=i=0; i<n; ++i) 
		if (a[i]>=0) {
			if (!tag) { sum2++; tag=1; }
			sum1++; tot=tot+a[i];
		} else  tag=0;
	if (m>sum1) {
		sort(a, a+n, cmp);
		for (ans=i=0; i<m; ++i) ans=ans+a[i];
		cout << ans << endl;
	} 
	else if (sum2<=m) cout << tot << endl;
	else {
		conduct2();
	}
}

int main() {
	while (scanf("%d%d", &m, &n)!=EOF) conduct();
	return 0;
}
