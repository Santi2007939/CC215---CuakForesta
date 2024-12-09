#pragma once
#include "Contaminante.h"
class ArrContaminante {
private:
    vector<Contaminante*> conta;
public:
    ArrContaminante() {}
    ~ArrContaminante() {
        for (Contaminante* contaminante : conta) {
            delete contaminante;
        }
        conta.clear();
    }
    //Modificar arreglo Contaminantes
    void EliminarContaminante(int indice) {
        if (indice >= 0 && indice < conta.size()) {
            delete conta[indice];
            conta.erase(conta.begin() + indice);
        }
    }
    void AgregarContaminante(Contaminante* co) {
        conta.push_back(co);
    }
    //Mover
    void ProcesarMovimientos(Jugador* perso) {
        int PMCJ = perso->GetArea()->IndiceAreaMasCercana(ReturnAreaTeletransportacion());
        float DMJ = perso->GetArea()->DistanciaCon(conta[PMCJ]->GetArea());
        for (auto& contamin : conta) {
            contamin->MoverEnemigos(DMJ, PMCJ, perso, ReturnAreaTeletransportacion());
        }
    }
    //Mostrar
    void MostrarContaminantesyEnemigos(BufferedGraphics^ buffer, Bitmap^ bmpConta1, Bitmap^ bmpEnemigo1, Bitmap^ bmpConta2, Bitmap^ bmpEnemigo2, Bitmap^ bmpConta3, Bitmap^ bmpEnemigo3) {
        for (auto& contamin : conta) {
            switch (contamin->GetTipo()) {
            case TipoContaminante::Tipo1:
                contamin->MostrarContaminante(buffer, bmpConta1);
                break;
            case TipoContaminante::Tipo2:
                contamin->MostrarContaminante(buffer, bmpConta2);
                break;
            case TipoContaminante::Tipo3:
                contamin->MostrarContaminante(buffer, bmpConta3);
                break;
            default:
                break;
            }
        }
        for (auto& contamin : conta) {
            switch (contamin->GetTipo()) {
            case TipoContaminante::Tipo1:
                contamin->MostrarEnemigos(buffer, bmpEnemigo1);
                break;
            case TipoContaminante::Tipo2:
                contamin->MostrarEnemigos(buffer, bmpEnemigo2);
                break;
            case TipoContaminante::Tipo3:
                contamin->MostrarEnemigos(buffer, bmpEnemigo3);
                break;
            default:
                break;
            }
        }
    }
    //Get Set
    vector<Contaminante*> GetContaminantes() {
        return conta;
    }
    vector<Area*> ReturnAreaTeletransportacion() {
        vector<Area*> areas;
        for (auto& contamin : conta) {
            areas.push_back(contamin->GetAreaTeletrasportacion());
        }
        return areas;
    }
};

