#pragma once
#include "DatoDibujo.h"

class DatoTexto :  public DatoDibujo {
private:
	string nombre;
	int x, y, ancho, alto;

public:
	DatoTexto(int _x, int _y, int _cantidad, string _nombre, Graphics^ g)
		: DatoDibujo(_cantidad) {
		this->x = _x;
		this->y = _y;
		this->nombre = _nombre;
		getDimensiones(g);
		
	}

	void getDimensiones(Graphics^ g) {
		Font^ font = gcnew System::Drawing::Font("Courier New", 12, FontStyle::Bold);
		String^ nombreDato = gcnew String(nombre.c_str());
		SizeF size = g->MeasureString(nombreDato, font);
		this->ancho = size.Width;
		this->alto = size.Height;
	}

	void dibujarNombreCantidad(BufferedGraphics^ buffer, Graphics^ g) {
		Font^ font = gcnew System::Drawing::Font("Courier New", 12, FontStyle::Bold);
		String^ nombreDato = gcnew String(nombre.c_str());
		buffer->Graphics->DrawString(nombreDato, font, Drawing::Brushes::Black, x, y);
	}

	void mostrar(BufferedGraphics^ buffer, Graphics^ g, Brush^ mayor = Brushes::Blue, Brush^ menor = Brushes::Red, int _cantidad = 0) {
		mostrarCantidadEnMedio(buffer, g, x, y, ancho, alto, mayor, menor, _cantidad);
		dibujarNombreCantidad(buffer, g);
	}

};