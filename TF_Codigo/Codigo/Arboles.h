#pragma once
#include "Biblioteca.h"
#include "Entidad.h"
class Arboles : public Entidad {
private:
    FasesArboles faseActual;
    TipoArboles tipo;
    EstadoArboles estadoFruto;
public:
    Arboles(int _x, int _y, TipoArboles _tipo)
        :Entidad(_x,_y,int(120),int(90)){
        faseActual = Fase1;
        tipo = _tipo;
        estadoFruto = Reposo;
    }

    ~Arboles() {}

    void Mostrar(BufferedGraphics^ buffer, Graphics^ g, Bitmap^ img) { 
        Rectangle corte = Rectangle(ancho * estadoFruto, alto * faseActual, ancho, alto);
       /* g->DrawRectangle(Pens::Black, getArea());*/
        buffer->Graphics->DrawImage(img, getArea(), corte, GraphicsUnit::Pixel); 
    }

    void AumentarFase() {
        if (faseActual < Fase5) {
            faseActual = static_cast<FasesArboles>(faseActual + 1);
        }
    }

    //Get's
    FasesArboles GetFase() {
        return faseActual;
    }
    TipoArboles GetTipo() {
        return tipo;
    }
    EstadoArboles GetEstadoFruto() {
        return estadoFruto;
    }

    //Set´s
    void SetFase(FasesArboles value) {
        faseActual = value;
    }
    void SetTipo(TipoArboles value) {
        tipo = value;
    }
    void SetEstadoFruto(EstadoArboles value) {
        estadoFruto = value;
    }

};
