#pragma once
#include "Entidad.h"
#include "ArrBala.h"
#include "DatoVida.h"
#include "ZonaArboles.h"
class PoderVidas : public Entidad {
private:
	short unsigned int TiempoRestante;
	short unsigned int ultimaVezPoderActivado;
	bool ejecutarAnimacion;

	//short unsigned int ultimavezPoderActivado;

public:
	PoderVidas() : Entidad(580, 656, 60, 60) {
		TiempoRestante = 0;
		ultimaVezPoderActivado = 0;
		ejecutarAnimacion = false;
	}

	void ActualizarEstadoImagen(DatoVida* datoVidaJugador, ZonaArboles^ zona) {
		if (datoVidaJugador->GetPoderActivado()) {

			int intervaloTiempo = TiempoPoderVidas / 6;
			TiempoRestante = clock() - ultimaVezPoderActivado;

			if (TiempoRestante <= intervaloTiempo) {
				indiceX = 0;
			}
			else if (TiempoRestante <= intervaloTiempo * 2) {
				indiceX = 1;
			}
			else if (TiempoRestante <= intervaloTiempo * 3) {
				indiceX = 2;
			}
			else if (TiempoRestante <= intervaloTiempo * 4) {
				indiceX = 3;
			}
			else if (TiempoRestante <= intervaloTiempo * 5) {
				indiceX = 4;
			}
			else {
				indiceX = 5;
			}
		}

		else {
			if (zona->GetEstadoFruto() == Fructuacion) indiceX = 0;
			else indiceX = 6;
			ejecutarAnimacion = false;
		}
		
	}

	void iniciarEjecucionPoder(ZonaArboles^ zona) {
		if (zona->GetEstadoFruto() == EstadoArboles::Fructuacion) {
			ultimaVezPoderActivado = clock();
			ejecutarAnimacion = true;
		}
	}

	int GetTiempoRestante() {
		return TiempoRestante;
	}
	int GetUltimaVezPoderActivado() {
		return ultimaVezPoderActivado;
	}
	bool GetEjecutarAnimacion() {
		return ejecutarAnimacion;
	}

	void setTiempoRestante(int _tiempoRestante) {
		TiempoRestante = _tiempoRestante;
	}
	void setUltimaVez(int _ultimaVez) {
		ultimaVezPoderActivado = _ultimaVez;
	}
	void setEjecutarAnimacion(bool _ejecutar) {
		ejecutarAnimacion = _ejecutar;
	}
	void setPoderVidas(int _tiempoRestante, int _ultimaVez, bool _ejecutar) {
		setTiempoRestante(_tiempoRestante);
		setUltimaVez(_ultimaVez);
		setEjecutarAnimacion(_ejecutar);
	}
};