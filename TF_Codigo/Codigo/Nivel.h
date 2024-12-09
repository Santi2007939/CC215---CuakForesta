#pragma once
#include "Ranking.h"
#include "FormMapa.h"
#include "GestorArchivosBinario.h"
#include "GestorArchivosGuardado.h"
#include "GestorArchivosGenerador.h"

namespace Codigo {
	public ref class Nivel : public Panel {
	private:
		SoundPlayer^ playerJuegoSonido;
		Button^ btnJugar, ^ siguiente;        // Botón de "Jugar" que aparece al hacer hover
		Button^ btnContinuar;    // Botón de "Continuar partida" que aparece al hacer hover
		Label^ lblTitulo;
		Panel^ panelNombre, ^ panelPuntaje, ^ panelFecha;
		String^ fondo, ^ imagenJugar, ^ imagenContinuar;
		String^ imagenJugarPresionado, ^ imagenContinuarPresionado;
		Ranking* ranking;
		GestorArchivosGenerador^ gestorGenerador;
		bool activado;
		int ancho;
		int anchoBoton, largoBoton, alturaBoton;
		int borde;
		int index;

	public:
		// Constructor que recibe parámetros para personalizar el nivel
		Nivel(int _index, Button^ _siguiente)
		{
			this->ancho = 414;
			this->borde = 25;
			this->anchoBoton = 170, this->largoBoton = 30;
			this->alturaBoton = 168;
			this->index = _index;
			fondo = "..\\SpriteFinalizados\\Mapa\\Ranking\\NivelTablero.png";
			imagenContinuar = "..\\SpriteFinalizados\\Mapa\\Ranking\\BotonSeguirPartidaSuelto.png";
			imagenJugar = "..\\SpriteFinalizados\\Mapa\\Ranking\\BotonNuevaPartidaSuelto.png";
			imagenJugarPresionado = "..\\SpriteFinalizados\\Mapa\\Ranking\\BotonNuevaPartidaPresionado.png";
			imagenContinuarPresionado = "..\\SpriteFinalizados\\Mapa\\Ranking\\BotonSeguirPartidaPresionado.png";

			GestorArchivosGenerador^ gestorGenerador= gcnew GestorArchivosGenerador();
			
			InitializeComponent();
			ranking = new Ranking();
			siguiente = _siguiente;

			GestorArchivosBinario^ gestorBinario = gcnew GestorArchivosBinario();
			gestorBinario->CargarRanking(this->index, ranking->getJugadores());

			GestorArchivosGuardado^ gestorTexto = gcnew GestorArchivosGuardado();
			this->btnContinuar->Enabled = gestorTexto->verificarNivel(this->index);

			
			activado = gestorGenerador->verificarNivel(this->index);

			delete gestorBinario, gestorTexto, gestorGenerador;
		}

		~Nivel() {
			delete btnJugar, btnContinuar, lblTitulo, panelNombre, panelPuntaje, panelFecha;
			delete fondo, imagenJugar, imagenContinuar;
			delete imagenJugarPresionado, imagenContinuarPresionado;
			delete playerJuegoSonido;
			//delete ranking;
		}

	private:
		void InitializeComponent()
		{
			this->btnJugar = gcnew Button();
			this->btnContinuar = gcnew Button();
			this->lblTitulo = gcnew Label();
			this->panelNombre = gcnew Panel();
			this->panelPuntaje = gcnew Panel();
			this->panelFecha = gcnew Panel();

			// Configura el botón de jugar
			this->btnJugar->Size = Drawing::Size(anchoBoton, largoBoton);
			this->btnJugar->Location = Point(ancho - (borde + anchoBoton), alturaBoton);
			this->btnJugar->Image = Image::FromFile(this->imagenJugar);
			this->btnJugar->BackColor = Color::Transparent;
			this->btnJugar->FlatAppearance->BorderSize = 0;
			this->btnJugar->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnJugar->MouseClick += gcnew MouseEventHandler(this, &Nivel::BotonJugar_Click);
			this->btnJugar->MouseEnter += gcnew System::EventHandler(this, &Nivel::Jugar_MouseEnter);
			this->btnJugar->MouseLeave += gcnew System::EventHandler(this, &Nivel::Jugar_MouseLeave);

			// Configura el botón de reiniciar
			this->btnContinuar->Size = Drawing::Size(anchoBoton, largoBoton);
			this->btnContinuar->Location = Point(borde, alturaBoton);
			this->btnContinuar->Image = Image::FromFile(this->imagenContinuar);
			this->btnContinuar->BackColor = Color::Transparent;
			this->btnContinuar->FlatAppearance->BorderSize = 0;
			this->btnContinuar->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnContinuar->MouseEnter += gcnew System::EventHandler(this, &Nivel::Continuar_MouseEnter);
			this->btnContinuar->MouseLeave += gcnew System::EventHandler(this, &Nivel::Continuar_MouseLeave);
			this->btnContinuar->MouseClick += gcnew MouseEventHandler(this, &Nivel::BotonContinuar_Click);
			//this->btnContinuar->MouseClick += gcnew MouseEventHandler(this, &Nivel::Nivel_Jugar);

			// Configura el label de ranking
			string titulo = gestorGenerador->getNombreNivel(this->index);
			String^ tituloString= gcnew String(titulo.c_str());
			this->lblTitulo->Text = tituloString;
			this->lblTitulo->Location = Point(22, 10);
			this->lblTitulo->Font = gcnew Drawing::Font("Arial", 15, FontStyle::Bold);
			this->lblTitulo->AutoSize = false;
			this->lblTitulo->Size = Drawing::Size(390, 30);
			this->lblTitulo->TextAlign = ContentAlignment::TopCenter;

			AjustarFuente(lblTitulo);
			
			this->Controls->Add(this->lblTitulo);
			this->Controls->Add(this->btnJugar);
			this->Controls->Add(this->btnContinuar);

			// Paneles
			this->panelNombre->Size = Drawing::Size(100, 140);
			this->panelPuntaje->Size = Drawing::Size(60, 140);
			this->panelFecha->Size = Drawing::Size(150, 140);
			this->panelNombre->Location = Point(borde + 5, 16);
			this->panelPuntaje->Location = Point(borde + 140, 16);
			this->panelFecha->Location = Point(borde + 215, 16);
			this->panelNombre->Paint += gcnew PaintEventHandler(this, &Nivel::DibujarNombre);
			this->panelFecha->Paint += gcnew PaintEventHandler(this, &Nivel::DibujarFecha);
			this->panelPuntaje->Paint += gcnew PaintEventHandler(this, &Nivel::DibujarPuntaje);
			//this->panelNombre->BackColor = Color::Black;

			this->Controls->Add(this->panelNombre);
			this->Controls->Add(this->panelPuntaje);
			this->Controls->Add(this->panelFecha);

			this->Size = Drawing::Size(ancho, 209);
			this ->BackgroundImage = Image::FromFile(this->fondo);
			this->Location = Point(100, 5);
			this->BackColor = Color::Transparent;
			

			// Configuración del evento para cambiar la imagen cuando el cursor esté encima del botón
		}

		System::Void Nivel_Jugar(System::Object^ sender, MouseEventArgs^ e, bool cargar) {
			int cantidad = ranking->getJugadores().size();
			int puntajeMayor = (cantidad > 0) ? ranking->getJugadores()[0]->getPuntaje() : 0;
			Juego^ juego = gcnew Juego(index, puntajeMayor, cargar, "..\\Musica\\Nivel" + index.ToString() + ".wav");
			this->Parent->Hide();
			juego->ShowDialog();
			this->Parent->Show();
			if (juego->usuario != nullptr) {
				ranking->añadirJugador(juego->usuario);
				ActualizarRanking();

				GestorArchivosBinario^ gestor = gcnew GestorArchivosBinario();
				gestor->GuardarRanking(this->index, ranking->getJugadores());

				gestorGenerador = gcnew GestorArchivosGenerador();
				if (!gestorGenerador->verificarNivel(this->index + 1)) gestorGenerador->activarSiguienteNivel(this->index);
				delete gestor, gestorGenerador;

				siguiente->Enabled = true;
			}
			else if (!juego->derrota) {
				GestorArchivosGuardado^ gestor = gcnew GestorArchivosGuardado();
				gestor->GuardarNivel(index, juego->getTiempo(), juego->getPuntaje(), juego->getControladora());
				this->btnContinuar->Enabled = true;
				delete gestor;
			}
			playerJuegoSonido = gcnew SoundPlayer();
			playerJuegoSonido->SoundLocation = "..\\Musica\\Inicio.wav";
			playerJuegoSonido->Load();
			playerJuegoSonido->PlayLooping();
			delete juego;
		}

		System::Void BotonJugar_Click(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			Nivel_Jugar(sender, e, false); // Inicia una nueva partida
		}

		System::Void BotonContinuar_Click(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			Nivel_Jugar(sender, e, true); // Continúa la partida guardada
		}

		System:: Void AjustarFuente(Label^ label) {
			// Obtén el texto y el tamaño del Label
			String^ texto = label->Text;
			Drawing::SizeF textSize;
			Graphics^ g = label->CreateGraphics();

			// Inicializa con una fuente base
			float tamaño = label->Font->Size;
			System::Drawing::Font^ textoFuente = label->Font;

			// Recalcula el tamaño de la fuente hasta que el texto encaje
			while (true) {
				textoFuente = gcnew System::Drawing::Font(label->Font->FontFamily, tamaño, label->Font->Style);
				textSize = g->MeasureString(texto, textoFuente);

				// Verifica si el texto cabe dentro del Label
				if (textSize.Width <= label->Width && textSize.Height <= label->Height)
					break;

				// Reduce el tamaño de la fuente
				tamaño -= 0.5f;
				if (tamaño <= 1.0f) break; // Evitar fuentes demasiado pequeñas
			}

			// Aplica la nueva fuente al Label
			label->Font = textoFuente;
		}

		public:
			// Método para actualizar el ranking
			void ActualizarRanking() {
				panelNombre->Invalidate();
				panelFecha->Invalidate();
				panelPuntaje->Invalidate();
			}

			void DibujarNombre(Object^ sender, PaintEventArgs^ e) {
				Graphics^ g = e->Graphics;
				ranking->mostrarTodosNombre(g, panelNombre); // Altura arbitraria, ajusta según desees
			}

			void DibujarFecha(Object^ sender, PaintEventArgs^ e) {
				Graphics^ g = e->Graphics;
				ranking->mostrarTodosFecha(g, panelFecha); // Altura arbitraria, ajusta según desees
			}

			void DibujarPuntaje(Object^ sender, PaintEventArgs^ e) {
				Graphics^ g = e->Graphics;
				ranking->mostrarTodosPuntaje(g, panelPuntaje); // Altura arbitraria, ajusta según desees
			}

			bool getActivado() {
				return this->activado;
			}

			int getIndex() {
				return this->index;
			}

		private: System::Void Jugar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
			this->btnJugar->Image = Image::FromFile(this->imagenJugarPresionado);
		}
		private: System::Void Jugar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
			this->btnJugar->Image = Image::FromFile(this->imagenJugar);
		}
		private: System::Void Continuar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
			this->btnContinuar->Image = Image::FromFile(this->imagenContinuarPresionado);
		}
		private: System::Void Continuar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
			this->btnContinuar->Image = Image::FromFile(this->imagenContinuar);
		}
	};


}
