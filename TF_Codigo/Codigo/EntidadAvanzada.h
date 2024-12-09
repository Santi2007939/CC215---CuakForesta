#pragma once
#include "Area.h"
class EntidadAvanzada {
protected:
    Area* area;
    int indiceX, indiceY;
public:
    EntidadAvanzada(float _x, float _y, int _ancho, int _alto, int _indiceX = 0, int _indiceY = 0) : area(new Area(_x, _y, _ancho, _alto)) {
        this->indiceX = _indiceX;
        this->indiceY = _indiceY;
    }
    virtual ~EntidadAvanzada() {
        delete area;
    }
    virtual void Mostrar(BufferedGraphics^ buffer, Bitmap^ bmp) {
        Rectangle porcionUsar = Rectangle(indiceX * area->GetAncho(), indiceY * area->GetAlto(), area->GetAncho(), area->GetAlto());
        Rectangle personaje = Rectangle(area->GetX(), area->GetY(), area->GetAncho(), area->GetAlto());
        buffer->Graphics->DrawImage(bmp, personaje, porcionUsar, GraphicsUnit::Pixel);
    }
    Area* GetArea() {
        return area;
    }
};