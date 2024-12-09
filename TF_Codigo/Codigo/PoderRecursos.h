#pragma once
#include "Entidad.h"
#include "ArrDatoRecurso.h"
class PoderRecursos : public Entidad {
private:
	short unsigned int TiempoRestante;
	short unsigned int ultimaVezPoderActivado;

	//short unsigned int ultimavezPoderActivado;

public:
	PoderRecursos() : Entidad(718, 656, 60, 60) {
		TiempoRestante = 0;
		ultimaVezPoderActivado = 0;
	}

	void ActualizarEstadoImagen(ArrDatoRecurso* arrDatoRecurso, ZonaArboles^ zona) {
		if (arrDatoRecurso->GetPoderActivado()) {

			int intervaloTiempo = TiempoPoderBalasInfinitas / 6;


			if (arrDatoRecurso->GetTiempoRestantePoder() <= intervaloTiempo) {
				indiceX = 0;
			}
			else if (arrDatoRecurso->GetTiempoRestantePoder() <= intervaloTiempo * 2) {
				indiceX = 1;
			}
			else if (arrDatoRecurso->GetTiempoRestantePoder() <= intervaloTiempo * 3) {
				indiceX = 2;
			}
			else if (arrDatoRecurso->GetTiempoRestantePoder() <= intervaloTiempo * 4) {
				indiceX = 3;
			}
			else if (arrDatoRecurso->GetTiempoRestantePoder() <= intervaloTiempo * 5) {
				indiceX = 4;
			}
			else {
				indiceX = 5;
			}
		}

		else {
			if (zona->GetEstadoFruto() == Fructuacion) indiceX = 0;
			else indiceX = 6;
		}
		
	}

};