#pragma once
#include "Juego.h"
#include "Nivel.h"
#include "GestorArchivosBinario.h"
#include "FormBase.h"

namespace Codigo {
	public ref class FormMapa : public FormBase
	{
	private:
		List<Nivel^> niveles;
		int cantidadNiveles = 4;
		GestorArchivosGenerador^ gestorGenerador;
		System::ComponentModel::ComponentResourceManager^ resources;
	public:
		FormMapa(void) : FormBase("..\\Musica\\Inicio.wav", true)
		{
			gestorGenerador = gcnew GestorArchivosGenerador();
			if (!gestorGenerador->verificarNivel(1)) gestorGenerador->activarSiguienteNivel(0);

			InitializeComponent();

			for (int i = 0; i < cantidadNiveles; i++) {
				int index = (i + 2 <= cantidadNiveles) ? i + 2 : i + 1;
				Button^ boton = dynamic_cast<Button^>(this->Controls[index]);
				niveles.Add(gcnew Nivel(i + 1, boton));
				niveles[i]->Visible = false;
				this->Controls->Add(niveles[i]);
			}
		}

	protected:
		~FormMapa()
		{
			for (int i = cantidadNiveles - 1; i >= 0; i--) {
				delete niveles[i];
			}
			delete Nivel1, Nivel2, Nivel3, Nivel4, Salir;
			delete gestorGenerador, resources;

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Nivel1;
	private: System::Windows::Forms::Button^ Nivel2;
	private: System::Windows::Forms::Button^ Nivel3;
	private: System::Windows::Forms::Button^ Nivel4;
	private: System::Windows::Forms::Button^ Salir;
	protected:

	protected:

	private:
		System::ComponentModel::Container ^components;
		

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMapa::typeid));
			this->Nivel1 = (gcnew System::Windows::Forms::Button());
			this->Nivel2 = (gcnew System::Windows::Forms::Button());
			this->Nivel3 = (gcnew System::Windows::Forms::Button());
			this->Nivel4 = (gcnew System::Windows::Forms::Button());
			this->Salir = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Nivel1
			this->Nivel1->TabIndex = 1;
			GenerarBoton(this->Nivel1);
			this->Nivel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Nivel1.BackgroundImage")));
			this->Nivel1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Nivel1.Image")));
			this->Nivel1->Location = System::Drawing::Point(16, 417);
			this->Nivel1->Name = L"Nivel1";
			
			// Nivel2
			this->Nivel2->TabIndex = 2;
			GenerarBoton(this->Nivel2);
			this->Nivel2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Nivel2.BackgroundImage")));
			this->Nivel2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Nivel2.Image")));
			this->Nivel2->Location = System::Drawing::Point(267, 388);
			this->Nivel2->Name = L"Nivel2";

			// Nivel3
			this->Nivel3->TabIndex = 3;
			GenerarBoton(this->Nivel3);
			this->Nivel3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Nivel3.BackgroundImage")));
			this->Nivel3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Nivel3.Image")));
			this->Nivel3->Location = System::Drawing::Point(484, 358);
			this->Nivel3->Name = L"Nivel3";
			
			
			// Nivel4
			this->Nivel4->TabIndex = 4;
			GenerarBoton(this->Nivel4);
			this->Nivel4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Nivel4.BackgroundImage")));
			this->Nivel4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Nivel4.Image")));
			this->Nivel4->Location = System::Drawing::Point(709, 283);
			this->Nivel4->Name = L"Nivel4";
			
			// 
			// Salir
			// 
			this->Salir->BackColor = System::Drawing::Color::Transparent;
			this->Salir->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Salir.BackgroundImage")));
			this->Salir->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Salir->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->Salir->Location = System::Drawing::Point(755, 15);
			this->Salir->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Salir->Name = L"Salir";
			this->Salir->Size = System::Drawing::Size(35, 32);
			this->Salir->TabIndex = 0;
			this->Salir->UseVisualStyleBackColor = false;
			this->Salir->Click += gcnew System::EventHandler(this, &FormMapa::Salir_Click);
			
			// 
			// FormMapa
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(800, 492);
			this->Controls->Add(this->Salir);
			this->Controls->Add(this->Nivel1);
			this->Controls->Add(this->Nivel2);
			this->Controls->Add(this->Nivel3);
			this->Controls->Add(this->Nivel4);
			
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"Mapa";


			this->Text = L"Mapa";
			this->ResumeLayout(false);



		}
#pragma endregion


	private: System::Void Salir_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void OcultarImagen(Button^ boton) {
		boton->Image = nullptr;
	}
	private: System::Void GenerarBoton(Button^ boton) {
		boton->BackColor = System::Drawing::Color::Transparent;
		boton->Cursor = System::Windows::Forms::Cursors::Hand;
		boton->FlatAppearance->BorderSize = 0;
		boton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		boton->Size = System::Drawing::Size(80, 74);
		boton->MouseEnter += gcnew System::EventHandler(this, &FormMapa::Boton_MouseEnter);
		boton->MouseLeave += gcnew System::EventHandler(this, &FormMapa::Boton_MouseLeave);
		VerificarEnabled(boton);
		boton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
		boton->Click += gcnew System::EventHandler(this, &FormMapa::Nivel_Click);
	}
		   System::Void VerificarEnabled(Button^ boton) {
			   boton->Enabled = this->gestorGenerador->verificarNivel(int(boton->TabIndex));
		   }

	private: System::Void RestaurarImagen(Button^ boton, String^ nombreImagen) {
		boton->Image = cli::safe_cast<System::Drawing::Image^>(resources->GetObject(boton->Name + L".Image"));
	}

	private: System::Void Boton_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		Button^ boton = dynamic_cast<Button^>(sender);
		if (boton != nullptr) OcultarImagen(boton);
	}
	private: System::Void Boton_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		Button^ boton = dynamic_cast<Button^>(sender);
		if (boton != nullptr) RestaurarImagen(boton, boton->Name);
	}
	private: System::Void Nivel_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ boton = dynamic_cast<Button^>(sender);
		if (boton != nullptr) {
			int indiceNivel = safe_cast<int>(boton->TabIndex) - 1;
			for (int i = 0; i < cantidadNiveles; i++) {
				niveles[i]->Visible = false;
			}
			niveles[indiceNivel]->Visible = !niveles[indiceNivel]->Visible;
		}
	}
};
}
