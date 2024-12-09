#pragma once
#include "Persona.h"

class Ranking {
private:
	vector<Persona*> jugadores;

public:
	Ranking() {}
	~Ranking() {
		for (Persona* jugador : jugadores) delete jugador;
		jugadores.clear();
	}
	
	void mostrarTodosPuntaje(Graphics^ g, Panel^ panelPuntaje) {
		Font^ font = gcnew System::Drawing::Font("Courier New", 10, FontStyle::Bold);

		for (int i = 1; i <= jugadores.size(); i++) {
			Brush^ brush = (i == 1) ? Brushes::GreenYellow : (i <= 3) ? Brushes::DarkBlue : Brushes::Black;
			jugadores[i - 1]->mostrarPuntaje(g, brush, panelPuntaje, i * 20, font);
		}
	}

	void mostrarTodosFecha(Graphics^ g, Panel^ panelFecha) {
		Font^ font = gcnew System::Drawing::Font("Courier New", 8, FontStyle::Bold);

		for (int i = 1; i <= jugadores.size(); i++) {
			jugadores[i - 1]->mostrarFecha(g, Brushes::Black, panelFecha, i * 20, font);
		}
	}
	void mostrarTodosNombre(Graphics^ g, Panel^ panelNombre) {
		Font^ font = gcnew System::Drawing::Font("Courier New", 10, FontStyle::Bold);

		for (int i = 1; i <= jugadores.size(); i++) {
			Brush^ brush = (i == 1) ? Brushes::GreenYellow : (i <= 3) ? Brushes::DarkBlue : Brushes::Black;
			jugadores[i - 1]->mostrarNombre(g, brush, panelNombre, i * 20, font);
		}
	}

	void añadirJugador(Persona* jugador) {
		int i = 0;
		for (i; i < jugadores.size(); i++) {
			if (jugadores[i]->getPuntaje() <= jugador->getPuntaje()) break;
		}
		jugadores.insert(jugadores.begin() + i, jugador);
		if (jugadores.size() > 5) jugadores.pop_back();
	}

	vector<Persona*>& getJugadores() {
		return this->jugadores;
	}
};