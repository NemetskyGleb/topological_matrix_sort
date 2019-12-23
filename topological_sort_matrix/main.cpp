#include "BoolMatrix.h"
#include <iostream>

const int n = 9;
int main(){
	using namespace std;
	//int m, n;
	/*cout << "Vertices: " << endl;
	cin >> n;
	cout << "Edges: " << endl;
	cin >> m;*/
	//BoolMatrix M(9, 9);
	int a, b, k;
	const char *str_1[9]{
			"010010100",
			"000001000",
			"000000001",
			"010000010",
			"001000000",
			"000000000",
			"000100000",
			"001001001",
			"000001000"
	};
	char** matrix = new char*[9];
	for (int i = 0; i < 9; i++)//выделение памяти под массив
		matrix[i] = new char[9];
	for (int i = 0; i < 8; i++)
		strcpy(matrix[i],str_1[i]);
	BoolMatrix M(matrix, n - 1);
	cout << M;
	/*for (int i = 0; i < m; i++)
	{
		cout << "enter number of edges in " << i + 1 << " vector" << endl;
		cin >> k;
		for (int j = 0; j < k; j++){
			cout << "enter position: " << endl;
			cin >> a;
			M.SetUp1(i, n - a);
		}
		cin.get();
	}*/
	//cout << M;
	 //Topological Sort
	 //V0 - список обрабатонных вершин
	 //V1 - список вершин добавленных на текщем шаге
	 //D - дезьюнкция всех строк матрицы
	 //W  - ~D
	BoolVector V0(n), V1(n), D(n), W(n);
	int *Res = new int[n];
	int count = 0;
	while(count < n){
		D = M.Disj();
		W = ~D; 
		V1 = V0 ^ W;
		for (int i = n - 1; i >= 0; i--){
			if (V1[i] == '1'){
				M.SetUp0(n, n - i - 1, 0);
				Res[count] = n - i;
				count++;
			}
		}
		V0 = W;
	}
	// Out
	cout << "Result" << endl;
	for (int i = 0; i < n; i++){
		cout << Res[i] << " " ;
	}
	cin.get();
	return 0;
}