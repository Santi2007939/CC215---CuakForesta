#pragma once
#include "Recurso.h"

class ArrRecurso {
private:
	vector<Recurso*> arr;

public:
	ArrRecurso() {

	}
	~ArrRecurso() {
		for (Recurso* recurso : arr) delete recurso;
		arr.clear();
	}

	void agregarRecurso(Recurso* nuevo) {
		arr.push_back(nuevo);
	}
	void eliminarRecurso(int pos) {
		if (pos < arr.size()) {
			arr.erase(arr.begin() + pos);
		}
	}
	void Mostrar(BufferedGraphics^ buffer, Graphics^ g) { 
		for (auto rec : arr) {
			rec->Mostrar(buffer, g);;
		}
	}
	void eliminarAutomaticamente() {
		auto it = arr.begin();
		while (it != arr.end()) {
			if ((*it)->GetRecogido()) {
				delete* it; // Libera la memoria asignada al puntero
				it = arr.erase(it); // Elimina el elemento del vector y avanza el iterador
			}
			else {
				++it; // Avanza el iterador si no hay que eliminar
			}
		}
	}
	vector<Recurso*> GetArr() {
		return arr;
	}

};