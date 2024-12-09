#pragma once
#include "Enemigo1.h"
#include "Enemigo2.h"
#include "Enemigo3.h"
class Contaminante : public EntidadAvanzada {
private:
    TipoContaminante tipo;
    Area* areaContaminada;
    Area* areaTeletransportacion;
    vector<Enemigo*> enemigos;
    int expansion;
    int tiempoActual;
    int tiempoTotal;

    bool enAnimacion;
    int cuadroAnimacion;
    int cuadrosTotalesAnimacion;
public:
    Contaminante(int _expansion, int _x, int _y, TipoContaminante _tipo)
        : EntidadAvanzada(_x, _y, 64, 90), areaTeletransportacion(new Area(_x + 17, _y + 57, 2, 2)), areaContaminada(new Area(_x - 10, _y - 10, 64 + 20, 90 + 20)), tipo(_tipo), expansion(_expansion), tiempoActual(0), enAnimacion(false), cuadroAnimacion(0), cuadrosTotalesAnimacion(8) {
        
        switch (tipo) {
        case TipoContaminante::Tipo1:
            tiempoTotal = 100;
            break;
        case TipoContaminante::Tipo2:
            tiempoTotal = 150;
            break;
        case TipoContaminante::Tipo3:
            tiempoTotal = 300;
            break;
        default:
            break;
        }
    }
    ~Contaminante() {
        delete areaContaminada;
        delete areaTeletransportacion;
        for (Enemigo* enemigo : enemigos) {
            delete enemigo;
        }
        enemigos.clear();
    }
    //Modificar arreglo enemigos
    void AgregarEnemigo() {
        switch (tipo) {
        case TipoContaminante::Tipo1:
            enemigos.push_back(new Enemigo1(area->GetX() + 17, area->GetY() + 62));
            break;
        case TipoContaminante::Tipo2:
            enemigos.push_back(new Enemigo2(area->GetX() + 17, area->GetY() + 57));
            break;
        case TipoContaminante::Tipo3:
            enemigos.push_back(new Enemigo3(area->GetX(), area->GetY()));
            break;
        default:
            break;
        }
    }
    void EliminarEnemigo(int indice) {
        if (indice >= 0 && indice < enemigos.size()) {
            delete enemigos[indice];
            enemigos.erase(enemigos.begin() + indice);
        }
    }
    void AumentarAreaContaminada() {
        float limiteSuperior = 160;
        float limiteInferior = 620;
        float limiteIzquierdo = 14;
        float limiteDerecho = 814;

        int xActual = areaContaminada->GetX();
        int yActual = areaContaminada->GetY();
        int anchoActual = areaContaminada->GetAncho();
        int altoActual = areaContaminada->GetAlto();

        int nuevoX = xActual - expansion;
        int nuevoY = yActual - expansion;
        int nuevoAncho = anchoActual + expansion * 2;
        int nuevoAlto = altoActual + expansion * 2;

        if (nuevoX < limiteIzquierdo) {
            nuevoX = limiteIzquierdo;
            nuevoAncho = (xActual + anchoActual) - limiteIzquierdo;
        }
        if (nuevoY < limiteSuperior) {
            nuevoY = limiteSuperior;
            nuevoAlto = (yActual + altoActual) - limiteSuperior;
        }
        if (nuevoX + nuevoAncho > limiteDerecho) {
            nuevoAncho = limiteDerecho - nuevoX;
        }
        if (nuevoY + nuevoAlto > limiteInferior) {
            nuevoAlto = limiteInferior - nuevoY;
        }

        areaContaminada->SetArea(nuevoX, nuevoY, nuevoAncho, nuevoAlto);
    }
    //Mover
    void MoverEnemigos(float _dW, int _pW, Jugador* perso, vector<Area*> contaVector) {
        for (int i = enemigos.size() - 1; i >= 0; --i) {
            switch (tipo) {
            case TipoContaminante::Tipo1: {
                Enemigo1* enemigo1 = dynamic_cast<Enemigo1*>(enemigos[i]);
                if (enemigo1) {
                    enemigo1->ProcesarMovimiento(perso);
                    if (enemigo1->getVida()->getCantidad() <= 0 && !enemigo1->GetenDescomposicion()) {
                        EliminarEnemigo(i);
                    }
                }
                break;
            }
            case TipoContaminante::Tipo2: {
                Enemigo2* enemigo2 = dynamic_cast<Enemigo2*>(enemigos[i]);
                if (enemigo2) {
                    enemigo2->ProcesarMovimiento(_dW, _pW, perso, contaVector);
                    if (enemigo2->getVida()->getCantidad() <= 0 && !enemigo2->GetenDescomposicion()) {
                        EliminarEnemigo(i);
                    }
                }
                break;
            }
            case TipoContaminante::Tipo3: {
                Enemigo3* enemigo3 = dynamic_cast<Enemigo3*>(enemigos[i]);
                if (enemigo3) {
                    enemigo3->ProcesarMovimiento(perso);
                    if (enemigo3->getVida()->getCantidad() <= 0 && !enemigo3->GetenDescomposicion()) {
                        EliminarEnemigo(i);
                    }
                }
                break;
            }
            default:
                break;
            }
        }
    }

