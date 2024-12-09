#pragma once
#include "FormBase.h"

public ref class FormularioGameOver : public FormBase {
private:
    Button^ btnSalir;
    Label^ label;
    String^ btnFondoSuelto, ^ btnFondoPresionado;

public:
    FormularioGameOver(String^ muerte) : FormBase("..\\Musica\\GameOver.wav", false) {

        btnFondoSuelto = "..\\SpriteFinalizados\\Mapa\\Ranking\\BotonAceptarSuelto.png";
        btnFondoPresionado = "..\\SpriteFinalizados\\Mapa\\Ranking\\BotonAceptarPresionado.png";

        this->ClientSize = Drawing::Size(578, 298);
        this->BackgroundImage = Image::FromFile("..\\Fondos\\FondoYouLose.png");

        label = gcnew Label();
        String^ textoMuerte = "Te mató: " + muerte;
        label->Text = textoMuerte;
        label->Font = gcnew Drawing::Font("Arial", 15, FontStyle::Bold);
        label->Location = Point(180, 70);
        label->ForeColor = Color::DarkRed;
        label->BackColor = Color::Transparent;
        label->Size = Drawing::Size(250, 30);


        this->btnSalir = gcnew Button();
        this->btnSalir->Text = "Salir";
        this->btnSalir->Location = Point(254, 270);
        this->btnSalir->Size = Drawing::Size(70, 22);
        this->btnSalir->BackgroundImage = Image::FromFile(this->btnFondoSuelto);
        this->btnSalir->MouseEnter += gcnew System::EventHandler(this, &FormularioGameOver::Salir_MouseEnter);
        this->btnSalir->MouseLeave += gcnew System::EventHandler(this, &FormularioGameOver::Salir_MouseLeave);
        this->btnSalir->FlatStyle = FlatStyle::Popup;
        this->btnSalir->Click += gcnew EventHandler(this, &FormularioGameOver::btnSalir_Click);
        this->btnSalir->ForeColor = Color::White;
        this->Name = L"Game Over!";
        this->Text = L"Game Over!";

        this->Controls->Add(label);
        this->Controls->Add(btnSalir);
    }

    ~FormularioGameOver() {
        delete btnSalir, label, btnFondoPresionado, btnFondoSuelto;
    }

private:
    System::Void btnSalir_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    private: System::Void Salir_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
        this->btnSalir->Image = Image::FromFile(this->btnFondoPresionado);
    }
    private: System::Void Salir_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
        this->btnSalir->Image = nullptr;
    }

};
