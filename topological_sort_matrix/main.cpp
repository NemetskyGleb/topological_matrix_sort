#include "BoolMatrix.h"
#include <iostream>


int main(){
	using namespace std;
	int m, n;
	cout << "Vertices: " << endl;
	cin >> n;
	cout << "Edges: " << endl;
	cin >> m;
	BoolMatrix M(n, n);
	int a, b, k;
	cout << M;
	for (int i = 0; i < m; i++)
	{
		cout << "enter number of edges in " << i + 1 << " vector" << endl;
		cin >> k;
		for (int j = 0; j < k; j++){
			cout << "enter position: " << endl;
			cin >> a;
			M.SetUp1(i, n - a);
		}
		cin.get();
	}
	cout << M;
	 //Topological Sort
	 //V0 - список обрабатонных вершин
	 //V1 - список вершин добавленных на текщем шаге
	 //D - дезьюнкция всех строк матрицы
	 //W  - ~D
	BoolVector V0(n), V1(n), D(n), W(n);
	int *Res = new int[n];
	int count = 0;
	while(count < n){
		D = M.Xor();
		cout << D;
		W = ~D;
		cout << W;
		V1 = V0 ^ W;
		cout << V1;
		for (int i = 0; i < n; i++){
			if (W[i] == '1'){
				M.SetUp0(n, i, 0);
				Res[count] = i + 1;
				count++;
			}
		}
		V0 = W;
	}
	// Out
	for (int i = 0; i < n; i++){
		cout << "Result : " << Res[i] << endl;
	}
	cin.get();
	return 0;
}