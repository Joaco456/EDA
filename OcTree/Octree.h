#ifndef OCTREE_H
#define OCTREE_H

#include "punto.h"
#include <vector>
double numParada = 1000;

using namespace std;

class Octree
{
public:
	Punto dimMaxima;
	Punto dimMinima;
	bool hoja;
	vector<Punto* > datos;
	//Octree* hijos[8];

	Octree()
	{
		dimMaxima = Punto(1, 1, 1);
		dimMinima = Punto(-1, -1, -1);
		hoja = true;
	}

	Octree(Punto max, Punto min)
	{
		dimMaxima = max;
		dimMinima = min;
		hoja = true;
	}
	
	~Octree() {
		for (auto i = 0; i < datos.size(); i++)
			delete datos[i];
		if (northWestF) {
			delete northWestF;
			delete southWestF;
			delete northEastF;
			delete southEastF;

			delete northWestB;
			delete southWestB;
			delete northEastB;
			delete southEastB;
		}
	}

	//octantes "frontales"
	Octree* northWestF;
	Octree* southWestF;
	Octree* northEastF;
	Octree* southEastF;
	//octantes "traseros"
	Octree* northWestB;
	Octree* southWestB;
	Octree* northEastB;
	Octree* southEastB;


	Octree* Ubicacion(Punto* point) //EN QUE OCTANTE SE UBICA EL PUNTO
	{
		float midX = (dimMaxima.x + dimMinima.x)/2;
		float midY = (dimMaxima.y + dimMinima.y) / 2;
		float midZ = (dimMaxima.z + dimMinima.z) / 2;

		if (point->x <= midX)
		{
			if (point->y <= midY)
			{
				if (point->z <= midZ)
					return southWestB;
				return southWestF;
			}
			else {
				if (point->z <= midZ)
					return northWestB;
				return northWestF;
			}
		}
		else {
			if (point->y <= midY)
			{
				if (point->z <= midZ)
					return southEastB;
				return southEastF;
			}
			else {
				if (point->z <= midZ)
					return northEastB;
				return northEastF;
			}
		}
	}

	bool Buscar(Punto* ptr, Octree** pOCT)
	{
		if (hoja)
		{
			*pOCT = this;

			for (auto i = 0; i < datos.size(); i++) //RECORRE PUNTOS DENTRO DEL OCTANTE
			{
				if (datos[i]->x == ptr->x and datos[i]->y == ptr->y and datos[i]->z == ptr->z)
					return true;
			}
			return false;
		}
		return Ubicacion(ptr)->Buscar(ptr, pOCT); //SI ES NODO INTERNO
	}

	bool Insertar(Punto* ptr)
	{
		Octree* pOCT = nullptr;

		if (Buscar(ptr, &pOCT)) return false; //SI YA EXISTE NO LO INSERTA

		if (pOCT == nullptr) return false; //VACIO
		
		if (pOCT->CondicionParada())
		{
			pOCT->hoja = false;

			float midX = (pOCT->dimMaxima.x + pOCT->dimMinima.x) / 2;
			float midY = (pOCT->dimMaxima.y + pOCT->dimMinima.y) / 2;
			float midZ = (pOCT->dimMaxima.z + pOCT->dimMinima.z) / 2;


			pOCT->northWestF = new Octree(Punto(pOCT->dimMinima.x, midY, midZ), Punto(midX, pOCT->dimMaxima.y, pOCT->dimMaxima.z));
			pOCT->southWestF = new Octree(Punto(pOCT->dimMinima.x, pOCT->dimMinima.y, midZ), Punto(midX, midY, pOCT->dimMaxima.z));
			pOCT->northEastF = new Octree(Punto(midX, midY, midZ), pOCT->dimMaxima);
			pOCT->southEastF = new Octree(Punto(midX, pOCT->dimMinima.y, midZ), Punto(pOCT->dimMaxima.x, midY, pOCT->dimMaxima.z));

			pOCT->northWestB = new Octree(Punto(pOCT->dimMinima.x, midY, pOCT->dimMinima.z), Punto(midX, pOCT->dimMaxima.y, midZ));
			pOCT->southWestB = new Octree(pOCT->dimMinima, Punto(midX, midY, midZ));
			pOCT->northEastB = new Octree(Punto(midX, midY, pOCT->dimMinima.z), Punto(pOCT->dimMaxima.x, pOCT->dimMaxima.y, midZ));
			pOCT->southEastB = new Octree(Punto(midX, pOCT->dimMinima.y, pOCT->dimMinima.z), Punto(pOCT->dimMaxima.x, midY, midZ));

			for (auto i = 0; i<int(pOCT->datos.size()); i++)
			{
				(pOCT->Ubicacion(pOCT->datos[i]))->Insertar(pOCT->datos[i]);
			}
			(pOCT->Ubicacion(ptr)->Insertar(ptr));

			(pOCT->datos).clear();
		}
		else { (pOCT->datos).push_back(ptr); }

		return true;
	}

	void Print()
	{

	}

private:

	bool CondicionParada()
	{
		if (datos.size() >= numParada)
			return true;
		return false;
	}

};


#endif // OCTREE_H