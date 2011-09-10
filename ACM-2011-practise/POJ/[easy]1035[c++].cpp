#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 20
#define M 10010
struct Trie
{
	Trie* next[26];
	int tag;
};
Trie *root;
char dic[M][N];
bool vst[M];
int n, m;

void trie_init()
{
	int i;
	root = new Trie();
	for (i = 0; i < 26; ++i) root->next[i] = NULL;
	root->tag = -1;
}

void trie_insert(char* word, int index)
{
	Trie* p;
	int i, j;
	p = root;
	for (i = 0; i < strlen(word); ++i)
	{
		if (p->next[word[i]-'a'] == NULL)
		{
			p->next[word[i]-'a'] = new Trie();
			for (j = 0; j < 26; ++j) p->next[word[i]-'a']->next[j] = NULL;
			p->next[word[i]-'a']->tag = -1;
		}
		p = p->next[word[i]-'a'];
	}
	p->tag = index;
}

int trie_check(char* word)
{
	Trie* p;
	int i;
	p = root;
	for (i = 0; i < strlen(word); ++i)
	{
		if (p->next[word[i]-'a'] == NULL) return -1;
		p = p->next[word[i]-'a'];
	}
	return p->tag;
}

void input()
{
	trie_init();
	m = 0;
	while (true)
	{
		scanf("%s", dic[m]);
		if (dic[m][0] == '#') break;
		trie_insert(dic[m], m);
		m++;
	}
}
	
void conduct()
{
	int i, j;
	char word[N], word2[N];
	int ret, len;
	while (true)
	{
		scanf("%s", word);
		if (word[0] == '#') break;
		if (trie_check(word) >= 0)
		{
			cout << word << " is correct" << endl;
			continue;
		}
		cout << word << ":";
		n = 0;
		len = strlen(word);
		memset(vst, false, sizeof(vst));
		for (i = 0; i <= strlen(word); ++i)
			for (j = 'a'; j <= 'z'; ++j)
			{
				strncpy(word2, word, i);
				word2[i] = (char)j;
				word2[i+1] = '\0';
				strcat(word2, word+i);
				//word2[len+1] = '\0';
				//printf("[Check Word:%s]", word2);
				if ((ret = trie_check(word2)) >= 0) vst[ret] = true;
			}
		for (i = 0; i < strlen(word); ++i)
			for (j = 'a'; j <= 'z'; ++j)
			{
				strcpy(word2, word);
				word2[i] = (char)j;
				//word2[len] = '\0';
				//printf("[Check Word:%s]", word2);
				if ((ret = trie_check(word2)) >= 0) vst[ret] = true;
			}
		for (i = 0; i < strlen(word); ++i)
		{
			strncpy(word2, word, i);
			word2[i] = '\0';
			strcat(word2, word+i+1);
			//word2[len-1] = '\0';
			//printf("[Check Word:%s]", word2);
			if ((ret = trie_check(word2)) >= 0) vst[ret] = true;
		}
		for (i = 0; i < m; ++i)
			if (vst[i]) cout << " " << dic[i];
		cout << endl;
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	srand(time(0));
	input();
	conduct();
	//fclose(stdin);
	//fclose(stdout);
}

