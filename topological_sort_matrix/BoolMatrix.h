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
	BoolVector Conj();	//���������� ���� ����� �������
	BoolVector Disj(); //���������� ���� ����� �������
	BoolVector Xor(); //XOR ���� ����� �������
	BoolMatrix operator~ ();
	BoolMatrix SetUp1(int i, int j); //���������� � 1 ��-� [i][j]
	BoolMatrix SetUp0(int i, int j); //�������� � 0 ��-� [i][j]
	BoolMatrix Invert(int i, int j); //������������� ��-� [i][j]
	BoolMatrix SetUp1(int kol, int i, int pos);	//���������� � 1 kol ��-��� � i-� ������, ������� � ������� pos
	BoolMatrix SetUp0(int kol, int i, int pos);//���������� � 0 kol ��-��� � i-� ������, ������� � ������� pos
	BoolMatrix Invert(int kol, int i, int pos);	//������������� kol ��-��� � i-� ������, ������� � ������� pos
	BoolVector & operator[] (int);
	bool operator== (BoolMatrix&);
	bool operator!= (BoolMatrix&);
	///*Shifts*/
	BoolMatrix ShiftRight(int i, int kol); //����� ������ ��-��� i  ������ �� kol ��-���, ��������� ����� �������
	BoolMatrix& ShiftRightEq(int i, int kol); //����� ������ ��-��� i  ������ �� kol ��-���, ���������� *this
	BoolMatrix ShiftLeft(int i, int kol);	//����� ����� ��-��� i  ������ �� kol ��-���, ��������� ����� �������
	BoolMatrix & ShiftLeftEq(int i, int kol);	//����� ����� ��-��� i  ������ �� kol ��-���, ���������� *this
	///*Input, Output*/
	void Scan(int, int);
	void Print();
	friend std::ostream& operator<< (std::ostream& os, BoolMatrix& X);
	friend std::istream& operator>> (std::istream& is, BoolMatrix& X);
};