#pragma once
#include "Bala.h"
class ArrBala{
protected:
	vector<Bala*> balas;
	int tiempoActual, tiempoTotal;
	bool disponible;
public:
	ArrBala() {
		this->tiempoActual = 0;
		this->tiempoTotal = 30;
		this->disponible = true;
	}
	~ArrBala() {
		for (Bala* bala : balas) {
			delete bala;
		}
		balas.clear();
	}
	virtual void añadirBala(Bala* b)
	{
		if (disponible) {
			disponible = false;
			balas.push_back(b);
		}
	}
	void eliminarBala(int indice) {
		if (indice >= 0 && indice < balas.size()) {
			Area* area = balas[indice]->GetArea();
			delete area;  
			balas[indice] = nullptr;  
			delete balas[indice];  
			balas.erase(balas.begin() + indice);  
		}
	}
	void mostrarTodo(BufferedGraphics^ buffer, Bitmap^ bmpBala, Graphics^ g) {
		for (int i = 0; i < balas.size(); i++) balas[i]->Mostrar(buffer, bmpBala);
	}
	void mostrarTodoBasico(BufferedGraphics^ buffer) {
		for (int i = 0; i < balas.size(); i++) balas[i]->MostrarBasico(buffer);
	}

	virtual void moverTodo() {

		for (int i = balas.size() - 1; i >= 0; --i) {
			balas[i]->Mover();
			eliminarFuera(i);
		}
	}
	void eliminarFuera(int i) {
		Bala* bala = balas[i];
		int yBala = bala->GetArea()->GetY(), altoBala = bala->GetArea()->GetAlto(), dyBala = bala->GetDY();
		int xBala = bala->GetArea()->GetX(), anchoBala = bala->GetArea()->GetAncho(), dxBala = bala->GetDX();
		if ((yBala + altoBala + dyBala > 620 || yBala + dyBala < 144) ||
			(xBala + dxBala > 814 || xBala + dxBala < 14)) {
			eliminarBala(i);
		}
	}
	virtual void aumentarTiempoBala() {
		if (!disponible) {
			tiempoActual++;
			if (tiempoActual >= tiempoTotal) {
				disponible = true;
				tiempoActual = 0;
			}
		}
	}
	void setDisponible(bool _disponible) {
		this->disponible = _disponible;
	}
	void setTiempoBala(int _tiempo) {
		this->tiempoActual = _tiempo;
	}
	bool getDisponible()const {
		return this->disponible;
	}
	int getTiempoActual()const {
		return this->tiempoActual;
	}
	vector<Bala*> getBalas() {
		return this->balas;
	}
};