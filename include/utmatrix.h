﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType *pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // конструктор копирования
	~TVector();
	int GetSize()      { return Size; } // размер вектора
	int GetStartIndex(){ return StartIndex; } // индекс первого элемента
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector &v) const;  // сравнение
	bool operator!=(const TVector &v) const;  // сравнение
	TVector& operator=(const TVector &v);     // присваивание

	// скалярные операции
	TVector  operator+(const ValType &val);   // прибавить скаляр
	TVector  operator-(const ValType &val);   // вычесть скаляр
	TVector  operator*(const ValType &val);   // умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector &v);     // сложение
	TVector  operator-(const TVector &v);     // вычитание
	ValType  operator*(const TVector &v);     // скалярное произведение

	// ввод-вывод
	friend istream& operator>>(istream &in, TVector &v)
	{
		for (int i = 0; i < v.Size; i++){

			cin.exceptions(ios::failbit | ios::badbit);
			try
			{
				in >> v.pVector[i];
			}
			catch (exception& e)
			{
				throw("Not correct input data");
			}
			
		}
		return in;
	}
	friend ostream& operator<<(ostream &out, const TVector &v)
	{
        for (int i = 0; i < v.StartIndex; i++)
			out << "0 ";
		for (int i = v.StartIndex; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) // конструктор
{
	if (s > MAX_VECTOR_SIZE || s < 0)
		throw("Not correct vector size");
	if (si < 0 || si >= s)
		throw("Not correct start index");

	Size = s;
	StartIndex = si;

	pVector = new ValType[Size];

}

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;

	pVector = new ValType[Size];

	for (int i = StartIndex; i < Size; i++){
		pVector[i] = v.pVector[i];
	}

}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[]pVector;
}

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos >= Size || pos < 0){
		throw("Index out of bounds.");
	}

	return pVector[pos];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (&v == 0)
		return false;

	if (this == &v)
		return true;

	if (Size != v.Size || StartIndex != v.StartIndex)
		return false;

	for (int i = StartIndex; i < Size; i++){
		if (v.pVector[i] != pVector[i])
			return false;
	}

	return true;
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return (!(*this == v));
}

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (&v == 0)
		throw("Invalid assigned object");

	if (this == &v)
		return *this;

	delete[]pVector;
	Size = v.Size;
	StartIndex = v.StartIndex;

	pVector = new ValType[Size];

	for (int i = StartIndex; i < Size; i++){
		pVector[i] = v.pVector[i];
	}

	return *this;
}

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{

	TVector<ValType> buf(*this);

	for (int i = StartIndex; i < Size; i++){
		buf.pVector[i] += val;
	}

	return buf;
}

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> buf(*this);

	for (int i = StartIndex; i < Size; i++){
		buf.pVector[i] -= val;
	}

	return buf;
}

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> buf(*this);

	for (int i = StartIndex; i < Size; i++){
		buf.pVector[i] *= val;
	}

	return buf;
}

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (&v == 0)
		throw("Invalid assigned object");

	if (Size != v.Size || StartIndex != v.StartIndex)
		throw("Objects must be equal size");

	TVector<ValType> buf(Size, StartIndex);

	for (int i = StartIndex; i < Size; i++){
		buf[i] = pVector[i] + v.pVector[i];
	}

	return buf;
}

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (&v == 0)
		throw("Invalid assigned object");

	if (Size != v.Size || StartIndex != v.StartIndex)
		throw("Objects must be equal size");

	TVector<ValType> buf(Size, StartIndex);
	
	for (int i = StartIndex; i < Size; i++){
		buf[i] = pVector[i] - v.pVector[i];
	}

	return buf;
}

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (&v == 0)
		throw("Invalid assigned object");

	if (Size != v.Size || StartIndex != v.StartIndex)
		throw("Objects must be equal size");

	ValType result = 0;

	for (int i = StartIndex; i < Size; i++){
		result += pVector[i] * v.pVector[i];
	}

	return result;
}


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix &mt);                    // копирование
	TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
	bool operator==(const TMatrix &mt) const;      // сравнение
	bool operator!=(const TMatrix &mt) const;      // сравнение
	TMatrix& operator= (const TMatrix &mt);        // присваивание
	TMatrix  operator+ (const TMatrix &mt);        // сложение
	TMatrix  operator- (const TMatrix &mt);        // вычитание

	// ввод / вывод
	friend istream& operator>>(istream &in, TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream & operator<<(ostream &out, const TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}
};

// Конструктор
template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE || s < 0)
		throw("Not correct matrix size");

	for (int i = 0; i < s; i++){
		pVector[i] = TVector<ValType>(s, i);
	}
    // !!!! correct
	for (int i = 0; i < s; i++){
		for (int j = 0; j < s; j++){
			pVector[i][j] = 0;
		}
	}
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :
TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) :
TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt)
		return true;

	if (&mt == 0)
		return false;

	if (Size != mt.Size || StartIndex != mt.StartIndex)
		return false;

	for (int i = StartIndex; i < Size; i++){
		if (!(mt.pVector[i] == pVector[i]))
			return false;
	}

	return true;
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this == mt);
}

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (&mt == 0){
		throw("Second matrix adress is NULL");
	}
	if (this != &mt){
		if (Size != mt.Size){
			delete[]pVector;
			pVector = new TVector<ValType>[mt.Size]; // были круглые
		}
		Size = mt.Size;
		StartIndex = mt.StartIndex;
		for (int i = 0; i < Size; i++){
			pVector[i] = mt.pVector[i];
		}
	}
	return *this;
}

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (&mt == 0){
		throw("Second matrix adress is NULL");
	}
	return TVector<TVector<ValType> >::operator +(mt);
}

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (&mt == 0){
		throw("Second matrix adress is NULL");
	}
	return TVector<TVector<ValType> >::operator -(mt);
}

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
