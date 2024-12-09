#pragma once
#include "Biblioteca.h"

class Dato {
protected:
	int cantidad;
	bool CantidadConstante;
public:
	Dato(int _cantidad) {
		this->cantidad = _cantidad;
		CantidadConstante = false;
	}

	void cantidadDisminuir(int n = 1) {
		if (!CantidadConstante) {
			if (cantidad != 0) cantidad -= n;
		}
	}
	void cantidadAumentar(int n = 1) {
		if (!CantidadConstante) {
			cantidad += n;
		}
	}

	void setCantidad(int _cantidad) {
		if (!CantidadConstante) {
			cantidad = _cantidad;
		}
	}

	int& getCantidad() {
		return this->cantidad;
	}

	void SetCantidadConstante(bool value) {
		CantidadConstante = value;
	}

	bool GetCantidadConstante() {
		return CantidadConstante;
	}

};