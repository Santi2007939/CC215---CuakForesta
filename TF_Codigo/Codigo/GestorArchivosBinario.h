#pragma once
#include "GestorArchivos.h"

public ref class GestorArchivosBinario : public GestorArchivos {

public:
    // Cargar el ranking de un nivel específico
    void CargarRanking(int nivel, vector<Persona*>& ranking) {
        ifstream nomArch;
        nomArch.open(obtenerRutaArchivo(nivel, "ranking.dat"), ios::in | ios::binary);

        if (nomArch.is_open()) {
            JugadorArchivo jugador;
            while (nomArch.read(reinterpret_cast<char*>(&jugador), sizeof(jugador))) {
                string tiempo = jugador.tiempo;
                string nombre = jugador.nombre;
                int puntaje = jugador.puntaje;
                ranking.push_back(new Persona(nombre, tiempo, puntaje, 0));
            }
            nomArch.close();
        }
    }

    // Guardar el ranking de un nivel específico
    void GuardarRanking(int nivel, vector<Persona*> ranking) {
        string nombreArchivo = obtenerRutaArchivo(nivel, "ranking.dat");
        int cantidad = ranking.size();

        ofstream archivo(nombreArchivo, ios::binary | ios::out);  // Abre en modo binario y añade al final
        if (archivo.is_open()) {
            JugadorArchivo usuarioDatos;
            for (int j = 0; j < cantidad; j++) {
                for (int i = 0; i < ranking[j]->getNombre().size(); i++) {
                    usuarioDatos.nombre[i] = ranking[j]->getNombre()[i];
                }
                usuarioDatos.nombre[ranking[j]->getNombre().size()] = '\0';
                for (int i = 0; i < ranking[j]->getFecha().size(); i++) {
                    usuarioDatos.tiempo[i] = ranking[j]->getFecha()[i];
                }
                usuarioDatos.tiempo[ranking[j]->getFecha().size()] = '\0';
                usuarioDatos.puntaje = ranking[j]->getPuntaje();
                archivo.write(reinterpret_cast<char*>(&usuarioDatos), sizeof(usuarioDatos));
            }
            archivo.close();
        }
    }
};
