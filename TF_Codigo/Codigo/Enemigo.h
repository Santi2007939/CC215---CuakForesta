#pragma once
#include "PersonajeA.h"
#include "Dato.h"
class Enemigo :public PersonajeA {
protected:
    Dato* Vida;
    bool enDescomposicion;
    int cuadroAnimacionDescomposicion;
    int cuadrosTotalesAnimacionDescomposicion;
public:
    Enemigo(int _vidas, float _x, float _y, float _ancho, float _alto, float _dx, float _dy) :PersonajeA(_x, _y, _ancho, _alto, _dx, _dy) {
        Vida = new Dato(_vidas);
        enDescomposicion = false;
        cuadroAnimacionDescomposicion = 0;
        cuadrosTotalesAnimacionDescomposicion = 4;
    }
    ~Enemigo() {
        delete Vida;
    }
    void MoverHacia(Area* otraEntidad) {
        if (area->GetCentroX() > otraEntidad->GetCentroX())
            setDireccion(Izquierda);
        else if (area->GetCentroX() < otraEntidad->GetCentroX())
            setDireccion(Derecha);
        Mover();
        if (area->GetCentroY() > otraEntidad->GetCentroY())
            setDireccion(Arriba);
        else if (area->GetCentroY() < otraEntidad->GetCentroY())
            setDireccion(Abajo);
        Mover();
    }
    Dato* getVida() {
        return this->Vida;
    }

    void setCuadroDescomposicion(int _cuadro) {
        cuadroAnimacionDescomposicion = _cuadro;
    }
    void setEnDescomposicion(bool _valor) {
        enDescomposicion = _valor;
    }

    virtual void setDatos(bool _valor, int _cuadro, int _cantidad, bool _cantidadConstante, float _x, float _y) {
        setCuadroDescomposicion(_cuadro);
        setEnDescomposicion(_valor);
        Vida->setCantidad(_cantidad);
        Vida->SetCantidadConstante(_cantidadConstante);
        area->SetX(_x);
        area->SetY(_y);
    }

    int GetCuadroDescomposicion() {
        return cuadroAnimacionDescomposicion;
    }
    bool GetenDescomposicion() {
        return enDescomposicion;
    }

};

