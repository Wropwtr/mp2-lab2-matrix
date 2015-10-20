// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void my_menu();

void default_menu(){
	TMatrix<int> a(5), b(5), c(5);
	int i, j;

	setlocale(LC_ALL, "Russian");
	cout << "Тестирование программ поддержки представления треугольных матриц"
		<< endl;
	for (i = 0; i < 5; i++)
	for (j = i; j < 5; j++)
	{
		a[i][j] = i * 10 + j;
		b[i][j] = (i * 10 + j) * 100;
	}
	c = a + b;
	cout << "Matrix a = " << endl << a << endl;
	cout << "Matrix b = " << endl << b << endl;
	cout << "Matrix c = a + b" << endl << c << endl;
	getchar();
}

void main()
{
	default_menu();
	return;
}
//---------------------------------------------------------------------------

void my_menu(){

	TMatrix<int> a(5), b(5), c(5);
	int j, i = 1;

	while (i != 0){

		cout << "Menu" << endl;
		cout << "1 - Enter matrix A" << endl;
		cout << "2 - Enter matrix B" << endl;
		cout << "3 - Swap A and B" << endl;
		cout << "4 - A - B" << endl;
		cout << "4 - A + B\n>" << endl;
		cin >> i;

	}
}

