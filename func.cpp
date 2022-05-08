#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

long long fact(long long n) //умею считать факториал
{
	if (n == 1 || n == 0)
		return 1;

	return fact(n - 1) * n;
}
long long lex(int* permutation, int n)//лексикографический порядок перестановки
{
	long long res = 0;
	int counter = 1;
	for (int i = 0; i < n - 1; i++)
	{
		while (permutation[i] == counter)
		{
			i++;
			counter++;
			if (counter == n)
				break;
		}
		if (i < n - 1)
		{
			if (counter != 1)
				for (int j = i; j < n; j++)
					permutation[j] -= counter - 1;
			res += fact(n - i - 1) * (permutation[i] - 1);
			for (int j = i + 1; j < n; j++)
			{
				if (permutation[i] < permutation[j])
					permutation[j]--;
			}
			counter = 1;
		}
	}
	return res + 1;
}

long long lex_diff(int* permutation1, int* permutation2, int n)//умею вычитать
{
	return abs(lex(permutation1, n) - lex(permutation2, n));
}

int chain_diff(int* permutation1, int* permutation2, int n)//цепная метрика
{
	int res = 0;
	for (int i = 0; i < n;)
	{
		int j = 0;
		int* index = find(permutation2, permutation2 + n, permutation1[i]);
		while (permutation1[i] == *(index + j) && i < n)
		{
			i++;
			j++;
		}
		if (i < n)
			res++;
		else
			return res;
	}
}

void recovery(int* permutation, int n)//восстановление
{
	int* bin = new int[n] {};

	for (int i = 0; i < n; i++)
		bin[permutation[i] - 1]++;

	for (int i = n; i > 0; i--)
		if (bin[permutation[i - 1] - 1] > 1)
		{
			int* index = find(bin, bin + n, 0);
			bin[permutation[i - 1] - 1]--;
			permutation[i - 1] = index - bin + 1;
			*index += 1;
			i++;
		}
}

int abcdefg(int* permutation1, int* permutation2, int n)//алфавитная метрика
{
	int res = 0;
	for (int i = 0; i < n; i++)
		if (permutation1[i] != permutation2[i])
			res++;

	return res;
}

int inversion(int* permutation1, int* permutation2, int n)//инверсная метрика
{
	int inv1 = 0, inv2 = 0;

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (permutation1[j] < permutation1[i])
				inv1++;
			if (permutation2[j] < permutation2[i])
				inv2++;
		}
	}

	return abs(inv1 - inv2);
}

int transpos(int* permutation1, int* permutation2, int n)//транспозиционная метрика
{
	int res = 0;

	for (int i = 0; i < n; i++)
	{
		if (permutation1[i] == permutation2[i])
			continue;
		else
		{
			int* index = find(permutation2 + i, permutation2 + n, permutation1[i]);
			swap(permutation2[i], *index);
			res++;
		}
	}

	return res;
}

int main()//главный
{
	int n = 5;
	int* b = new int[n] {1, 2, 3, 4, 5};
	int* a = new int[n] {5, 1, 2, 3, 4};
	recovery(b, n);
	for (int i = 0; i < n; i++)
		cout << b[i];

	cout << '\n' << transpos(a, b, n);
}