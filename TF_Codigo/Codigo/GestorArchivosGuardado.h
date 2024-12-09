#pragma once
#include "GestorArchivos.h"
#include "Controladora.h"

public ref class GestorArchivosGuardado : public GestorArchivos {

public:
    // Cargar el ranking de un nivel específico

    bool verificarNivel(int nivel) {
        ifstream nomArch;
        nomArch.open(obtenerRutaArchivo(nivel, "guardado.txt"), ios::in);
        if (nomArch.is_open()) {
            nomArch.close();
            return true;
        }
        return false;
    }

    void CargarNivel(int nivel, int& tiempo, int& puntaje, Controladora^ controladora) {
        ifstream nomArch;
        nomArch.open(obtenerRutaArchivo(nivel, "guardado.txt"), ios::in);

        if (nomArch.is_open()) {
            string comentario;
            float posX, posY, angulo;
            int cantidad;
            
            // Personahe
            nomArch >> comentario >> posX >> posY >> angulo >> cantidad;
            controladora->GetObjJugador()->GetArea()->SetX(posX);
            controladora->GetObjJugador()->GetArea()->SetY(posY);
            controladora->GetObjJugador()->getVida()->setCantidad(cantidad);
            controladora->GetObjJugador()->setAngulo(angulo);

            int booleanoPoderVida;
            int tiempoActualPoderVida, ultimaVez;
            nomArch >> ultimaVez >> booleanoPoderVida >> tiempoActualPoderVida;
            controladora->GetObjJugador()->getVida()->setDatoVida(bool(booleanoPoderVida), ultimaVez, tiempoActualPoderVida);

            int cantidadBalasMapa, cantidadBalasTotal, tiempoBalas;
            bool disponibleArma;
            nomArch >> comentario >> cantidadBalasMapa >> cantidadBalasTotal >> tiempoBalas >> disponibleArma;
            for (int i = 0; i < cantidadBalasMapa; i++) {
                nomArch >> posX >> posY >> angulo;
                controladora->GetArrBala()->setDisponible(true);
                controladora->GetArrBala()->añadirBala(new Bala(posX, posY, angulo));
            }
            controladora->GetArrBala()->getDatoBala()->setCantidad(cantidadBalasTotal);
            controladora->GetArrBala()->setTiempoBala(tiempoBalas);
            controladora->GetArrBala()->setDisponible(disponibleArma);

            //Recursos
            int cantidadDatoRecursos = 0, cantidadRecursos = 0;
            int tipoRecurso;
            nomArch >> comentario >> cantidadRecursos >> cantidadDatoRecursos;
            for (int i = 0; i < cantidadDatoRecursos; i++) { // Datos
                nomArch >> cantidad;
                controladora->GetArrDatoRecurso()->GetArr()[i]->setCantidad(cantidad);
            }
            for (int i = 0; i < cantidadRecursos; i++) {
                nomArch >> posX >> posY >> tipoRecurso;
                controladora->GetArrRecurso()->agregarRecurso(new Recurso(posX, posY, static_cast<TipoRecurso>(tipoRecurso)));
            }

            //Aliados
            int cantidadAliados;
            nomArch >> comentario >> cantidadAliados;
            for (int i = 0; i < cantidadAliados; i++) {
                nomArch >> posX >> posY;
                controladora->GetArrAliado()->AgregarAliado(new Aliado(posX, posY));
            }

            int cantidadContamiantes;
            int tipoContaminante, tiempoActual;
            int ancho, alto;
            int booleano; // Booleano guardado como entero
            int cuadroAnimacion, cantidadEnemigos;
            int cantidadVida, booleanoConstante;

            int booleanoTeletransportacion;
            int cantidadTiempoTeletransportacion, tiempoActualEnemigo;

            nomArch >> comentario >> cantidadContamiantes;
            for (int i = 0; i < cantidadContamiantes; i++) {
                nomArch >> tipoContaminante >> tiempoActual;
                nomArch >> posX >> posY >> alto >> ancho;
                controladora->GetArrContaminante()->GetContaminantes()[i]->SetTiempoActual(tiempoActual);
                controladora->GetArrContaminante()->GetContaminantes()[i]->GetAreaContaminada()->SetArea(posX, posY, ancho, alto);

                nomArch >> booleano >> cuadroAnimacion >> cantidadEnemigos;
                controladora->GetArrContaminante()->GetContaminantes()[i]->SetEnAnimacion(bool(booleano));
                controladora->GetArrContaminante()->GetContaminantes()[i]->SetCuadroAnimacion(cuadroAnimacion);
                for (int j = 0; j < cantidadEnemigos; j++) {
                    nomArch >> booleano >> cuadroAnimacion >> cantidadVida >> booleanoConstante >> posX >> posY;
                    controladora->GetArrContaminante()->GetContaminantes()[i]->AgregarEnemigo();
                    if (tipoContaminante == Tipo2) {
                        auto enemigoTipo2 = dynamic_cast<Enemigo2*>(controladora->GetArrContaminante()->GetContaminantes()[i]->GetEnemigos()[j]);
                        if (enemigoTipo2) {
                            nomArch >> booleanoTeletransportacion >> cantidadTiempoTeletransportacion >> tiempoActualEnemigo;
                            enemigoTipo2->setDatos(bool(booleano), cuadroAnimacion, cantidadVida, bool(booleanoConstante), posX, posY, bool(booleanoTeletransportacion), cantidadTiempoTeletransportacion, tiempoActualEnemigo);
                        }
                    }
                    else {
                        controladora->GetArrContaminante()->GetContaminantes()[i]->GetEnemigos()[j]->setDatos(bool(booleano), cuadroAnimacion, cantidadVida, bool(booleanoConstante), posX, posY);
                    }


               }
            }

            int cantidadBalasEnemigo, tiempoBalasEnemigo;
            int booleanoDisponibleArmaEnemigo;
            nomArch >> comentario >> cantidadBalasEnemigo >> tiempoBalasEnemigo >> booleanoDisponibleArmaEnemigo;
            for (int i = 0; i < cantidadBalasEnemigo; i++) {
                nomArch >> posX >> posY >> angulo;
                controladora->GetArrBalaEnemigos()->setDisponible(true);
                controladora->GetArrBalaEnemigos()->añadirBala(new Bala(posX, posY, angulo));
            }
            controladora->GetArrBalaEnemigos()->setTiempoBala(tiempoBalasEnemigo);
            controladora->GetArrBalaEnemigos()->setDisponible(bool(booleanoDisponibleArmaEnemigo));

            int cantidadZonasArboles;
            int cantidadAgua, cantidadSemilla, cantidadResiduo;
            nomArch >> comentario >> cantidadZonasArboles;
            int estadoFruto, ultimaFruta;
            for (int i = 0; i < cantidadZonasArboles; i++) {
                nomArch >> cantidadAgua >> cantidadSemilla >> cantidadResiduo >> ultimaFruta;
                controladora->GetObjSeccionArboles()->getArr()[i]->setZona(cantidadAgua, cantidadSemilla, cantidadResiduo, ultimaFruta);
                nomArch >> estadoFruto;
                controladora->GetObjSeccionArboles()->getArr()[i]->getObjArbol()->SetEstadoFruto(static_cast<EstadoArboles>(estadoFruto));
            }

            int tiempoPoder, ultimaPoder;
            int booleanoPoder;
            nomArch >> comentario >> tiempoPoder >> booleanoPoder >> ultimaPoder;
            controladora->GetPoderVidas()->setPoderVidas(tiempoPoder, ultimaPoder, booleanoPoder);

            int tiempoRestantePoder;
            nomArch >> comentario >> booleanoPoder >> ultimaPoder >> tiempoPoder >> tiempoRestantePoder;
            controladora->GetArrBala()->setPoder(ultimaPoder, tiempoPoder, tiempoRestantePoder, bool(booleanoPoder));

            nomArch >> comentario >> booleanoPoder >> ultimaPoder >> tiempoPoder >> tiempoRestantePoder;
            controladora->GetArrDatoRecurso()->setPoder(ultimaPoder, tiempoPoder, tiempoRestantePoder, bool(booleanoPoder));

            nomArch >> comentario >> tiempo;


            nomArch.close();
            remove(obtenerRutaArchivo(nivel, "guardado.txt").c_str());
        }
        
    }

    void GuardarNivel(int nivel, int tiempo, int puntaje, Controladora^ controladora) {

        string nombreArchivo = obtenerRutaArchivo(nivel, "guardado.txt");
        ofstream archivo(nombreArchivo, ios::out);

        if (archivo.is_open()) {
            // Jugador
            Jugador* jug = controladora->GetObjJugador();
            archivo << "Jugador:" << " " << jug->GetArea()->GetX() << " " << jug->GetArea()->GetY() << " " << jug->getAngulo() << " " << jug->getVida()->getCantidad() << endl;
            archivo << jug->getVida()->GetUltimaVezPoder() << " " << jug->getVida()->GetPoderActivado() << " " << jug->getVida()->GetTiempoRestante() << endl;

            // Balas
            int cantidadBalasArma = controladora->GetArrBala()->getBalas().size();
            int cantidadBalasMapa = controladora->GetArrBala()->getDatoBala()->getCantidad();
            int tiempoBalas = controladora->GetArrBala()->getTiempoActual();
            bool disponibleArma = controladora->GetArrBala()->getDisponible();
            archivo << "Balas:" << " " << cantidadBalasArma << " " << cantidadBalasMapa << " " << tiempoBalas << " " << disponibleArma << endl;
            for (Bala* bala : controladora->GetArrBala()->getBalas()) {
                archivo << bala->GetArea()->GetX() << " " << bala->GetArea()->GetY() << " " << bala->GetAngulo() << endl;
            }

            // Recursos
            int cantidadRecursos = controladora->GetArrRecurso()->GetArr().size();
            int cantidadDatoRecursos = controladora->GetArrDatoRecurso()->GetArr().size();
            archivo << "Recursos:" << " " << cantidadRecursos << " " << cantidadDatoRecursos << endl;
            // Datos
            for (int i = 0; i < cantidadDatoRecursos; i++) {
                archivo << controladora->GetArrDatoRecurso()->GetArr()[i]->getCantidad();
                if (i != cantidadDatoRecursos - 1) archivo << " ";
                else archivo << endl;
            }
            // Recursos
            for (Recurso* recurso : controladora->GetArrRecurso()->GetArr()) {
                archivo << recurso->GetArea()->GetX() << " " << recurso->GetArea()->GetY() << " " << int(recurso->getTipo()) << endl;
            }

            //Aliados
            int cantidadAliados = controladora->GetArrAliado()->GetArr().size();
            archivo << "Aliados:" << " " << cantidadAliados << endl;
            for (Aliado* aliado : controladora->GetArrAliado()->GetArr()) {
                archivo << aliado->GetArea()->GetX() << " " << aliado->GetArea()->GetY() << endl;
            }

            int cantidadContaminantes = controladora->GetArrContaminante()->GetContaminantes().size();
            
            archivo << "Contaminantes:" << " " << cantidadContaminantes << endl;
            for (int i = 0; i < cantidadContaminantes; i++) {
                Contaminante* conta = controladora->GetArrContaminante()->GetContaminantes()[i];
                archivo << int(conta->GetTipo()) << " " << conta->GetTiempoActual() << " ";
                archivo << conta->GetAreaContaminada()->GetX() << " " << conta->GetAreaContaminada()->GetY() << " " << conta->GetAreaContaminada()->GetAlto() << " " << conta->GetAreaContaminada()->GetAncho() << endl;
                archivo << conta->GetEnAnimacion() << " " << conta->GetCuadroAnimacion() << " " << conta->GetEnemigos().size() << endl;
                for (int j = 0; j < conta->GetEnemigos().size(); j++) {
                    archivo << conta->GetEnemigos()[j]->GetenDescomposicion() << " " << conta->GetEnemigos()[j]->GetCuadroDescomposicion() << " " << conta->GetEnemigos()[j]->getVida()->getCantidad() << " " << conta->GetEnemigos()[j]->getVida()->GetCantidadConstante() << endl;
                    archivo << conta->GetEnemigos()[j]->GetArea()->GetX() << " " << conta->GetEnemigos()[j]->GetArea()->GetY();
                    if (conta->GetTipo() == Tipo2) {
                        auto enemigoTipo2 = dynamic_cast<Enemigo2*>(conta->GetEnemigos()[j]);
                        if (enemigoTipo2) {
                            archivo << " " << enemigoTipo2->GetEnTeletransportacion() << " " << enemigoTipo2->getTiempoTeletrasnportacion() << " " << enemigoTipo2->getTiempoActual();
                        }
                    }
                    archivo << endl;
                    
                }
            }

            int tiempoBalasEnemigo = controladora->GetArrBalaEnemigos()->getTiempoActual();
            bool disponibleArmaEnemigo = controladora->GetArrBalaEnemigos()->getDisponible();
            int cantidadBalasEnemigo = controladora->GetArrBalaEnemigos()->getBalas().size();
            archivo << "BalasEnemigo:" << " " << cantidadBalasEnemigo << " " << tiempoBalasEnemigo << " " << disponibleArmaEnemigo << endl;
            for (Bala* bala : controladora->GetArrBalaEnemigos()->getBalas()) {
                archivo << bala->GetArea()->GetX() << " " << bala->GetArea()->GetY() << " " << bala->GetAngulo() << endl;
            }

            int cantidadZonasArboles = 3;
            archivo << "ZonasArboles:" << " " << cantidadZonasArboles << endl;
            for (int i = 0; i < 3; i++) {
                ZonaArboles^ zona = controladora->GetObjSeccionArboles()->getArr()[i];
                archivo << zona->getCantidadAgua() << " " << zona->getCantidadSemilla() << " " << zona->getCantidadResiduo() << " " << zona->GetUltimaVezProducidaFruta() << " " << int(zona->getObjArbol()->GetEstadoFruto()) << endl;
            }

            archivo << "PoderVida:" << " ";
            archivo << controladora->GetPoderVidas()->GetTiempoRestante() << " " << controladora->GetPoderVidas()->GetEjecutarAnimacion() << " " << controladora->GetPoderVidas()->GetUltimaVezPoderActivado() << endl;

            archivo << "PoderBala:" << " ";
            archivo << controladora->GetArrBala()->GetPoderActivado() << " " << controladora->GetArrBala()->GetUltimaVezPoderActivado() << " " << controladora->GetArrBala()->GetTiempoPoder() << " " << controladora->GetArrBala()->GetTiempoRestantePoder() << endl;

            archivo << "PoderRecursos:" << " ";
            archivo << controladora->GetArrDatoRecurso()->GetPoderActivado() << " " << controladora->GetArrDatoRecurso()->GetUltimaVezPoderActivado() << " " << controladora->GetArrDatoRecurso()->GetTiempoPoder() << " " << controladora->GetArrDatoRecurso()->GetTiempoRestantePoder() << endl;

            archivo << "Tiempo:" << " " << tiempo << endl;

            archivo.close();
        }
    }
};
