// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

#define Type int

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
	//default_menu();
	my_menu();
	return;
}
//---------------------------------------------------------------------------

void my_menu(){

	TMatrix<int> a, b;
	int j, i = 1;

	while (i != 0){

		cout << "Menu" << endl;
		cout << "1 - Enter matrix A" << endl;
		cout << "2 - Enter matrix B" << endl;
		cout << "3 - Swap A and B" << endl;
		cout << "4 - A - B" << endl;
		cout << "5 - A + B>" << endl;
		cout << "6 - Zero both matrix>" << endl;
		cout << "7 - Print A>" << endl;
		cout << "8 - Print B>" << endl;
        cout << "9 - A == B ?" << endl;
        cout << "10 - A != B ?" << endl;
		cout << "0 - EXIT>" << endl;
		cin >> i;
		cout << endl;

		switch (i){
		case 1:
		{
				  int sizeA = 0;
				  cout << "Enter size of matrix\n";
				  cin >> sizeA;  // try mb
                  if ( sizeA < 1)
                      throw("Size can not be negative");
				  a = TMatrix<Type>(sizeA);
				  cout << "Enter matrix:\n";
				  cin >> a;

				  break;
		}
		case 2:
		{
				  int sizeB = 0;
				  cout << "Enter size of matrix\n";
				  cin >> sizeB;
                  if ( sizeB < 1)
                      throw("Size can not be negative");
				  b = TMatrix<Type>(sizeB);
				  cout << "Enter matrix:\n";
				  cin >> b;

				  break;
		}
		case 3:
		{
				  TMatrix<Type> buf = a;
				  a = b;
				  b = buf;

				  break;
		}
		case 4:
		{
				  TMatrix<Type> buf = a - b;
				  cout << buf;

				  break;
		}
		case 5:
		{
				  TMatrix<Type> buf = a + b;
				  cout << buf;

				  break;
		}
		case 6:
		{
				  a = TMatrix<Type>(a.GetSize());
				  b = TMatrix<Type>(b.GetSize());

				  break;
		}
		case 7:
		{
				  cout << a;
				  break;
		}
		case 8:
		{
				  cout << b;
				  break;
		}
        case 9:
        {
            if ( a == b){
                cout << "true"<<endl;
            }
            else{
                cout <<" false"<< endl;
            }
            break;
        }
        case 10:
        {
            if ( a != b){
                cout << "true"<<endl;
            }
            else{
                cout <<" false"<< endl;
            }
            break;
        }
		case 0:
			return;
		default:
			continue;
		}
		cout << endl;
	}

	return;
}

