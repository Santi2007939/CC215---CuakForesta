#pragma once
#include "PersonajeA.h"
class Bala : public PersonajeA {
private:
    float angulo;
    bool visibilidad;
public:
    Bala(float _x, float _y, float _angulo) : PersonajeA(_x, _y, 16, 16, 10, 10) {
        this->angulo = _angulo;
        this->visibilidad = true;
    }
    ~Bala() {
        delete area;
    }

    float GetAngulo()const {
        return this->angulo;
    }
    void Mover() {
        area->SetX(area->GetX() + dx * cos(angulo));
        area->SetY(area->GetY() + dy * sin(angulo));
    }
    void MostrarBasico(BufferedGraphics^ buffer) {
        Rectangle rect = Rectangle(area->GetX(), area->GetY(), 10, 10);
        Color colorElipse = Color::FromArgb(255, 255, 0, 0);
        SolidBrush^ brush = gcnew SolidBrush(colorElipse);
        buffer->Graphics->FillEllipse(brush, rect);
        delete brush;
    }

};