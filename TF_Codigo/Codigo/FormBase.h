#pragma once
#include "Biblioteca.h"

public ref class FormBase : public Form {
protected:
    SoundPlayer^ player;
    String^ rutaArchivo;
    bool isPlaying;
    bool infinito;

public:
    FormBase(String^ _rutaArchivo, bool _infinito) {
        player = gcnew SoundPlayer();
        isPlaying = false;
        rutaArchivo = _rutaArchivo;
        infinito = _infinito;

        // Evento de carga del formulario
        this->Load += gcnew EventHandler(this, &FormBase::OnFormLoad);

        // Evento para capturar teclas
        this->KeyDown += gcnew KeyEventHandler(this, &FormBase::OnKeyDown);
        this->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &FormBase::FormBase_PreviewKeyDown);
        this->KeyPreview = true;
        this->Shown += gcnew EventHandler(this, &FormBase::OnFormShown);
        this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormBase::CierreForm);
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        this->Icon = gcnew System::Drawing::Icon("..\\SpriteFinalizados\\logo.ico");
    }

    ~FormBase() {
        delete player, rutaArchivo;
    }

    // Método para cargar y reproducir música
    void CargarYReproducirMusica() {
        try {
            player->SoundLocation = rutaArchivo;
            player->Load();   
            if (infinito) player->PlayLooping();
            else player->Play();
            isPlaying = true;
        }
        catch (Exception^ e) {
            MessageBox::Show("Error al cargar la música: " + e->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    // Método para detener la música
    void DetenerMusica() {
        if (isPlaying) {
            player->Stop();
            isPlaying = false;
        }
    }

    // Método para alternar música (pausar/reanudar)
    void AlternarMusica() {
        if (isPlaying) {
            DetenerMusica();
        }
        else {
            player->PlayLooping();
            isPlaying = true;
        }
    }

    void ejecutarSonidoBase() {
        try {
            player->SoundLocation = "..\\Musica\\Inicio.wav";
            player->Load();
            player->PlayLooping();
            isPlaying = true;
        }
        catch (Exception^ e) {
            MessageBox::Show("Error al cargar la música: " + e->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        
    }

private:
    // Evento de carga del formulario
    void OnFormLoad(Object^ sender, EventArgs^ e) {
        CargarYReproducirMusica();
    }

   
    void OnFormShown(Object^ sender, EventArgs^ e) {
        this->Focus();
        isPlaying = true;
        if (!isPlaying) { // Verifica si la música no está activa
            if (infinito) player->PlayLooping();
            else player->Play();
            isPlaying = true;
        }
    }
    
    void FormBase_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e) {
        if (e->KeyCode == Keys::M) {
            e->IsInputKey = true;
        }

    }

    // Evento para detectar la tecla M
    void OnKeyDown(Object^ sender, KeyEventArgs^ e) {
        if (e->KeyCode == Keys::M && infinito) {
            AlternarMusica();
        }
    }

    System::Void CierreForm(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
        DetenerMusica();
    }
};
