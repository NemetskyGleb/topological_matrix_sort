#include "BoolVector.h"
int BoolVector::Input(char* s, int i_s, int i_bv, int N)
//формированием эл-та bv[i_bv]
//i_s -индекс символа в s
//N -кол-во значащих цифр в bv[i_bv]
{
	UC mask = 1;
	mask <<= (N - 1);
	bv[i_bv] = 0;
	for (int i = i_s; i < N; i++, i_s++, mask >>= 1)
		if (s[i] == '1') bv[i_bv] |= mask;
	return i_s;
}
BoolVector::BoolVector()
{
	n = 0;
	m = 1;
	bv = new UC[m];
	bv[0] = 0;
}
BoolVector::BoolVector(int N)
{
	n = N;
	m = N / 8;
	int k = N % 8;
	if (k) m++;
	// вместо последних трех действий можно записать m=(N+7)/8;
	bv = new UC[m];
	for (int i = 0; i<m; i++)
		bv[i] = 0;
}
BoolVector::BoolVector(char* s)
{
	n = strlen(s);
	m = (n - 1) / 8 + 1;
	bv = new UC[m];
	for (int i = 0; i < m; i++)
		bv[i] = 0;
	UC mask = 1;
	int i = strlen(s) - 1;
	for (int i1 = n, i2 = m - 1; i1 > 0 && i >= 0; i1--, i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			i2--;
		}
		if (s[i] == '1')
			bv[i2] |= mask;
	}
}   
BoolVector::BoolVector(char *s, int N){
	if (strlen(s)){
		if (N == -1){
			n = strlen(s);
		}
		else{
			n = N;
		}
		if (n){
			m = (n - 1) / 8 + 1;
			bv = new UC[m];
			for (int i = 0; i < m; i++)
				bv[i] = 0;
			UC mask = 1;
			int i = strlen(s) - 1;
			for (int i1 = n, i2 = m - 1; i1 > 0 && i >= 0; i1--, i--, mask <<= 1)
			{
				if (!mask)
				{
					mask = 1;
					i2--;
				}
				if (s[i] == '1')
					bv[i2] |= mask;
			}
		}
	}
	else{
		m = 0;
		n = 0;
		bv = NULL;
	}

}
BoolVector::BoolVector(BoolVector &V)
{
	n = V.n;
	m = V.m;
	bv = new UC[m];
	for (int i = 0; i<m; i++)
		bv[i] = V.bv[i];
}
BoolVector::~BoolVector()
{
	delete[]bv;
}
BoolVector & BoolVector::operator=(BoolVector &V)
{
	if (this != &V)
	{
		delete[]bv;
		n = V.n;
		m = V.m;
		bv = new UC[m];
		for (int i = 0; i<m; i++)
			bv[i] = V.bv[i];
	}
	return *this;
}
BoolVector BoolVector::operator&(BoolVector V) //создается новый вектор
{//n1-длина результата, n1=min{n, V.n}
	int n1 = n;
	int i_res = m - 1;
	if (n1 > V.n) { n1 = V.n; i_res = V.m - 1; }

	/*int n1, i_res;
	if(n<V.n) {n1=n; i_res=m-1;}
	else {n1=V.n; i_res=V.m-1;}
	*/

	int i, i_V;
	BoolVector Res(n1);
	for (i = m - 1, i_V = V.m - 1; i_res >= 0; i--, i_V--, i_res--)
		Res.bv[i_res] = bv[i] & V.bv[i_V];
	return Res;
}
BoolVector & BoolVector::operator&=(BoolVector V) //изменяется *this
{
	BoolVector T = (*this) & V;
	*this = T;
	return *this;
}
BoolVector BoolVector::operator|(BoolVector V){
	int n1 = n;
	int i_res = m - 1;
	if (n1 < V.n) { n1 = V.n; i_res = V.m - 1; }
	int i, i_V;
	BoolVector Res(n1);
	for (i = m - 1, i_V = V.m - 1; i_V >= 0 && i>=0; i--, i_V--, i_res--)
		Res.bv[i_res] = bv[i] | V.bv[i_V];
	if (i >= 0) for (;i >= 0;i--, i_res--)Res.bv[i_res] = bv[i];
	if (i_V >= 0) for (;i_V >= 0;i_V--, i_res--)Res.bv[i_res] = V.bv[i_V];
	return Res;
}
BoolVector& BoolVector::operator|=(BoolVector V){
	return *this = *this | V;
}
BoolVector BoolVector::operator^(BoolVector V){
	int n1 = n;
	int i_res = m - 1;
	if (n1 < V.n) { n1 = V.n; i_res = V.m - 1; }
	int i, i_V;
	BoolVector Res(n1);
	for (i = m - 1, i_V = V.m - 1; i_V >= 0 && i>=0; i--, i_V--, i_res--)
		Res.bv[i_res] = bv[i] ^ V.bv[i_V];
	if (i >= 0) for (;i >= 0;i--, i_res--)Res.bv[i_res] = bv[i];
	if (i_V >= 0) for (;i_V >= 0;i_V--, i_res--)Res.bv[i_res] = V.bv[i_V];
	return Res;
}
BoolVector& BoolVector::operator^=(BoolVector V){
	return *this = *this ^ V;
}
BoolVector & BoolVector::operator~()
{
	for (int i = 0; i < m; i++)
		bv[i] = ~bv[i];
	return *this;
}
BoolVector BoolVector::operator>> (int k) //создается новый вектор
{
	BoolVector Res(n);
	if (k < n)
	{
		for (int i = 0; i < n - k; i++)
			/*if(this->operator[](i+k)=='1')
			Res.SetUp1(i);
			else Res.SetUp0(i);
			*/
		if ((*this)[i + k] == '1')
			Res.SetUp1(i);
		else Res.SetUp0(i);
	}
	return Res;
}
BoolVector & BoolVector::operator>>= (int k) //изменяется *this
{
	BoolVector T = (*this) >> k;
	*this = T;
	return *this;
}
BoolVector BoolVector::operator<<(int k){
		BoolVector Res(n);
	if (k < n){
		for (int i = n - 1; i >= 0; i--){
			if ((*this)[i-k] == '1')
				Res.SetUp1(i);
			else Res.SetUp0(i);
		}
	}
	return Res;
}
BoolVector & BoolVector::operator<<= (int k){
	return *this = *this << k;
}
BoolVector BoolVector::SetUp1(int pos)
{
	if (pos >= n) std::cout << "incorrect position";
	else {
		int m1 = pos / 8, k1 = pos % 8;
		UC mask = 1 << k1;
		bv[m - 1 - m1] |= mask;
	}
	return *this;
}
BoolVector BoolVector::SetUp1(int kol, int pos){
	if (n - pos >= kol){
		int	k1 = pos % 8;
		UC mask = 1 << k1;
		int m1 = m - pos / 8 - 1;
		for (int i = 0; i < kol; i++, mask <<= 1){
			if (!mask){
				mask = 1;
				m1--;
			}
			bv[m1] |= mask;
		}
	}
	else { std::cout << "incorrect postion return *this" << std::endl; };
	return *this;
}
BoolVector BoolVector::SetUp0(int pos){
	if (pos >= n) std::cout << "incorrect position" << std::endl;
	else {
		int m1 = m - pos / 8 - 1;
		bv[m1] &= ~(1 << pos % 8);
	}
	return *this;
}
BoolVector BoolVector::SetUp0(int kol, int pos){
	if (n - pos >= kol){
		int	k1 = pos % 8;
		UC mask = 1 << k1;
		int m1 = m - pos / 8 - 1;
		for (int i = 0; i < kol; i++, mask <<= 1){
			if (!mask){
				mask = 1;
				m1--;
			}
			bv[m1] &= ~mask;
		}
	}
	else { std::cout << "incorrect postion return *this" << std::endl; };
	return *this;
}
BoolVector BoolVector::Invert(int pos){
	if (pos >= 0 && pos < n){
		int m1 = m - pos / 8 - 1;
		int k1 = pos % 8;
		UC mask = 1 << k1;
		if (bv[m1] & mask)
			bv[m1] &= ~mask;
		else
			bv[m1] |= mask;
	}
	else { std::cout << "incorrect position return *this" << std::endl; }
	return *this;
}
BoolVector BoolVector::Invert(int kol, int pos){
	if (pos >= 0 && pos < n){
		if (kol <= (n - pos)){
			int m1 = m - pos / 8 - 1;
			int k1 = pos % 8;
			UC mask = 1 << k1;
			for (int i = 0; i < kol; i++, mask <<= 1){
				if (!mask){
					mask = 1;
					m1--;
				}
				if (bv[m1] & mask)
					bv[m1] &= ~mask;
				else
					bv[m1] |= mask;
			}
		}
	}
	else { std::cout << "incorrect postion return *this" << std::endl; }
	return *this;
}
UC BoolVector::operator[] (int pos)
{
	if (pos >= n) { std::cout << "incorrect position"; return '0'; }
	else {
		int m1 = pos / 8, k1 = pos % 8;
		UC mask = 1 << k1;
		if (bv[m - 1 - m1] & mask) return '1';
		else return '0';
	}
}
void BoolVector::Print(){
	UC mask = 1;
	if (n % 8 == 0)
		mask <<= 7;
	else
		mask <<= (n % 8 - 1);

	for (int i = 0; i < m; i++, mask = 1 << 7)
	{
		for (; mask; mask >>= 1)
		{
			if (bv[i] & mask)
				std::cout << '1';
			else
				std::cout << '0';
		}
	}
	std::cout << std::endl;
}
void BoolVector::Scan(int N)
{
	std::cout << "enter bool vector, length " << N << std::endl;
	std::cin.get();
	char *s;
	s = new char[N + 1];
	std::cin.getline(s, N + 1);
	BoolVector T(s);
	*this = T;
	delete[]s;
}
int BoolVector::Weight(){
	int res = 0;
	UC mask;
	for (int i = 0; i < m; i++){
		for (mask = 1; mask; mask <<= 1){
			if (bv[i] & mask)
				res++;
		}
	}
	return res;
}
bool BoolVector::operator==(BoolVector V){
	bool res = true;
	if (n == V.n){
		for (int i = 0; i < m; i++){
			if (bv[i] != V.bv[i]) return false;
		}
	}
	else return false;
	return true;
}
bool BoolVector::operator!= (BoolVector V){
	if (n == V.n){
		for (int i = 0; i < m; i++){
			if (bv[i] == V.bv[i]) return false;
		}
	}
	return true;
}
bool BoolVector::operator< (BoolVector V){
	if (n > V.n) return false;
	for (int i = 0; i < n; i++)
		if (V[i] < (*this)[i]) return false;
	return true;
}
bool BoolVector::operator> (BoolVector V){
	if (n < V.n) return false;
		for (int i = 0; i < n; i++)
			if (V[i] >(*this)[i]) return false;
	return true;
}
std::istream& operator>>(std::istream &r, BoolVector &V){
	std::cout << "enter length:" << std::endl;
	int N;
	std::cin >> N;
	V.Scan(N);
	return r;
}
std::ostream&  operator<<(std::ostream& os, BoolVector &V){
	UC mask = 1;
	if (V.n % 8 == 0)
		mask <<= 7;
	else
		mask <<= (V.n % 8 - 1);

	for (int i = 0; i < V.m; i++, mask = 1 << 7)
	{
		for (; mask; mask >>= 1)
		{
			if (V.bv[i] & mask)
				os << '1';
			else
				os << '0';
		}
	}
	os << std::endl;
	return os;
}