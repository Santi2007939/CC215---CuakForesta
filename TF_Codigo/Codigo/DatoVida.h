#pragma once
#include "DatoEntidad.h"
#include "ZonaArboles.h"

class DatoVida : public DatoEntidad {
	int cantidadOriginal;
	bool poderActivado;
	int ultimaVezPoderActivado;
	int tiempoRestantePoder;
public:
	DatoVida(float _x, float _y, int _cantidad)
		: DatoEntidad(_x, _y, 60, 60, _cantidad) {
		this->cantidadOriginal = _cantidad;
		poderActivado = false;
		tiempoRestantePoder = 0;
	}

	void Mostrar(BufferedGraphics^ buffer, Bitmap^ bmp, Graphics^ g) {
		ejecucionPoder();
		int divisor = 25;
		indiceX = (cantidadOriginal - cantidad + (divisor - 1)) / divisor;

		int coordX = x + 53;
		int coordY = (y + alto / 2 - (alto / 6));
		int largoBarra = 2;
		buffer->Graphics->FillRectangle(Brushes::Black, coordX, coordY, cantidadOriginal * largoBarra, int(this->alto / 3));
		buffer->Graphics->FillRectangle(Brushes::IndianRed, coordX, coordY, cantidad * largoBarra, int(this->alto / 3));

		Entidad::Mostrar(buffer, bmp, g);
	}

	void inciarEjecucionPoder(ZonaArboles^ zona) {
		if (zona->GetEstadoFruto() == EstadoArboles::Fructuacion) {
			poderActivado = true;
			cantidad += AumentoVidasPoder;
			if (cantidad >= cantidadOriginal) {
				cantidad = cantidadOriginal;
			}
			ultimaVezPoderActivado = clock();
		}
	}

	void ejecucionPoder() {
		tiempoRestantePoder = clock() - ultimaVezPoderActivado;

		if (poderActivado) {
			if (tiempoRestantePoder <= TiempoPoderVidas) {
			}
			else {
				ultimaVezPoderActivado = clock();
				poderActivado = false;
			}

		}

	}

	void SetPoderActivado(bool value) { poderActivado = value; }
	bool GetPoderActivado() { return poderActivado; }
	void SetUltimaVezPoder(int _ultima) { ultimaVezPoderActivado = _ultima; }
	int GetUltimaVezPoder() { return ultimaVezPoderActivado; }
	void setTiempoRestantePoder(int _tiempoRestante) { tiempoRestantePoder = _tiempoRestante; }
	int GetTiempoRestante() { return tiempoRestantePoder; }

	void setDatoVida(bool value, int _ultima, int _tiempoRestante) {
		poderActivado = value;
		ultimaVezPoderActivado = _ultima;
		tiempoRestantePoder = _tiempoRestante;
	}

};