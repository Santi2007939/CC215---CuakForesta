#pragma once
#include "GestorArchivos.h"
#include "Controladora.h"

public ref class GestorArchivosGenerador : public GestorArchivos {

public:
    // Cargar el ranking de un nivel específico

    bool verificarNivel(int nivel) {
        ifstream nomArch;
        nomArch.open(obtenerRutaArchivo(nivel, "activado.txt"), ios::in);
        if (nomArch.is_open()) {
            nomArch.close();
            return true;
        }
        return false;
    }

    string getNombreNivel(int nivel) {
        ifstream nomArch;
        nomArch.open(obtenerRutaArchivo(nivel, "datos.txt"), ios::in);
        string nombre;
        if (nomArch.fail()) {
            nombre = "Cuidado!";
        }
        else {
            std::getline(nomArch, nombre);
            nomArch.close();
        }
        return nombre;
    }



    void activarSiguienteNivel(int nivel) {
        if (nivel >= 4) return;
        nivel++;
        ofstream nomArch;
        nomArch.open(obtenerRutaArchivo(nivel, "activado.txt"), ios::out);
        if (nomArch.is_open()) {
            nomArch.close();
        }
    }

    void CrearNivel(int nivel, Controladora^ controladora) {
        ifstream nomArch;
        nomArch.open(obtenerRutaArchivo(nivel, "datos.txt"), ios::in);

        if (nomArch.fail()) {
            nomArch.close();

            ofstream escritura;
            escritura.open(obtenerRutaArchivo(nivel, "datos.txt"), ios::out);
            escritura << "Cuidado!" << endl;
            escritura << "Jugador:" << " " << 350 << " " << 150 << endl;
            
            escritura << "Contaminantes:" << " " << 3 << " " << 0 << " " << 0 << endl;
            escritura << 90 << " " << 220 << endl;
            escritura << 660 << " " << 220 << endl;
            escritura << 370 << " " << 470 << endl;
            escritura.close();

            nomArch.open(obtenerRutaArchivo(nivel, "datos.txt"), ios::in);
        }

        string comentario;
        std::getline(nomArch, comentario);
        float posX, posY;

        nomArch >> comentario >> posX >> posY;
        controladora->GetObjJugador()->GetArea()->SetX(posX);
        controladora->GetObjJugador()->GetArea()->SetY(posY);

        int cantidadTipo1, cantidadTipo2, cantidadTipo3;
        nomArch >> comentario >> cantidadTipo1 >> cantidadTipo2 >> cantidadTipo3;
        for (int i = 0; i < cantidadTipo1; i++) {
            nomArch >> posX >> posY;
            Contaminante* conta = new Contaminante(20, posX, posY, Tipo1);
            controladora->GetArrContaminante()->AgregarContaminante(conta);
        }
        for (int i = 0; i < cantidadTipo2; i++) {
            nomArch >> posX >> posY;
            Contaminante* conta = new Contaminante(20, posX, posY, Tipo2);
            controladora->GetArrContaminante()->AgregarContaminante(conta);
        }
        for (int i = 0; i < cantidadTipo3; i++) {
            nomArch >> posX >> posY;
            Contaminante* conta = new Contaminante(20, posX, posY, Tipo3);
            controladora->GetArrContaminante()->AgregarContaminante(conta);
        }

    }

};