    //Mostrar
    void Mostrar(BufferedGraphics^ buffer, Bitmap^ bmp) override {
        area->SetAlto(bmp->Height / 2);
        area->SetAncho(bmp->Width / 8);
        Rectangle porcionUsar = Rectangle(indiceX * area->GetAncho(), 0 * area->GetAlto(), area->GetAncho(), area->GetAlto());
        Rectangle personaje = Rectangle(area->GetX(), area->GetY(), area->GetAncho(), area->GetAlto());
        buffer->Graphics->DrawImage(bmp, personaje, porcionUsar, GraphicsUnit::Pixel);
    }
    void MostrarAreaContaminada(BufferedGraphics^ buffer) {
        Rectangle rect = Rectangle(areaContaminada->GetX(), areaContaminada->GetY(), areaContaminada->GetAncho(), areaContaminada->GetAlto());
        Color colorTransparente = Color::FromArgb(100, 255, 0, 0);
        SolidBrush^ brush = gcnew SolidBrush(colorTransparente);
        buffer->Graphics->FillRectangle(brush, rect);
        delete brush;
    }
    void MostrarAnimacionAparicion(BufferedGraphics^ buffer, Bitmap^ bmp) {
        Rectangle porcionUsar = Rectangle(cuadroAnimacion * area->GetAncho(), 1 * area->GetAlto(), area->GetAncho(), area->GetAlto());
        Rectangle personaje = Rectangle(area->GetX(), area->GetY(), area->GetAncho(), area->GetAlto());
        buffer->Graphics->DrawImage(bmp, personaje, porcionUsar, GraphicsUnit::Pixel);
        cuadroAnimacion++;
        if (cuadroAnimacion >= cuadrosTotalesAnimacion) {
            cuadroAnimacion = 0;
            enAnimacion = false;
            AgregarEnemigo();
            AumentarAreaContaminada();
        }
    }
    void MostrarContaminante(BufferedGraphics^ buffer, Bitmap^ bmpConta) {
        MostrarAreaContaminada(buffer);
        tiempoActual++;
        if (tiempoActual >= tiempoTotal && !enAnimacion) {
            enAnimacion = true;
            cuadroAnimacion = 0;
            tiempoActual = 0;
        }
        if (enAnimacion) {
            MostrarAnimacionAparicion(buffer, bmpConta);
        }
        else {
            Mostrar(buffer, bmpConta);
        }
    }
    void MostrarEnemigos(BufferedGraphics^ buffer, Bitmap^ bmpEnemigo) {
        for (auto& enemigo : enemigos) {
            switch (tipo) {
            case TipoContaminante::Tipo1: {
                Enemigo1* enemigo1 = dynamic_cast<Enemigo1*>(enemigo);
                if (enemigo1) {
                    enemigo1->Mostrar(buffer, bmpEnemigo);
                }
                break;
            }
            case TipoContaminante::Tipo2: {
                Enemigo2* enemigo2 = dynamic_cast<Enemigo2*>(enemigo);
                if (enemigo2) {
                    enemigo2->Mostrar(buffer, bmpEnemigo);
                }
                break;
            }
            case TipoContaminante::Tipo3: {
                Enemigo3* enemigo3 = dynamic_cast<Enemigo3*>(enemigo);
                if (enemigo3) {
                    enemigo3->Mostrar(buffer, bmpEnemigo);
                }
                break;
            }
            default:
                break;
            }
        }
    }
    //Set Get
    TipoContaminante GetTipo()const {
        return tipo;
    }

    vector<Enemigo*> GetEnemigos()const {
        return enemigos;
    }
    Area* GetAreaContaminada() {
        return areaContaminada;
    }
    Area* GetAreaTeletrasportacion() {
        return areaTeletransportacion;
    }
    int GetExpansion() const {
        return expansion;
    }
    void SetExpansion(int _expansion) {
        expansion = _expansion;
    }
    int GetTiempoActual() const {
        return tiempoActual;
    }
    void SetTiempoActual(int _tiempoActual) {
        tiempoActual = _tiempoActual;
    }
    int GetTiempoTotal() const {
        return tiempoTotal;
    }
    void SetTiempoTotal(int _tiempoTotal) {
        tiempoTotal = _tiempoTotal;
    }
    bool GetEnAnimacion() const {
        return enAnimacion;
    }
    void SetEnAnimacion(bool _enAnimacion) {
        enAnimacion = _enAnimacion;
    }
    int GetCuadroAnimacion() const {
        return cuadroAnimacion;
    }
    void SetCuadroAnimacion(int _cuadroAnimacion) {
        cuadroAnimacion = _cuadroAnimacion;
    }
    int GetCuadrosTotalesAnimacion() const {
        return cuadrosTotalesAnimacion;
    }
    void SetCuadrosTotalesAnimacion(int _cuadrosTotalesAnimacion) {
        cuadrosTotalesAnimacion = _cuadrosTotalesAnimacion;
    }
};

