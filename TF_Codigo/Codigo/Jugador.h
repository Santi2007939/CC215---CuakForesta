#pragma once
#include "PersonajeA.h"
#include "DatoVida.h"

class Jugador : public PersonajeA {
private:
	float angulo;
	DatoVida* vidas;
public:
	Jugador(int _x, int _y) : PersonajeA(_x, _y, 56, 56, 10, 10) {
		angulo = 0;
		vidas = new DatoVida(26, 658, 100);
	}

	~Jugador() {
		delete vidas;
	}

	void calcularAngulo(float deltaX, float deltaY) {
		angulo = Math::Atan2(deltaY, deltaX);
	}
	void mostrar(BufferedGraphics^ buffer, Bitmap^ bmpJugador, Bitmap^ bmpCorazon, Graphics^ g) {		
		buffer->Graphics->TranslateTransform(area->GetX() + area->GetAncho() / 2, area->GetY() + area->GetAlto() / 2);
		// Rotar el sprite según el ángulo calculado (en grados)
		buffer->Graphics->RotateTransform(angulo * 180 / Math::PI);
		// Dibujar la imagen centrada en el nuevo origen
		buffer->Graphics->DrawImage(bmpJugador, -area->GetAncho() / 2, -area->GetAlto() / 2, area->GetAncho(), area->GetAlto());
		// Restablecer las transformaciones para que no afecten a otros dibujos
		buffer->Graphics->ResetTransform();
		vidas->Mostrar(buffer, bmpCorazon, g);
		//Entidad::mostrar(buffer, bmp, g);
	}
	void setAngulo(float _angulo) {
		this->angulo = _angulo;
	}
	float getAngulo() {
		return this->angulo;
	}
	DatoVida* getVida() {
		return this->vidas;
	}
};