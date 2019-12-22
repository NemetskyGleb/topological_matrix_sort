#pragma once
#include <iostream>
typedef unsigned char UC;
class BoolVector{
private:
	UC *bv;
	int n; //длина булева вектора
	int m; //размер масссива bv
public:
	int Input(char*, int, int, int); //формированием эл-та массива bv
	BoolVector();
	BoolVector(int);
	BoolVector(char*);
	BoolVector(char *s, int N); //strlen(s)!=N
	BoolVector(BoolVector &);
	~BoolVector();
	BoolVector & operator=(BoolVector&);

	void Print();
	void Scan(int);

	int Weight();
	BoolVector operator& (BoolVector); 
	BoolVector& operator&= (BoolVector); 
	BoolVector operator| (BoolVector); 
	BoolVector& operator|= (BoolVector); 
	BoolVector operator^ (BoolVector); 
	BoolVector & operator^= (BoolVector); 
	BoolVector& operator~ ();

	BoolVector operator>> (int); 
	BoolVector& operator>>= (int);
	BoolVector operator<< (int); 
	BoolVector& operator<<= (int); 
	BoolVector SetUp1(int);
	BoolVector SetUp0(int);
	BoolVector SetUp1(int kol, int pos);
	BoolVector SetUp0(int kol, int pos);
	BoolVector Invert(int);
	BoolVector Invert(int kol, int pos);
	UC operator[] (int);
	bool operator== (BoolVector);
	bool operator!= (BoolVector);
	bool operator< (BoolVector);  //x<y если x[i]<=y[i] для всех i
	bool operator> (BoolVector);  //x>y если x[i]>=y[i] для всех i

	friend std::ostream& operator<< (std::ostream &r, BoolVector &V);
	friend std::istream& operator>> (std::istream &r, BoolVector &V);
};
