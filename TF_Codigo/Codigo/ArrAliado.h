#pragma once
#include "Aliado.h"

class ArrAliado {
private:
	vector<Aliado*> arr;

public:
	ArrAliado() {}

	~ArrAliado() {
		for (Aliado* aliado : arr) delete aliado;
		arr.clear();
	}

	void AgregarAliado(Aliado* nuevoAliado) {
		arr.push_back(nuevoAliado);
	}

	void EliminarAliado(int pos) {
		arr.erase(arr.begin() + pos);
	}

	void Mostrar(BufferedGraphics^ buffer, Bitmap^ img) {
		for each (auto aliado in arr) {
			aliado->Mostrar(buffer, img);
		}
	}

	vector<Aliado*> GetArr() {
		return arr;
	}
};