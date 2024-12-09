#pragma once
#include "DatoEntidad.h"
enum estadoArma { habilitado, recarga, noBalas };
class DatoBala : public DatoEntidad {

public:
	DatoBala(float _x, float _y, int _cantidad)
		: DatoEntidad(_x, _y, 40, 60, _cantidad) {}

	void mostrar(BufferedGraphics^ buffer, Bitmap^ bmp, Graphics^ g, estadoArma estado) {
		if (cantidad == 0) indiceX = 2;
		else if (estado == recarga) indiceX = 1;
		else indiceX = 0;

		DatoEntidad::mostrar(buffer, bmp, g, Brushes::White, Brushes::DarkRed);
	}
};