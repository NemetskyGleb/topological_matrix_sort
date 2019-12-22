#pragma once
#include "BoolVector.h"
#include <iostream>
typedef unsigned char UC;
class BoolMatrix{
private:
	BoolVector* BV;
	int m, n; // m - rows, n - columns
	int Max(char** s, int M); // help function
public:
	BoolMatrix();
	BoolMatrix(int, int);
	BoolMatrix(char** s, int M);
	BoolMatrix(BoolMatrix &);
	BoolMatrix& operator=(BoolMatrix&);
	~BoolMatrix() { delete[] BV; };
	///* logic operations*/
	BoolMatrix operator&(const BoolMatrix&);
	BoolMatrix& operator&=(const BoolMatrix&);
	BoolMatrix operator|(const BoolMatrix&);
	BoolMatrix& operator|=(const BoolMatrix&);
	BoolMatrix operator^(const BoolMatrix&);
	BoolMatrix& operator^=(const BoolMatrix&);
	BoolVector Conj();	//конъюнкция всех строк матрицы
	BoolVector Disj(); //дизъюнкция всех строк матрицы
	BoolVector Xor(); //XOR всех строк матрицы
	BoolMatrix operator~ ();
	BoolMatrix SetUp1(int i, int j); //установить в 1 эл-т [i][j]
	BoolMatrix SetUp0(int i, int j); //сбросить в 0 эл-т [i][j]
	BoolMatrix Invert(int i, int j); //инвертировать эл-т [i][j]
	BoolMatrix SetUp1(int kol, int i, int pos);	//установить в 1 kol эл-тов в i-й строке, начиная с позиции pos
	BoolMatrix SetUp0(int kol, int i, int pos);//установить в 0 kol эл-тов в i-й строке, начиная с позиции pos
	BoolMatrix Invert(int kol, int i, int pos);	//инвертировать kol эл-тов в i-й строке, начиная с позиции pos
	BoolVector & operator[] (int);
	bool operator== (BoolMatrix&);
	bool operator!= (BoolMatrix&);
	///*Shifts*/
	BoolMatrix ShiftRight(int i, int kol); //сдвиг вправо эл-тов i  строки на kol эл-тов, создается новая матрица
	BoolMatrix& ShiftRightEq(int i, int kol); //сдвиг вправо эл-тов i  строки на kol эл-тов, изменяется *this
	BoolMatrix ShiftLeft(int i, int kol);	//сдвиг влево эл-тов i  строки на kol эл-тов, создается новая матрица
	BoolMatrix & ShiftLeftEq(int i, int kol);	//сдвиг влево эл-тов i  строки на kol эл-тов, изменяется *this
	///*Input, Output*/
	void Scan(int, int);
	void Print();
	friend std::ostream& operator<< (std::ostream& os, BoolMatrix& X);
	friend std::istream& operator>> (std::istream& is, BoolMatrix& X);
};