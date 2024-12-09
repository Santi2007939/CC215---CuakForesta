#pragma once
#include "Biblioteca.h"
#include <string>

class Persona {
private:
	string nombre;
	string fecha;
	int puntaje;

public:

	Persona(String^ _nombre, int _tiempo, int _puntaje)
	{
		generarFecha();
		generarNombre(_nombre);
		this->puntaje = _tiempo * 10 + _puntaje;
	}

	Persona(string _nombre, string _fecha, int _puntaje, int diferente) {
		this->nombre = _nombre;
		this->fecha = _fecha;
		this->puntaje = _puntaje;
	}

	void generarNombre(String^ _nombre) {
		int longitud = _nombre->Length;
		string usar;
		for (int i = 0; i < longitud; i++) {
			usar += char(_nombre[i]);
		}
		this->nombre = usar;
	}

	void agregarCero(int n, string& s) {
		if (n < 10) s += '0';
	}

	void generarFecha() {
		DateTime ahora = DateTime::Now;
		string fechaCompleta = "";
		int dia = ahora.Day, mes = ahora.Month, año = ahora.Year % 100;
		int hora = ahora.Hour, minuto = ahora.Minute, segundo = ahora.Second;
		agregarCero(dia, fechaCompleta); fechaCompleta += to_string(dia); fechaCompleta += '/';
		agregarCero(mes, fechaCompleta); fechaCompleta += to_string(mes); fechaCompleta += '/';
		fechaCompleta += to_string(año); fechaCompleta += ' ';
		agregarCero(hora, fechaCompleta); fechaCompleta += to_string(hora); fechaCompleta += ':';
		agregarCero(minuto, fechaCompleta); fechaCompleta += to_string(minuto); fechaCompleta += ':';
		agregarCero(segundo, fechaCompleta); fechaCompleta += to_string(segundo);

		this->fecha = fechaCompleta;
	}

	/*
	void mostrar(Graphics^ g, Brush^ brush, Panel^ panelNombre, Panel^ panelFecha, Panel^ panelPuntaje, int altura) {
		Font^ font = gcnew System::Drawing::Font("Courier New", 12, FontStyle::Bold);

		mostrarNombre(g, brush, panelNombre, altura, font);
		mostrarFecha(g, brush, panelFecha, altura, font);
		mostrarPuntaje(g, brush, panelPuntaje, altura, font);
	}
	*/

	void mostrarFecha(Graphics^ g, Brush^ brush, Panel^ panel, int altura, Font^ font) {
		String^ textoFecha = gcnew String(fecha.c_str());

		SizeF sizeFecha = g->MeasureString(textoFecha, font);
		int textoFechaX = (panel->Width - int(sizeFecha.Width)) / 2;
		g->DrawString(textoFecha, font, brush, textoFechaX, panel->Top + altura);

	}
	void mostrarPuntaje(Graphics^ g, Brush^ brush, Panel^ panel, int altura, Font^ font) {
		
		String^ textoPuntaje = puntaje.ToString();

		SizeF sizePuntaje = g->MeasureString(textoPuntaje, font);
		int textoPuntajeX = (panel->Width - int(sizePuntaje.Width)) / 2;
		g->DrawString(textoPuntaje, font, brush, textoPuntajeX, panel->Top + altura);
	}
	void mostrarNombre(Graphics^ g, Brush^ brush, Panel^ panel, int altura, Font^ font) {
		String^ textoNombre = gcnew String(nombre.c_str());

		SizeF sizeNombre = g->MeasureString(textoNombre, font);
		int textoNombreX = (panel->Width - int(sizeNombre.Width)) / 2;
		g->DrawString(textoNombre, font, brush, textoNombreX, panel->Top + altura);
	}

	string getNombre() {
		return this->nombre;
	}

	int getPuntaje() {
		return this->puntaje;
	}

	string getFecha() {
		return this->fecha;
	}

	void setPuntaje(int _puntaje) {
		this->puntaje = puntaje;
	}
};