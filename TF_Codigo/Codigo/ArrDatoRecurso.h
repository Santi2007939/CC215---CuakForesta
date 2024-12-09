#pragma once
#include "DatoEntidad.h"

class ArrDatoRecurso {
private:
	int x, y;
	vector<DatoEntidad*> arr;
	bool poderActivado;
	int ultimaVezPoderActivado;
	int tiempoRestantePoder;
	int tiempoPoder;
public:
	ArrDatoRecurso(int _x, int _y) {
		this->x = _x;
		this->y = _y;

		for (int i = 0; i < 3; i++) {
			arr.push_back(new DatoEntidad(x + i * 45, y, 44, 40));
		}
		poderActivado = false;
		ultimaVezPoderActivado = 0;
		tiempoRestantePoder = 0;
		tiempoPoder = TiempoPoderRecursos;
	}
	void Mostrar(BufferedGraphics^ buffer, Bitmap^ bmpSemilla, Bitmap^ bmpAgua, Bitmap^ bmpResiduo, Graphics^ g) {
		ejecucionPoder();
		List<Bitmap^> bmpRecursos;
		bmpRecursos.Add(bmpSemilla);
		bmpRecursos.Add(bmpAgua);
		bmpRecursos.Add(bmpResiduo);
		for (int i = 0; i < 3; i++) {
			arr[i]->mostrar(buffer, bmpRecursos[i], g);
		}
	}

	vector<DatoEntidad*> GetArr() {
		return this->arr;
	}

	~ArrDatoRecurso() {
		for (DatoEntidad* dato : arr) delete dato;
		arr.clear();
	}



	void iniciarEjecucionPoder(ZonaArboles^ zona) {
		if (zona->GetEstadoFruto() == EstadoArboles::Fructuacion) {
			poderActivado = true;
			ultimaVezPoderActivado = clock();
		}
	}

	void ejecucionPoder() {
		tiempoRestantePoder = clock() - ultimaVezPoderActivado;

		if (poderActivado) {
			if (tiempoRestantePoder <= tiempoPoder) {

			}
			else {
				ultimaVezPoderActivado = clock();
				poderActivado = false;
			}

		}

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

};