#pragma once
#include "FormBase.h"

public ref class FormularioNombre : public FormBase {
public: String^ NombreJugador; // Para almacenar el nombre del jugador ingresado
private:
    Button^ btnAceptar;
    String^ btnFondoSuelto, ^ btnFondoPresionado;

public:
    FormularioNombre() : FormBase("..\\Musica\\Won!.wav", false) {

       btnFondoSuelto = "..\\SpriteFinalizados\\Mapa\\Ranking\\BotonAceptarSuelto.png";
       btnFondoPresionado ="..\\SpriteFinalizados\\Mapa\\Ranking\\BotonAceptarPresionado.png";

        this->Size = Drawing::Size(585, 335);
        this->BackgroundImage = Image::FromFile("..\\Fondos\\FondoYouWin.png");

        TextBox^ textBoxNombre = gcnew TextBox();
        textBoxNombre->Location = Point(240, 240);
        textBoxNombre->Width = 100;

        Label^ label = gcnew Label();
        label->Text = "Ingrese un nickname menor o igual a 10 letras";
        label->Location = Point(180, 70);
        label->ForeColor = Color::WhiteSmoke;
        label->BackColor = Color::Transparent;
        label->Size = Drawing::Size(250, 20);
        
        
        this->btnAceptar = gcnew Button();
        this->btnAceptar->Text = "Aceptar";
        this->btnAceptar->Location = Point(254, 270);
        this->btnAceptar->Size = Drawing::Size(70, 22);
        this->btnAceptar->BackgroundImage = Image::FromFile(this->btnFondoSuelto);
        this->btnAceptar->MouseEnter += gcnew System::EventHandler(this, &FormularioNombre::Aceptar_MouseEnter);
        this->btnAceptar->MouseLeave += gcnew System::EventHandler(this, &FormularioNombre::Aceptar_MouseLeave);
        this->btnAceptar->FlatStyle = FlatStyle::Popup;
        this->btnAceptar->Click += gcnew EventHandler(this, &FormularioNombre::btnAceptar_Click);
        this->btnAceptar->ForeColor = Color::White;

        this->Controls->Add(textBoxNombre);
        this->Controls->Add(label);
        this->Controls->Add(btnAceptar);
       
        this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormularioNombre::Cierre);
        this->Name = L"Victoria!";
        this->Text = L"Victoria!";
    }

protected:
    ~FormularioNombre()
    {
        delete btnAceptar, btnFondoSuelto, btnFondoPresionado;
    }

private:
    System::Void btnAceptar_Click(System::Object^ sender, System::EventArgs^ e) {
        TextBox^ textBoxNombre = safe_cast<TextBox^>(this->Controls[0]);

        if (textBoxNombre->Text->Length > 10) {
            MessageBox::Show("El nombre no puede tener más de 10 caracteres. Intente nuevamente.", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return; // Salir de la función sin cerrar el formulario
        }

        if (String::IsNullOrWhiteSpace(textBoxNombre->Text)) {
            MessageBox::Show("No se ha colocado ningún nombre.", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return; // Salir de la función sin cerrar el formulario
        }
        
        NombreJugador = textBoxNombre->Text;
        this->DialogResult = System::Windows::Forms::DialogResult::OK; // Indicar que se ha completado
        this->Close();
    }
private: System::Void Cierre(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
    TextBox^ textBoxNombre = safe_cast<TextBox^>(this->Controls[0]);
    if (this->DialogResult != System::Windows::Forms::DialogResult::OK) {
        if (textBoxNombre->Text->Length > 10) {
            MessageBox::Show("El nombre será 'jugador' por exceder el límite.", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            NombreJugador = "Jugador";
        }
        if (String::IsNullOrWhiteSpace(textBoxNombre->Text)) {
            MessageBox::Show("No se ha colocado ningún nombre. Será 'jugador' por defecto", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            NombreJugador = "Jugador";
        }
        this->DialogResult = System::Windows::Forms::DialogResult::OK; 
    }
}

    
    private: System::Void Aceptar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
        this->btnAceptar->Image = Image::FromFile(this->btnFondoPresionado);
    }
    private: System::Void Aceptar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
        this->btnAceptar->Image = nullptr;
    }
    
};
