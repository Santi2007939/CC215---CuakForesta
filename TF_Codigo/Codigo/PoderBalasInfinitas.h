#pragma once
#include "Entidad.h"
#include "ArrBalaJugador.h"
class PoderBalasInfinitas : public Entidad {
private:
	short unsigned int tiempoPoder;
public:
	PoderBalasInfinitas(ArrBalaJugador* objArrBala) : Entidad(649, 656, 60, 60) {
		tiempoPoder = objArrBala->GetTiempoPoder();
	}
	void ActualizarEstadoImagen(ArrBalaJugador* objArrBala, ZonaArboles^ zona) {
		if (objArrBala->GetPoderActivado()) {
			int intervaloTiempo = TiempoPoderBalasInfinitas / 6;
			if (objArrBala->GetTiempoRestantePoder() <= intervaloTiempo) {
				indiceX = 0;
			}
			else if (objArrBala->GetTiempoRestantePoder() <= intervaloTiempo * 2) {
				indiceX = 1;
			}
			else if (objArrBala->GetTiempoRestantePoder() <= intervaloTiempo * 3) {
				indiceX = 2;
			}
			else if (objArrBala->GetTiempoRestantePoder() <= intervaloTiempo * 4) {
				indiceX = 3;
			}
			else if (objArrBala->GetTiempoRestantePoder() <= intervaloTiempo * 5) {
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