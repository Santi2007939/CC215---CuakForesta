#pragma once
#include "Enemigo.h"
#include "Jugador.h"
class Enemigo2 : public Enemigo {
private:
    bool EnTeletransportacion;
    int tiempoTeletransportacion;
    int tiempoActual;
public:
    Enemigo2(float _x, float _y) :Enemigo(50, _x, _y, 33, 32, 4, 4), EnTeletransportacion(false), tiempoTeletransportacion(10), tiempoActual(0) {
    }
    ~Enemigo2() {}
    bool GetEnTeletransportacion() {
        return EnTeletransportacion;
    }
    void ProcesarMovimiento(float _dJ, int _pJ, Jugador* perso, vector<Area*> contaVector) {
        if (EnTeletransportacion) {
            tiempoActual++;
            if (tiempoActual >= tiempoTeletransportacion) {

                EnTeletransportacion = false;
                tiempoActual = 0;
            }
            return;
        }

        if (Vida->getCantidad() <= 0) {
            enDescomposicion = true;
            if (cuadroAnimacionDescomposicion < cuadrosTotalesAnimacionDescomposicion) {
                cuadroAnimacionDescomposicion++;
            }
            else {
                enDescomposicion = false;
            }
        }
        vector<Area*> areas;
        int pE = area->IndiceAreaMasCercana(contaVector);
        float dE = area->DistanciaCon(contaVector[pE]);
        int pJ = _pJ;
        float dJ = _dJ;
        float dN = area->DistanciaCon(perso->GetArea());

        if (dE + dJ <= dN && pE != pJ) {
            areas.clear();
            if (!GetArea()->InterseccionaCon(contaVector[pE])) {
                MoverHacia(contaVector[pE]);
            }
            else {
                for (int i = 0; i < contaVector.size(); i++) {
                    if (i == pE || i == pJ) continue;
                    if (contaVector[i]->DistanciaCon(contaVector[pJ]) < contaVector[pE]->DistanciaCon(contaVector[pJ])) {
                        areas.push_back(contaVector[i]);
                    }
                }


                if (areas.empty()) {
                    area->SetX(contaVector[pJ]->GetX());
                    area->SetY(contaVector[pJ]->GetY());
                    EnTeletransportacion = true;
                }
                else {
                    area->SetX(contaVector[pE]->AreaMasCercana(areas)->GetX());
                    area->SetY(contaVector[pE]->AreaMasCercana(areas)->GetY());
                    EnTeletransportacion = true;
                }
            }
        }
        else {
            MoverHacia(perso->GetArea());
        }
    }
    void Mostrar(BufferedGraphics^ buffer, Bitmap^ bmp) override {
        if (EnTeletransportacion) {
            MostrarTeletransportar(buffer, bmp);
        }
        else {
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
    }
    void MostrarTeletransportar(BufferedGraphics^ buffer, Bitmap^ bmp) {
        if (!buffer || !bmp) return;
        Rectangle porcionUsar = Rectangle(indiceX * area->GetAncho(), indiceY * area->GetAlto(), area->GetAncho(), area->GetAlto());
        Rectangle personaje = Rectangle(area->GetX(), area->GetY(), area->GetAncho(), area->GetAlto());
        ImageAttributes^ imgAttributes = gcnew ImageAttributes();

        ColorMatrix^ colorMatrix = gcnew ColorMatrix();
        float brillo = 1.5f;
        colorMatrix->Matrix00 = brillo; // R
        colorMatrix->Matrix11 = brillo; // G
        colorMatrix->Matrix22 = brillo; // B
        colorMatrix->Matrix33 = 1.0f;   // A
        colorMatrix->Matrix44 = 1.0f;   // W
        imgAttributes->SetColorMatrix(colorMatrix, ColorMatrixFlag::Default, ColorAdjustType::Bitmap);
        buffer->Graphics->DrawImage(
            bmp,
            personaje,
            porcionUsar.X,
            porcionUsar.Y,
            porcionUsar.Width,
            porcionUsar.Height,
            GraphicsUnit::Pixel,
            imgAttributes
        );
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

    void setEnTeletrasnportacion(bool _enTeletransportacion) {
        EnTeletransportacion = _enTeletransportacion;
    }
    void setTiempoTeletransportacion(int _tiempoTeletransportacion) {
        tiempoTeletransportacion = _tiempoTeletransportacion;
    }
    void setTiempoActual(int _tiempoActual) {
        tiempoActual = _tiempoActual;
    }

    int getTiempoTeletrasnportacion() {
        return tiempoTeletransportacion;
    }
    int getTiempoActual() {
        return tiempoActual;
    }

    void setDatos(bool _valor, int _cuadro, int _cantidad, bool _cantidadConstante, float _x, float _y, bool _enTeletransportacion, int _tiempoTeletransportacion, int _tiempoActual) {
        Enemigo::setDatos(_valor, _cuadro, _cantidad, _cantidadConstante, _x, _y);
        setEnTeletrasnportacion(_enTeletransportacion);
        setTiempoTeletransportacion(_tiempoTeletransportacion);
        setTiempoActual(_tiempoActual);
    }
};

