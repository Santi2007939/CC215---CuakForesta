#pragma once
#include "Arboles.h"

ref class ZonaArboles {
private:
    int x, y;
    int ancho;
    int alto;
    Arboles* objArbol;

    int cantidadSemilla;
    int cantidadAgua;
    int cantidadResiduo;

    int UltimaVezProducidaFruta;

    const int distanciaMinima = 200;
    TipoArboles tipoArboles;

    Bitmap^ imgArboles;

public:
    ZonaArboles(int _x, int _y, TipoArboles _tipo) {

        x = _x;
        y = _y;
        ancho = 120;
        alto = 90;

        cantidadSemilla = 0;
        cantidadAgua = 0;
        cantidadResiduo = 0;
        tipoArboles = _tipo;

        switch (tipoArboles)
        {
        case TResourceTree:
            imgArboles = gcnew Bitmap("..\\SpriteFinalizados\\Png\\ResourceTree.png");
            break;
        case TBulletTree:
            imgArboles = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BulletTree.png");
            break;
        case THealthTree:
            imgArboles = gcnew Bitmap("..\\SpriteFinalizados\\Png\\HealthTree.png");
            break;
        default:
            break;
        }

        objArbol = new Arboles(_x, _y, tipoArboles);
        UltimaVezProducidaFruta = clock();
    }

    ~ZonaArboles() {
        delete objArbol, imgArboles;
    }

    void Mostrar(BufferedGraphics^ buffer, Graphics^ g) {
        AumentarFaseArbol();
        /*g->DrawRectangle(Pens::Green, x, y, ancho, alto);*/
        objArbol->Mostrar(buffer, g, imgArboles);
    }

    void ActualizarEstadoBoton(Rectangle personaje, Button^ btn) {
        int distancia = Math::Sqrt(Math::Pow(personaje.X - x, 2) + Math::Pow(personaje.Y - y, 2));
        btn->Enabled = (distancia < distanciaMinima);
    }

    void AgregarSemilla() {
        cantidadSemilla++;
    }
    void AgregarAgua() {
        cantidadAgua++;
    }
    void AgregarResiduo() {
        cantidadResiduo++;
    }

    TipoArboles getTipo() { return tipoArboles; }

    Rectangle getArea() {
        return Rectangle(x, y, ancho, alto);
    }

    Arboles* getObjArbol() {
        return objArbol;
    }

    void AumentarFaseArbol() {
        if ((cantidadSemilla >= 4) && (cantidadAgua >= 4) && (cantidadResiduo >= 4)) {
            objArbol->SetFase(Fase5);
        }
        else if ((cantidadSemilla >= 3) && (cantidadAgua >= 3 ) && (cantidadResiduo >= 3)) {
            objArbol->SetFase(Fase4);
        }
        else if ((cantidadSemilla >= 2) && (cantidadAgua >= 2) && (cantidadResiduo >= 2)) {
            objArbol->SetFase(Fase3);
        }
        else if ((cantidadSemilla >= 1) && (cantidadAgua >= 1) && (cantidadResiduo >= 1)) {
            objArbol->SetFase(Fase2);
        }
       
    }

    void SetUltimaVezProducidaFruta(int value) { UltimaVezProducidaFruta = value; }
    int GetUltimaVezProducidaFruta() { return UltimaVezProducidaFruta; }

    FasesArboles getFase() { return objArbol->GetFase(); }

    EstadoArboles GetEstadoFruto() {
        return objArbol->GetEstadoFruto();
    }

    int getCantidadAgua() { return cantidadAgua; }
    int getCantidadSemilla() { return cantidadSemilla; }
    int getCantidadResiduo() { return cantidadResiduo; }

    void setCantidadAgua(int _agua) {
        cantidadAgua = _agua;
    }
    void setCantidadSemilla(int _semilla) {
        cantidadSemilla = _semilla;
    }
    void setCantidadResiduo(int _residuo) {
        cantidadResiduo = _residuo;
    }

    void setZona(int _agua, int _semilla, int _residuo, int _ultimaVez) {
        setCantidadAgua(_agua);
        setCantidadSemilla(_semilla);
        setCantidadResiduo(_residuo);
        SetUltimaVezProducidaFruta(_ultimaVez);
    }


};
