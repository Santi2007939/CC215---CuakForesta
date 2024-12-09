#pragma once
#include "DatoTexto.h"
#include "SeccionArboles.h"

class DatoArbol : public DatoTexto {
private:
	const int porcentajeGanar = 70;
public:
	DatoArbol(Graphics^ g) : DatoTexto(480,3, 0,"Porcentaje",g) {

	}
	~DatoArbol() {}

	void AumentarPorcentaje(SeccionArboles^ objSeccionArboles) {
		
		int sumatoria = 0;
		for each (auto zona in objSeccionArboles->getArr()) {
			int añadir = zona->getFase() - 1;
			añadir = max(añadir, 0);
			sumatoria += añadir;
		}
		
		cantidad = 100 * sumatoria / 9;
	}


	bool ganar() {
		if (cantidad >= 70) {
			return true;
		}
		else {
			return false;
		}
	}
};