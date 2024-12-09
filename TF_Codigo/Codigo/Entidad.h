#pragma once
#include "Biblioteca.h"

// #include <cmath>
// #include <limits>

class Entidad {
protected:
    float x, y;
    int ancho, alto;
    int indiceX, indiceY;

public:
    Entidad(float _x, float _y, int _ancho, int _alto, int _indiceX = 0, int _indiceY = 0) {
        this->x = _x;
        this->y = _y;
        this->ancho = _ancho;
        this->alto = _alto;
        this->indiceX = _indiceX;
        this->indiceY = _indiceY;
    }

    ~Entidad() {}

    virtual void Mostrar(BufferedGraphics^ buffer, Bitmap^ bmp, Graphics^ g) {
        Rectangle porcionUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
        Rectangle personaje = Rectangle(x, y, ancho, alto);
        buffer->Graphics->DrawImage(bmp, personaje, porcionUsar, GraphicsUnit::Pixel);
    }
   
    Rectangle getArea() {
        return Rectangle(int(x), int(y), ancho, alto);
    }

    float GetX()const {
        return x;
    }
    float GetY()const {
        return y;
    }
    
    int GetAncho()const {
        return ancho;
    }
    int GetAlto()const {
        return alto;
    }
    void SetX(int x) {
        this->x = x;
    }
    void SetY(int y) {
        this->y = y;
    }

    void SetAncho(int ancho) {
        this->ancho = ancho;
    }
    void SetAlto(int alto) {
        this->alto = alto;
    }


};
