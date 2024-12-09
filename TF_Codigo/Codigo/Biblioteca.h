#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <list>
// Trasnfomar String a string

// namespaces
using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic; // Para la lista
using namespace System::Drawing::Imaging; 
using namespace System::Media;

// Enums
enum Direccion { Arriba, Abajo, Izquierda, Derecha, Ninguno };
enum FasesArboles { Fase1, Fase2, Fase3, Fase4, Fase5 };

enum TipoArboles { TResourceTree, TBulletTree, THealthTree };
enum EstadoArboles { Reposo, Fructuacion };
enum TipoRecurso { Semilla, Agua, Residuo };
enum TipoContaminante { Tipo1, Tipo2, Tipo3 };

enum AccionesEnemigo1y2{CaminarIzq, CaminarDer, CaminarIzqDñ, CaminarDerDñ, MorirIzq, MorirDer};
enum Enemigo3Acc {SinDaño, Daño1, Daño2, Daño3, Daño4};
const int AnchoZona = 120;
const int AltoZona = 90;
struct JugadorArchivo {
    char tiempo[19];
    char nombre[11];
    int puntaje;
};
const unsigned int TiempoPoderBalasInfinitas = 10000;
const unsigned int TiempoPoderVidas = 400;
const unsigned int TiempoPoderRecursos = 10000;
const unsigned int AumentoVidasPoder = 50;


const unsigned int NumeroFases = 5;

const int numeroVidasJugador = 100;
