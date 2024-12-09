#pragma once
#include "Enemigo.h"
#include "Jugador.h"
class Enemigo3 : public Enemigo {
private:
    float angulo;
public:
    Enemigo3(float _x, float _y) :Enemigo(100, _x, _y, 58, 58, 5, 5) {
    }
    ~Enemigo3() {}
    void CalcularAngulo(Jugador* perso) {
        float deltaX = perso->GetArea()->GetCentroX() - area->GetCentroX();
        float deltaY = perso->GetArea()->GetCentroY() - area->GetCentroY();
        angulo = Math::Atan2(deltaY, deltaX);
    }
    void Mostrar(BufferedGraphics^ buffer, Bitmap^ bmp) override {
        if (enDescomposicion == true) {
            indiceY = 4;
        }
        if (enDescomposicion == true && cuadroAnimacionDescomposicion == 1) {
            indiceX = 0;
        }
        Rectangle porcionUsar(indiceX * area->GetAncho(), indiceY * area->GetAlto(), area->GetAncho(), area->GetAlto());
        buffer->Graphics->TranslateTransform(area->GetX() + area->GetAncho() / 2, area->GetY() + area->GetAlto() / 2);
        buffer->Graphics->RotateTransform(angulo * 180 / Math::PI);
        buffer->Graphics->DrawImage(bmp, -area->GetAncho() / 2, -area->GetAlto() / 2, porcionUsar, GraphicsUnit::Pixel);
        buffer->Graphics->ResetTransform();
    }
    void ProcesarMovimiento(Jugador* perso) {
        CalcularAngulo(perso);
        if (Vida->getCantidad() <= 0) {
            enDescomposicion = true;
            if (cuadroAnimacionDescomposicion < cuadrosTotalesAnimacionDescomposicion) {
                cuadroAnimacionDescomposicion++;
            }
            else {
                enDescomposicion = false;
            }
        }
        if (area->DistanciaCon(perso->GetArea()) < 100) {
        }
        else {
            MoverHacia(perso->GetArea());
        }
    }
    bool SiDisparar(Jugador* perso) {
        if (area->DistanciaCon(perso->GetArea()) < 100) {
            return true;
        }
        else {
            return false;
        }
    }
    float GetAngulo() const {
        return this->angulo;
    }
    void SetAngulo(float _angulo) {
        this->angulo = _angulo;
    }
};


