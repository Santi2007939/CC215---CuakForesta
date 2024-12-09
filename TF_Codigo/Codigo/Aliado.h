#pragma once
#include "Personaje.h"

class Aliado : public PersonajeA {
private:

public:
	Aliado(float _x, float _y, float _dx = 0, float _dy = 0)
	: PersonajeA(_x, _y, 28, 28, _dx, _dy){		
	}
};

