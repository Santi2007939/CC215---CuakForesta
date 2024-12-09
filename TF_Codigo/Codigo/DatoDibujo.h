#pragma once
#include "Dato.h"

class DatoDibujo: public Dato {

public:
	DatoDibujo(int _cantidad) : Dato(_cantidad) {}

	void mostrarCantidadEnMedio(BufferedGraphics^ buffer, Graphics^ g, int posX, int posY, int ancho, int alto, Brush^ mayor = Brushes::DarkBlue, Brush^ menor = Brushes::DarkRed, int cantidadSuperada = 0) {

		Font^ font = gcnew System::Drawing::Font("Courier New", 12, FontStyle::Bold);
		Brush^ brush;
		brush = (cantidad > cantidadSuperada) ? mayor : menor;

		int coordenadaX = posX + (ancho / 2);
		int coordenadaY = posY + (alto + 1);


		String^ textoCantidad = cantidad.ToString();
		SizeF size = g->MeasureString(textoCantidad, font);

		int textoX = coordenadaX - int(size.Width / 2);


		buffer->Graphics->DrawString(textoCantidad, font, brush, textoX, coordenadaY);
	}

};