#pragma once
#include "EntidadAvanzada.h"
class PersonajeA : public EntidadAvanzada {
protected:
    float dx, dy;
    Direccion dir;
public:
    PersonajeA(float _x, float _y, float _ancho, float _alto, float _dx, float _dy, int _indiceX = 0, int _indiceY = 0)
        : EntidadAvanzada(_x, _y, _ancho, _alto, _indiceX, _indiceY) {
        this->dx = _dx;
        this->dy = _dy;
        dir = Ninguno;
    }
    virtual void Mover() {
        float limiteSuperior = 160;
        float limiteInferior = 620;
        float limiteIzquierdo = 14;
        float limiteDerecho = 814;
        switch (dir) {
        case Direccion::Arriba: {
            area->SetY(max(limiteSuperior, area->GetY() - dy));
            break;
        }
        case Direccion::Abajo: {
            area->SetY(min(limiteInferior - area->GetAlto(), area->GetY() + dy));
            break;
        }
        case Direccion::Izquierda: {
            area->SetX(max(limiteIzquierdo, area->GetX() - dx));

            break;
        }
        case Direccion::Derecha: {
            area->SetX(min(limiteDerecho - area->GetAncho(), area->GetX() + dx));

            break;
        }
        }
    }
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
    Direccion getDireccion() {
        return this->dir;
    }
    void setDireccion(Direccion _dir) {
        this->dir = _dir;
    }
};