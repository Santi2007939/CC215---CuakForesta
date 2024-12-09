#pragma once
#include "Biblioteca.h"

namespace Codigo {

	public ref class PanelPausa : public Panel {
	private:
		String^ fondo, ^ imagenContinuar, ^ imagenSalirNivel;
		String^ imagenContinuarPresionado, ^ imagenSalirNivelPresionado;

		int ancho, alto;
		int anchoBoton, largoBoton, alturaBoton;
		int borde;

	public:
		Button^ btnContinuar, ^ btnSalirNivel;    // Botón de "Continuar partida" que aparece al hacer hover

	public:
		// Constructor que recibe parámetros para personalizar el nivel
		PanelPausa()
		{
			this->ancho = 251;
			this->alto = 119;
			this->borde = 55;
			this->anchoBoton = 40; this->largoBoton = 40;
			this->alturaBoton = 54;

			fondo = "..\\SpriteFinalizados\\Pausa\\MenuPausa.png";
			imagenContinuar = "..\\SpriteFinalizados\\Pausa\\BotonContinuarSuelto.png";
			imagenSalirNivel = "..\\SpriteFinalizados\\Pausa\\BotonSalirSuelto.png";
			imagenSalirNivelPresionado = "..\\SpriteFinalizados\\Pausa\\BotonSalirPresionado.png";
			imagenContinuarPresionado = "..\\SpriteFinalizados\\Pausa\\BotonContinuarPresionado.png";

			InitializeComponent();
			
		}

		~PanelPausa() {
			delete fondo, imagenContinuar, imagenSalirNivel;
			delete imagenContinuarPresionado, imagenSalirNivelPresionado;
			delete btnContinuar, btnSalirNivel;
		}

	private:
		void InitializeComponent()
		{
			this->btnContinuar = gcnew Button();
			this->btnSalirNivel = gcnew Button();

			// Configura el botón de jugar
			this->btnContinuar->Size = Drawing::Size(anchoBoton, largoBoton);
			this->btnContinuar->Location = Point(ancho - (borde + anchoBoton) + 2, alturaBoton);
			this->btnContinuar->BackgroundImage = Image::FromFile(this->imagenContinuar);
			this->btnContinuar->BackColor = Color::Transparent;
			this->btnContinuar->FlatAppearance->BorderSize = 0;
			this->btnContinuar->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			
			this->btnContinuar->MouseEnter += gcnew System::EventHandler(this, &PanelPausa::Continuar_MouseEnter);
			this->btnContinuar->MouseLeave += gcnew System::EventHandler(this, &PanelPausa::Continuar_MouseLeave);

			// Configura el botón de reiniciar
			this->btnSalirNivel->Size = Drawing::Size(anchoBoton, largoBoton);
			this->btnSalirNivel->Location = Point(borde, alturaBoton);
			this->btnSalirNivel->BackgroundImage = Image::FromFile(this->imagenSalirNivel);
			this->btnSalirNivel->BackColor = Color::Transparent;
			this->btnSalirNivel->FlatAppearance->BorderSize = 0;
			this->btnSalirNivel->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnSalirNivel->MouseEnter += gcnew System::EventHandler(this, &PanelPausa::SalirNivel_MouseEnter);
			this->btnSalirNivel->MouseLeave += gcnew System::EventHandler(this, &PanelPausa::SalirNivel_MouseLeave);
			//this->btnContinuar->MouseClick += gcnew MouseEventHandler(this, &Nivel::Nivel_Jugar);
			

			this->Size = Drawing::Size(ancho,alto);
			this->BackgroundImage = Image::FromFile(this->fondo);
			
			this->BackColor = Color::Transparent;

			this->Visible = false;
			// Configuración del evento para cambiar la imagen cuando el cursor esté encima del botón
		}

	private: System::Void Continuar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		this->btnContinuar->Image = Image::FromFile(this->imagenContinuarPresionado);
	}
	private: System::Void Continuar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		this->btnContinuar->Image = nullptr;
	}
	private: System::Void SalirNivel_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		this->btnSalirNivel->Image = Image::FromFile(this->imagenSalirNivelPresionado);
	}
	private: System::Void SalirNivel_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		this->btnSalirNivel->Image = nullptr;
	}
	};


}
