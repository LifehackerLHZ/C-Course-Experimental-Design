#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int a[100];
int n;
void print(int p)
{
	for (int i = 1; i < p; i++)
	{
		if (i == p - 1)
			cout << a[i] << endl;
		else
			cout << a[i] << "+";
	}
}
void dfs(int left,int p,int k)
{
	if (left == 0)
	{
		print(p); return;
	}
	for (int i = k; i <= left; i++)
	{
		if (i == left && p == 1)
			continue;
		a[p] = i;
		dfs(left - i, p + 1,i);
		a[p] = 0;
	}
}
int main()
{
	cin >> n;
	dfs(n, 1,1);
}