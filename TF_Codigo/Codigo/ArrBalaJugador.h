#pragma once
#include "ArrBala.h"
#include "DatoBala.h"

class ArrBalaJugador : public ArrBala {
private:
	DatoBala* balaDato;
	estadoArma estado;
	int tiempoPoder, tiempoPoderTotal;
	int ultimaVezPoderActivado;
	bool poderActivado;
	int numeroDeBalasActual;
	int tiempoRestantePoder;
public:
	ArrBalaJugador():ArrBala() {
		balaDato = new DatoBala(312, 640, 20);
		this->poderActivado = false;
		this->estado = habilitado;
		this->tiempoPoder = TiempoPoderBalasInfinitas;
		this->ultimaVezPoderActivado = 0;
		numeroDeBalasActual = 20;
		tiempoRestantePoder = 0;
	}
	~ArrBalaJugador() {
		for (Bala* bala : balas) delete bala;
		balas.clear();
	}
	void añadirBala(Bala* b) override {
		if (disponible) {
			disponible = false;
			balaDato->cantidadDisminuir();
			balas.push_back(b);
		}
	}
	void moverTodo() override {
		ejecucionPoder();
		for (int i = balas.size() - 1; i >= 0; --i) {
			balas[i]->Mover();
			eliminarFuera(i);
		}
	}
	void ejecucionPoder() {
		tiempoRestantePoder = clock() - ultimaVezPoderActivado;

		if (poderActivado) {
			if (tiempoRestantePoder <= tiempoPoder) {
				disponible = true;
				estado = habilitado;

				balaDato->setCantidad(numeroDeBalasActual);
			}
			else {
				ultimaVezPoderActivado = clock();
				disponible = false;
				poderActivado = false;
				balaDato->SetCantidadConstante(false);
			}

		}

	}
	void mostrarTodo(BufferedGraphics^ buffer, Bitmap^ bmpBala, Bitmap^ bmpBalaDato, Graphics^g) {
		
		for (int i = 0; i < balas.size(); i++) balas[i]->Mostrar(buffer, bmpBala);
		balaDato->mostrar(buffer, bmpBalaDato, g, estado);
	} 
	void aumentarTiempoBala() override{
		if (!poderActivado) {
			if (!disponible && (balaDato->getCantidad() != 0 || poderActivado)) {
				tiempoActual++;
				estado = recarga;
				if (tiempoActual >= tiempoTotal) {
					disponible = true;
					estado = habilitado;
					tiempoActual = 0;
				}
			}
			else if (!disponible) {
				estado = noBalas;
			}
		}

	}

	DatoEntidad* getDatoBala() {
		return this->balaDato;
	}
	estadoArma getEstadoArma() {
		return this->estado;
	}

	void SetPoderActivado(bool value) { poderActivado = value; }
	bool GetPoderActivado() { return poderActivado; }

	int GetUltimaVezPoderActivado() const { return ultimaVezPoderActivado; }
	void setUltimaVezPoderActivado(int _ultimaVez) { ultimaVezPoderActivado = _ultimaVez; }
	int GetTiempoPoder() const { return tiempoPoder; }
	void setTiempoPoder(int _tiempoPoder) { tiempoPoder = _tiempoPoder; }
	int GetTiempoRestantePoder() const { return tiempoRestantePoder; }
	void setTiempoRestante(int _tiempoRestante) { tiempoRestantePoder = _tiempoRestante; }

	void setPoder(int _ultimaVez, int _tiempoPoder, int _tiempoRestante, bool _activado) {
		setUltimaVezPoderActivado(_ultimaVez);
		setTiempoPoder(_tiempoPoder);
		setTiempoRestante(_tiempoRestante);
		SetPoderActivado(_activado);
	}

	void inciarEjecucionPoder(ZonaArboles^ zona) {
		if (zona->GetEstadoFruto() == EstadoArboles::Fructuacion) {
			poderActivado = true;
			ultimaVezPoderActivado = clock();
			balaDato->SetCantidadConstante(true);
		}
	}
};