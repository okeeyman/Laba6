#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

using namespace std;

queue <int> q;

void BFSD(int v, int** M, int* Vis, int Size)
{
	int i;
	q.push(v); Vis[v] = 0;

	while (!q.empty())
	{
		v = q.front();
		q.pop();
		printf("%3d", v + 1);

		for (i = 0; i < Size; i++)
		{
			if ((Vis[i] == -1) && (M[v][i] == 1))
			{
				q.push(i);
				Vis[i] = Vis[v] + 1;
			}
		}
	}
}

void main()
{
	int** G = NULL, i = 0, j = 0, S = 0, * Visited = NULL, N;
	char ReVis = 0;

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	printf("Введите размерность матрицы смежности: "); //Ввод размерности матрицы
	scanf("%d", &S);

	while (S <= 0) //Проверка корректности введенного числа
	{
		printf("Некорректно введённое число! Введите целое положительное число: ");
		scanf("%d", &S);
	}

	G = (int**)malloc(S * sizeof(int)); //Выделяем память
	Visited = (int*)malloc(S * sizeof(int));

	for (i = 0; i < S; i++) //Помечаем вершины как "непосещенные"
		Visited[i] = -1;

	for (i = 0; i < S; i++) //Генерация матрицы
	{
		G[i] = (int*)malloc(S * sizeof(int));
		for (j = 0; j < S; j++)
		{
			G[i][j] = rand() % 2;
			if (G[i][i] != 0)
				G[i][j] = 0;
		}
	}

	for (i = 0; i < S; i++) //Вывод матрицы на экран
	{
		printf("\n");
		for (j = 0; j < S; j++)
		{
			G[j][i] = G[i][j];
			printf("%2d", G[i][j]);
		}
	}

	printf("\n\nС какой вершины начать обход в ширину? ");
	scanf("%d", &N);

	while (N<1 || N>S) //Проверка номера введенной вершины
	{
		printf("Неверное значение! Попробуйте еще раз: ");
		scanf("%d", &N);
	}

	printf("\nОбход графа в ширину: ");
	i = N - 1;

	BFSD(i, G, Visited, S); //Обход графа в ширинв

	printf("\nВектор расстояний от выбранной вершины до всех остальных: ");

	for (i = 0; i < S; i++) {

		if (Visited[i] != -1) {
			printf("%3d", Visited[i]);
		}
		else {
			printf(" нет_связи ");
		}
	}

	printf("\n");

	free(Visited); //Очистка памяти
	free(G);
}