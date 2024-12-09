#pragma once
#include "Entidad.h"
#include "DatoDibujo.h"

class DatoEntidad : public Entidad, public DatoDibujo {

public:
	DatoEntidad(float _x, float _y, int _ancho, int _alto, int _cantidad = 0, int _indiceX = 0, int _indiceY = 0)
		: Entidad(_x, _y, _ancho, _alto, _indiceX, _indiceY), DatoDibujo(_cantidad) {}

	void mostrar(BufferedGraphics^ buffer, Bitmap^ bmpDato, Graphics^ g, Brush^ mayor = Brushes::DarkBlue, Brush^ menor = Brushes::DarkRed) {
		mostrarCantidadEnMedio(buffer, g, x, y, ancho, alto, mayor, menor);
		Entidad::Mostrar(buffer, bmpDato, g);
	}
};