#pragma once
#include "Entidad.h"

class Personaje : public Entidad {
protected:
	float dx, dy;

public:
	Personaje(float _x, float _y, float _ancho, float _alto, float _dx = 0, float _dy = 0, int _indiceX = 0, int _indiceY = 0)
		: Entidad(_x, _y, _ancho, _alto, _indiceX, _indiceY) {
		this->dx = _dx;
		this->dy = _dy;
	}
 

    virtual void Mover(BufferedGraphics^ buffer, Bitmap^ bmp, Graphics^ g) {
        /*
        switch (dir) {
        case Direccion::Arriba: y -= dy;  break;
        case Direccion::Abajo: y += dy;  break;
        case Direccion::Izquierda: x -= dx;  break;
        case Direccion::Derecha: x += dx;  break;
        }
        */
    }

    /*
    float calcularDistanciaConOtraEntidad(Entidad* otraEntidad) const {
        float dx = max(0, max(otraEntidad->GetX() - (x + ancho), x - (otraEntidad->GetX() + otraEntidad->GetAncho())));
        float dy = max(0, max(otraEntidad->GetY() - (y + alto), y - (otraEntidad->GetY() + otraEntidad->GetAlto())));
        return sqrt(dx * dx + dy * dy);
    }
    */

    bool detectarColision(Entidad* otraEntidad) {
        if (otraEntidad != nullptr) {
            return this->getArea().IntersectsWith(otraEntidad->getArea());
        }
        return false;
    }

    /*
    int puntoMasCercano(vector<Entidad*> vectorEntidad) {
        float minDistancia = std::numeric_limits<float>::max();
        int indiceMasCercano = -1;
        for (int i = 0; i < vectorEntidad.size(); i++) {
            if (vectorEntidad[i] != nullptr) {
                float distancia = calcularDistanciaConOtraEntidad(vectorEntidad[i]);
                if (distancia < minDistancia) {
                    minDistancia = distancia;
                    indiceMasCercano = i;
                }
            }
        }
        return indiceMasCercano;
    }
    int puntoMasCercano2(vector<Entidad*> vectorEntidad, vector<int> numeros) {
        float minDistancia = std::numeric_limits<float>::max();
        int indiceMasCercano = -1;
        for (int i = 0; i < numeros.size(); i++) {
            float distancia = calcularDistanciaConOtraEntidad(vectorEntidad[numeros[i]]);
            if (distancia < minDistancia) {
                minDistancia = distancia;
                indiceMasCercano = numeros[i];
            }
        }
        return indiceMasCercano;
    }
    */

    void SetDX(int dx) {
        this->dx = dx;
    }
    void SetDY(int dy) {
        this->dy = dy;
    }

	float GetDX()const {
		return dx;
	}
	float GetDY()const {
		return dy;
	}
};