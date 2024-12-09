#pragma once
#include "FormCreditos.h"
#include "FormMapa.h"
#include "FormInstrucciones.h"
#include "FormBase.h"

namespace Codigo {

	public ref class JuegoMenu : public FormBase
	{
	public:
	
		JuegoMenu(void) : FormBase("..\\Musica\\Inicio.wav", true)
		{
			InitializeComponent();
		}

	private:
		SoundPlayer^ musicaFondo;
		System::ComponentModel::ComponentResourceManager^ resources;
		FormMapa^ formMapa;
		FormCreditos^ formCreditos;
		FormInstrucciones^ formInstrucciones;
		System::Windows::Forms::Button^ Jugar;
		System::Windows::Forms::Button^ Creditos;
		System::Windows::Forms::Button^ Instrucciones;
		System::Windows::Forms::Button^ Salir;
		System::ComponentModel::Container^ components;

	protected:
		~JuegoMenu()
		{
			delete resources, formMapa, formCreditos, formInstrucciones;
			if (components)
			{
				delete components;
			}
		}

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			resources = (gcnew System::ComponentModel::ComponentResourceManager(JuegoMenu::typeid));
			this->Jugar = (gcnew System::Windows::Forms::Button());
			this->Creditos = (gcnew System::Windows::Forms::Button());
			this->Instrucciones = (gcnew System::Windows::Forms::Button());
			this->Salir = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			
			// Jugar
			ConfigurarBoton(this->Jugar);
			this->Jugar->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Jugar.BackgroundImage")));
			this->Jugar->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Jugar.Image")));
			this->Jugar->Location = System::Drawing::Point(271, 316);
			this->Jugar->Name = L"Jugar";
			this->Jugar->TabIndex = 0;
			this->Jugar->Click += gcnew System::EventHandler(this, &JuegoMenu::Jugar_Click);
			
			
			// Creditos
			ConfigurarBoton(this->Creditos);
			this->Creditos->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Creditos.BackgroundImage")));
			this->Creditos->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Creditos.Image")));
			this->Creditos->Location = System::Drawing::Point(271, 395);
			this->Creditos->Name = L"Creditos";
			this->Creditos->TabIndex = 1;
			this->Creditos->Click += gcnew System::EventHandler(this, &JuegoMenu::Creditos_Click);
			
			// Instrucciones
			ConfigurarBoton(this->Instrucciones);
			this->Instrucciones->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Instrucciones.BackgroundImage")));
			this->Instrucciones->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Instrucciones.Image")));
			this->Instrucciones->Location = System::Drawing::Point(404, 316);
			this->Instrucciones->Name = L"Instrucciones";
			this->Instrucciones->TabIndex = 2;
			this->Instrucciones->Click += gcnew System::EventHandler(this, &JuegoMenu::Instrucciones_Click);

			// Salir
			ConfigurarBoton(this->Salir);
			this->Salir->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Salir.BackgroundImage")));
			this->Salir->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Salir.Image")));
			this->Salir->Location = System::Drawing::Point(404, 395);
			this->Salir->Name = L"Salir";
			this->Salir->TabIndex = 3;
			this->Salir->Click += gcnew System::EventHandler(this, &JuegoMenu::Salir_Click);

			// 
			// JuegoMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(800, 492);
			this->Controls->Add(this->Salir);
			this->Controls->Add(this->Instrucciones);
			this->Controls->Add(this->Creditos);
			this->Controls->Add(this->Jugar);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"JuegoMenu";
			this->Text = L"CuakForesta";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		System::Void OcultarImagen(Button^ boton) {
			boton->Image = nullptr;
		}
		System::Void ConfigurarBoton(Button^ boton) {
			boton->BackColor = System::Drawing::Color::Transparent;
			boton->Cursor = System::Windows::Forms::Cursors::Hand;
			boton->FlatAppearance->BorderSize = 0;
			boton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			boton->Size = System::Drawing::Size(93, 44);
			boton->MouseEnter += gcnew System::EventHandler(this, &JuegoMenu::Boton_MouseEnter);
			boton->MouseLeave += gcnew System::EventHandler(this, &JuegoMenu::Boton_MouseLeave);
		}

	private: System::Void RestaurarImagen(Button^ boton, String^ nombreImagen) {
		boton->Image = cli::safe_cast<System::Drawing::Image^>(resources->GetObject(boton->Name + L".Image"));
		delete resources;
	}

	private: System::Void Boton_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		Button^ boton = dynamic_cast<Button^>(sender);
		if (boton != nullptr && boton->Image != nullptr) {
			OcultarImagen(boton);
		}
	}
	private: System::Void Boton_MouseLeave(System::Object ^ sender, System::EventArgs ^ e) {
		Button^ boton = dynamic_cast<Button^>(sender);
		if (boton != nullptr) RestaurarImagen(boton, boton->Name);
	}
	private: System::Void Salir_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void Creditos_Click(System::Object^ sender, System::EventArgs^ e) {
		if (formCreditos == nullptr || formCreditos->IsDisposed) {
			formCreditos = gcnew FormCreditos();
		}
		this->Hide();
		formCreditos->ShowDialog();
		this->Show();
		delete formCreditos;
	}
	private: System::Void Jugar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (formMapa == nullptr || formMapa->IsDisposed) {
			formMapa = gcnew FormMapa();
		}
		this->Hide();
		formMapa->ShowDialog();
		this->Show();
		delete formMapa;
		this->isPlaying = false;
		this->AlternarMusica();
	}
	private: System::Void Instrucciones_Click(System::Object^ sender, System::EventArgs^ e) {
		if (formInstrucciones == nullptr || formInstrucciones->IsDisposed) {
			formInstrucciones = gcnew FormInstrucciones();
		}
		this->Hide();
		formInstrucciones->ShowDialog();
		this->Show();
		delete formInstrucciones;
	}

};
}
