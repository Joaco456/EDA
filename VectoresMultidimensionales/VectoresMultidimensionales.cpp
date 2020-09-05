
#include "VectoresMultidimensionales.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
typedef vector<vector<int>> vectorComplex;
typedef vector<int> vectorChill;

//CREANDO EL ESPACIO DE VECTORES
void MultiD(vectorComplex &Espacio, int filas, int dimensiones)
{
	srand(time(NULL));
	int n = 1 + rand() % (20000-1);
	for (auto i = 0; i < filas; i++)
	{
		vectorChill vector;
		for (auto j = 0; j < dimensiones; j++)
		{
			vector.push_back(n);
			int n = 1 + rand() % (10000-1);
		}
		Espacio.push_back(vector);
	}	
}

void print(int a, int b, int m) { cout << a << " V.S " << b << " = " << m << endl;}

//DISTANCIA EUCLIDIANA
int Euclidean(vectorComplex& Espacio, int filas, int dimensiones)
{
	float suma = 0;
	for (size_t i = 0; i < filas; i++)
	{
		for (size_t j = i + 1; j < filas; j++)
		{
			for (size_t k = 0; k < dimensiones; k++)
				suma += pow(Espacio[i][k] - Espacio[j][k], 2);
			//print(i, j, sqrt(suma));
		}
	}
	return sqrt(suma);

}
/*int Ecl(vectorChill a, vectorChill b)
{
	float suma = 0;
	for (auto i = 0; i < a.size(); i++)
		suma += pow(b[i] - a[i], 2);
	return sqrt(suma);
}*/


int main()
{
	vectorComplex espacioE;
	int a = 1;
	cout << "----- DISTANCIA EUCLIDIANA MULTIDIMENSIONAL -----" << endl;
	while (a == 1)
	{
		int filas = 0, dimensiones = 0;
		cout << "Nro Filas: "; cin >> filas;
		cout << "Nro Dimensiones: "; cin >> dimensiones;
		MultiD(espacioE, filas, dimensiones);
		auto begin = chrono::high_resolution_clock::now();
		Euclidean(espacioE, filas, dimensiones);
		auto end = chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto ms = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
		cout << ms << "ms" << endl;
		cin >> a;
	}


	/*vectorChill a = { 1,2,3,1};
	vectorChill b = { 6,5,4,2};
	cout << Ecl(a, b)<<endl;
	for (int i = 0; i < 10; i++)
	{
		int n = 1 + rand() % (10000-1);
		cout << n << " ";
	}*/
	return 0;
}
