#pragma once
#include <fstream>
#include "Biblioteca.h"
using namespace System::IO;

public ref class GestorArchivos {
public:
    string obtenerRutaArchivo(int nivel, String^ _nombre_ruta) {
        if (nivel == 5) return "";
        String^ carpetaNivel = ".\\Datos\\nivel" + nivel;

        // Crear la carpeta del nivel si no existe
        if (!Directory::Exists(carpetaNivel)) {
            if (!Directory::Exists(".\\Datos")) Directory::CreateDirectory(".\\Datos");
        }
        Directory::CreateDirectory(carpetaNivel);

        String^ rutaCompleta = Path::Combine(carpetaNivel, _nombre_ruta);


        int longitud = rutaCompleta->Length;
        string ruta = "";
        for (int i = 0; i < longitud; i++) {
            ruta += char(rutaCompleta[i]);
        }
        delete rutaCompleta;
        return ruta;
    }

public:
    // Cargar el ranking de un nivel específico
   
};
