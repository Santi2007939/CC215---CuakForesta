#pragma once
#include "Enemigo.h"
#include "Jugador.h"
class Enemigo1 : public Enemigo {
private:

public:
    Enemigo1(float _x, float _y) :Enemigo(30, _x, _y, 30, 28, 4, 4) {
    }
    ~Enemigo1() {}
    void Mostrar(BufferedGraphics^ buffer, Bitmap^ bmp) override {
        if (enDescomposicion == true && cuadroAnimacionDescomposicion == 1) {
            indiceX = 0;
        }
        Rectangle porcionUsar = Rectangle(indiceX * area->GetAncho(), indiceY * area->GetAlto(), area->GetAncho(), area->GetAlto());
        Rectangle personaje = Rectangle(area->GetX(), area->GetY(), area->GetAncho(), area->GetAlto());
        buffer->Graphics->DrawImage(bmp, personaje, porcionUsar, GraphicsUnit::Pixel);
        indiceX++;
        if (indiceX == 4) {
            indiceX = 0;
        }
    }
    void Mover() override {
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
            if (enDescomposicion) {
                indiceY = MorirIzq;
            }
            else {
                if (Vida->getCantidad() > 10) {
                    indiceY = CaminarIzq;
                }
                else {
                    indiceY = CaminarIzqDñ;
                }
            }
            break;
        }
        case Direccion::Derecha: {
            area->SetX(min(limiteDerecho - area->GetAncho(), area->GetX() + dx));
            if (enDescomposicion) {
                indiceY = MorirDer;
            }
            else {
                if (Vida->getCantidad() > 10) {
                    indiceY = CaminarDer;
                }
                else {
                    indiceY = CaminarDerDñ;
                }
            }
            break;
        }
        }
    }
    void ProcesarMovimiento(Jugador* perso) {
        if (Vida->getCantidad() <= 0) {
            enDescomposicion = true;
            if (cuadroAnimacionDescomposicion < cuadrosTotalesAnimacionDescomposicion) {
                cuadroAnimacionDescomposicion++;
            }
            else {
                enDescomposicion = false;
            }
        }
        MoverHacia(perso->GetArea());
    }
};

