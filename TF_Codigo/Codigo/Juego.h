#pragma once
#include "Jugador.h"
#include "ArrBala.h"
#include "FormNombre.h"
#include "Persona.h"
#include "Controladora.h"
#include "DatoTexto.h"
#include "PanelPausa.h"
#include "GestorArchivosGuardado.h"
#include "GestorArchivosGenerador.h"
#include "FormularioGameOver.h"
#include "FormBase.h"

namespace Codigo {
	//ref class PanelPausa;

	public ref class Juego : public FormBase
	{
	public:
		Persona* usuario;
		bool derrota;
	private:
		Graphics^ g;
		PanelPausa^ panelPausa;
		bool pausa;
		int puntajeMayor;
		DatoTexto* tiempo, *puntaje, *record;
	
		Bitmap^ bmpFondo;
		List<Bitmap^> bmpCursores;
		Controladora^ objControladora;

		List<Button^>^ listBotones; 
		
		Bitmap^ bmpDatoCorazon;
		/*
		Bitmap^ bmpEnemy;
		Bitmap^ bmpMap;
		Bitmap^ bmpBullet;
		Hero* hero;
		Controller* controller;
		*/
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ btnAguaZonaResourceTree;
	private: System::Windows::Forms::Button^ btnResiduoZonaResourceTree;
	private: System::Windows::Forms::Button^ btnSemillaZonaResourceTree;
	private: System::Windows::Forms::Button^ btnAguaZonaBulletTree;
	private: System::Windows::Forms::Button^ btnResiduoZonaBulletTree;
	private: System::Windows::Forms::Button^ btnSemillaZonaBulletTree;
	private: System::Windows::Forms::Button^ btnAguaZonaHealthTree;
	private: System::Windows::Forms::Button^ btnResiduoZonaHealthTree;
	private: System::Windows::Forms::Button^ btnSemillaZonaHealthTree;
	private: System::Windows::Forms::Timer^ TiempoTemporizador;

	

	public:
		Juego(int nivel, int _puntajeMayor, bool cargar, String^ _ruta) : FormBase(_ruta, true)
		{
			derrota = false;
			this->panelPausa = gcnew PanelPausa();
			this->puntajeMayor = _puntajeMayor;
			InitializeComponent();
			Graphics^ g = this->CreateGraphics();
			
			bmpFondo = gcnew Bitmap("..\\Fondos\\FondoJuego.png");

			bmpDatoCorazon = gcnew Bitmap("..\\SpriteFinalizados\\Png\\Vida.png");

			record = new DatoTexto(600, 2, this->puntajeMayor, "Record", g);
			tiempo = new DatoTexto(760, 2, 200, "Tiempo", g);
			puntaje = new DatoTexto(680, 2, 0, "Puntaje", g);
	
			usuario = nullptr;
			objControladora = gcnew Controladora(g); 
			GestorArchivosGenerador^ gestorGenerador = gcnew GestorArchivosGenerador();
			gestorGenerador->CrearNivel(nivel, objControladora);

			listBotones = gcnew List<Button^>; 

			listBotones->Add(btnSemillaZonaResourceTree);
			listBotones->Add(btnAguaZonaResourceTree);
			listBotones->Add(btnResiduoZonaResourceTree);

			listBotones->Add(btnSemillaZonaBulletTree);
			listBotones->Add(btnAguaZonaBulletTree);
			listBotones->Add(btnResiduoZonaBulletTree);

			listBotones->Add(btnSemillaZonaHealthTree);
			listBotones->Add(btnAguaZonaHealthTree);
			listBotones->Add(btnResiduoZonaHealthTree);

			pausa = false;
			this->panelPausa->btnContinuar->MouseClick += gcnew MouseEventHandler(this, &Juego::Continuar_PanelPausa);
			this->panelPausa->btnSalirNivel->MouseClick += gcnew MouseEventHandler(this, &Juego::Salir_PanelPausa);
			this->panelPausa->Controls->Add(panelPausa->btnContinuar);
			this->panelPausa->Controls->Add(panelPausa->btnSalirNivel);

			this->panelPausa->Location = Point(this->ClientSize.Width / 2 - panelPausa->Width / 2, this->ClientSize.Height / 2 - panelPausa->Height / 2);
			this->Controls->Add(panelPausa);	
			InicializarPanelOpacidad();

			if (cargar) {
				GestorArchivosGuardado^ gestorTexto = gcnew GestorArchivosGuardado();
				gestorTexto->CargarNivel(nivel, tiempo->getCantidad(), puntaje->getCantidad(), objControladora);
				delete gestorTexto;
			}
		}

		void InicializarPanelOpacidad() {
			panelOpacidad = gcnew Panel();
			panelOpacidad->Size = this->ClientSize;
			panelOpacidad->BackColor = Color::FromArgb(128, Color::Black); // Opacidad con Color negro
			panelOpacidad->Visible = false;
			this->Controls->Add(panelOpacidad);
			panelOpacidad->BringToFront();
		}

		void MostrarPanelPausa() {
			panelOpacidad->Visible = true;
			panelPausa->Visible = true;
			panelPausa->BringToFront();
		}

		void OcultarPanelPausa() {
			panelOpacidad->Visible = false;
			panelPausa->Visible = false;
		}

	protected:
		~Juego()
		{
			delete objControladora, panelOpacidad;
			delete g, panelPausa;
			delete tiempo, puntaje, record;
			delete bmpFondo, listBotones, bmpDatoCorazon;

			if (components)
			{
				delete components;
			}
		}

	protected:



	private: Panel^ panelOpacidad;
	private: System::ComponentModel::IContainer^ components;

	private:


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Juego::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->TiempoTemporizador = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnAguaZonaResourceTree = (gcnew System::Windows::Forms::Button());
			this->btnResiduoZonaResourceTree = (gcnew System::Windows::Forms::Button());
			this->btnSemillaZonaResourceTree = (gcnew System::Windows::Forms::Button());
			this->btnAguaZonaBulletTree = (gcnew System::Windows::Forms::Button());
			this->btnResiduoZonaBulletTree = (gcnew System::Windows::Forms::Button());
			this->btnSemillaZonaBulletTree = (gcnew System::Windows::Forms::Button());
			this->btnAguaZonaHealthTree = (gcnew System::Windows::Forms::Button());
			this->btnResiduoZonaHealthTree = (gcnew System::Windows::Forms::Button());
			this->btnSemillaZonaHealthTree = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// TiempoTemporizador
			// 
			this->TiempoTemporizador->Enabled = true;
			this->TiempoTemporizador->Interval = 1000;
			this->TiempoTemporizador->Tick += gcnew System::EventHandler(this, &Juego::TiempoTemporizador_Tick);
			// 
			// btnAguaZonaResourceTree
			// 
			this->btnAguaZonaResourceTree->BackColor = System::Drawing::Color::Transparent;
			this->btnAguaZonaResourceTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAguaZonaResourceTree.BackgroundImage")));
			this->btnAguaZonaResourceTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnAguaZonaResourceTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAguaZonaResourceTree.Image")));
			this->btnAguaZonaResourceTree->Location = System::Drawing::Point(36, 104);
			this->btnAguaZonaResourceTree->Name = L"btnAguaZonaResourceTree";
			this->btnAguaZonaResourceTree->Size = System::Drawing::Size(26, 26);
			this->btnAguaZonaResourceTree->TabIndex = 20;
			this->btnAguaZonaResourceTree->UseVisualStyleBackColor = false;
			this->btnAguaZonaResourceTree->Click += gcnew System::EventHandler(this, &Juego::btnAguaZonaResourceTree_Click);
			this->btnAguaZonaResourceTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// btnResiduoZonaResourceTree
			// 
			this->btnResiduoZonaResourceTree->BackColor = System::Drawing::Color::Transparent;
			this->btnResiduoZonaResourceTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnResiduoZonaResourceTree.BackgroundImage")));
			this->btnResiduoZonaResourceTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnResiduoZonaResourceTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnResiduoZonaResourceTree.Image")));
			this->btnResiduoZonaResourceTree->Location = System::Drawing::Point(82, 104);
			this->btnResiduoZonaResourceTree->Name = L"btnResiduoZonaResourceTree";
			this->btnResiduoZonaResourceTree->Size = System::Drawing::Size(26, 26);
			this->btnResiduoZonaResourceTree->TabIndex = 21;
			this->btnResiduoZonaResourceTree->UseVisualStyleBackColor = false;
			this->btnResiduoZonaResourceTree->Click += gcnew System::EventHandler(this, &Juego::btnResiduoZonaResourceTree_Click);
			this->btnResiduoZonaResourceTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// btnSemillaZonaResourceTree
			// 
			this->btnSemillaZonaResourceTree->BackColor = System::Drawing::Color::Transparent;
			this->btnSemillaZonaResourceTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSemillaZonaResourceTree.BackgroundImage")));
			this->btnSemillaZonaResourceTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnSemillaZonaResourceTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSemillaZonaResourceTree.Image")));
			this->btnSemillaZonaResourceTree->Location = System::Drawing::Point(130, 104);
			this->btnSemillaZonaResourceTree->Name = L"btnSemillaZonaResourceTree";
			this->btnSemillaZonaResourceTree->Size = System::Drawing::Size(26, 26);
			this->btnSemillaZonaResourceTree->TabIndex = 22;
			this->btnSemillaZonaResourceTree->UseVisualStyleBackColor = false;
			this->btnSemillaZonaResourceTree->Click += gcnew System::EventHandler(this, &Juego::btnSemillaZonaResourceTree_Click);
			this->btnSemillaZonaResourceTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// btnAguaZonaBulletTree
			// 
			this->btnAguaZonaBulletTree->BackColor = System::Drawing::Color::Transparent;
			this->btnAguaZonaBulletTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAguaZonaBulletTree.BackgroundImage")));
			this->btnAguaZonaBulletTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnAguaZonaBulletTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAguaZonaBulletTree.Image")));
			this->btnAguaZonaBulletTree->Location = System::Drawing::Point(233, 104);
			this->btnAguaZonaBulletTree->Name = L"btnAguaZonaBulletTree";
			this->btnAguaZonaBulletTree->Size = System::Drawing::Size(26, 26);
			this->btnAguaZonaBulletTree->TabIndex = 23;
			this->btnAguaZonaBulletTree->UseVisualStyleBackColor = false;
			this->btnAguaZonaBulletTree->Click += gcnew System::EventHandler(this, &Juego::btnAguaZonaBulletTree_Click);
			this->btnAguaZonaBulletTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// btnResiduoZonaBulletTree
			// 
			this->btnResiduoZonaBulletTree->BackColor = System::Drawing::Color::Transparent;
			this->btnResiduoZonaBulletTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnResiduoZonaBulletTree.BackgroundImage")));
			this->btnResiduoZonaBulletTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnResiduoZonaBulletTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnResiduoZonaBulletTree.Image")));
			this->btnResiduoZonaBulletTree->Location = System::Drawing::Point(279, 104);
			this->btnResiduoZonaBulletTree->Name = L"btnResiduoZonaBulletTree";
			this->btnResiduoZonaBulletTree->Size = System::Drawing::Size(26, 26);
			this->btnResiduoZonaBulletTree->TabIndex = 24;
			this->btnResiduoZonaBulletTree->UseVisualStyleBackColor = false;
			this->btnResiduoZonaBulletTree->Click += gcnew System::EventHandler(this, &Juego::btnResiduoZonaBulletTree_Click);
			this->btnResiduoZonaBulletTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// btnSemillaZonaBulletTree
			// 
			this->btnSemillaZonaBulletTree->BackColor = System::Drawing::Color::Transparent;
			this->btnSemillaZonaBulletTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSemillaZonaBulletTree.BackgroundImage")));
			this->btnSemillaZonaBulletTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnSemillaZonaBulletTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSemillaZonaBulletTree.Image")));
			this->btnSemillaZonaBulletTree->Location = System::Drawing::Point(327, 104);
			this->btnSemillaZonaBulletTree->Name = L"btnSemillaZonaBulletTree";
			this->btnSemillaZonaBulletTree->Size = System::Drawing::Size(26, 26);
			this->btnSemillaZonaBulletTree->TabIndex = 25;
			this->btnSemillaZonaBulletTree->UseVisualStyleBackColor = false;
			this->btnSemillaZonaBulletTree->Click += gcnew System::EventHandler(this, &Juego::btnSemillaZonaBulletTree_Click);
			this->btnSemillaZonaBulletTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// btnAguaZonaHealthTree
			// 
			this->btnAguaZonaHealthTree->BackColor = System::Drawing::Color::Transparent;
			this->btnAguaZonaHealthTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAguaZonaHealthTree.BackgroundImage")));
			this->btnAguaZonaHealthTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnAguaZonaHealthTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAguaZonaHealthTree.Image")));
			this->btnAguaZonaHealthTree->Location = System::Drawing::Point(430, 104);
			this->btnAguaZonaHealthTree->Name = L"btnAguaZonaHealthTree";
			this->btnAguaZonaHealthTree->Size = System::Drawing::Size(26, 26);
			this->btnAguaZonaHealthTree->TabIndex = 26;
			this->btnAguaZonaHealthTree->UseVisualStyleBackColor = false;
			this->btnAguaZonaHealthTree->Click += gcnew System::EventHandler(this, &Juego::btnAguaZonaHealthTree_Click);
			this->btnAguaZonaHealthTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// btnResiduoZonaHealthTree
			// 
			this->btnResiduoZonaHealthTree->BackColor = System::Drawing::Color::Transparent;
			this->btnResiduoZonaHealthTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnResiduoZonaHealthTree.BackgroundImage")));
			this->btnResiduoZonaHealthTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnResiduoZonaHealthTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnResiduoZonaHealthTree.Image")));
			this->btnResiduoZonaHealthTree->Location = System::Drawing::Point(476, 104);
			this->btnResiduoZonaHealthTree->Name = L"btnResiduoZonaHealthTree";
			this->btnResiduoZonaHealthTree->Size = System::Drawing::Size(26, 26);
			this->btnResiduoZonaHealthTree->TabIndex = 27;
			this->btnResiduoZonaHealthTree->UseVisualStyleBackColor = false;
			this->btnResiduoZonaHealthTree->Click += gcnew System::EventHandler(this, &Juego::btnResiduoZonaHealthTree_Click);
			this->btnResiduoZonaHealthTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// btnSemillaZonaHealthTree
			// 
			this->btnSemillaZonaHealthTree->BackColor = System::Drawing::Color::Transparent;
			this->btnSemillaZonaHealthTree->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSemillaZonaHealthTree.BackgroundImage")));
			this->btnSemillaZonaHealthTree->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnSemillaZonaHealthTree->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSemillaZonaHealthTree.Image")));
			this->btnSemillaZonaHealthTree->Location = System::Drawing::Point(524, 104);
			this->btnSemillaZonaHealthTree->Name = L"btnSemillaZonaHealthTree";
			this->btnSemillaZonaHealthTree->Size = System::Drawing::Size(26, 26);
			this->btnSemillaZonaHealthTree->TabIndex = 28;
			this->btnSemillaZonaHealthTree->UseVisualStyleBackColor = false;
			this->btnSemillaZonaHealthTree->Click += gcnew System::EventHandler(this, &Juego::btnSemillaZonaHealthTree_Click);
			this->btnSemillaZonaHealthTree->GotFocus += gcnew System::EventHandler(this, &Juego::BotonPerderFoco);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(828, 720);
			this->Controls->Add(this->btnSemillaZonaHealthTree);
			this->Controls->Add(this->btnResiduoZonaHealthTree);
			this->Controls->Add(this->btnAguaZonaHealthTree);
			this->Controls->Add(this->btnSemillaZonaBulletTree);
			this->Controls->Add(this->btnResiduoZonaBulletTree);
			this->Controls->Add(this->btnAguaZonaBulletTree);
			this->Controls->Add(this->btnSemillaZonaResourceTree);
			this->Controls->Add(this->btnResiduoZonaResourceTree);
			this->Controls->Add(this->btnAguaZonaResourceTree);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Juego";
			this->Text = L"Juego";
			this->Load += gcnew System::EventHandler(this, &Juego::Juego_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::PresionarTecla);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::SoltarTecla);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Juego::Juego_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Juego::Juego_MouseMove);
			this->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &Juego::MyForm_PreviewKeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void pictureBox16_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
			Point posicionGlobalMouse = System::Windows::Forms::Cursor::Position;
			int mouseY = this->PointToClient(posicionGlobalMouse).Y;

			Graphics^ g = this->CreateGraphics();
			BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
			BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);
			buffer->Graphics->Clear(Color::White);
			buffer->Graphics->DrawImage(bmpFondo, 0, 0, bmpFondo->Width, bmpFondo->Height);

			objControladora->ActualizarEstadoBotones(listBotones); 

			tiempo->mostrar(buffer, g, Brushes::Blue, Brushes::Red, 5);
			puntaje->setCantidad(tiempo->getCantidad() * 10);
			puntaje->mostrar(buffer, g, Brushes::YellowGreen, Brushes::Blue, puntajeMayor);
			record->mostrar(buffer, g, Brushes::Blue, Brushes::Blue);
			
			objControladora->Mostrar(buffer, g); //Aqui se encuentra implementada el metodo mover y mostrar del jugador

			buffer->Render(g);

			delete buffer;
			delete espacio;
			delete g;

			if (objControladora->victoria() || tiempo->getCantidad() == 0 || objControladora->GetObjJugador()->getVida()->getCantidad() <= 0) {
				timer1->Stop();
				TiempoTemporizador->Stop();

				if (objControladora->victoria()) {
					FormularioNombre^ formNombre = gcnew FormularioNombre();
					if (formNombre->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
						usuario = new Persona(formNombre->NombreJugador, tiempo->getCantidad(), puntaje->getCantidad());
					}
					delete formNombre;
					
				}
				else {
					String^ textoMuerte = (tiempo->getCantidad() == 0) ? "El tiempo" : "Un enemigo";
					FormularioGameOver^ formOver = gcnew FormularioGameOver(textoMuerte);
					formOver->ShowDialog();
					derrota = true;
					delete formOver;
				}
				this->Close();
			}
		}

		private:
			void CambiarEstadoPausa(bool estado) {
				this->pausa = estado;
				this->panelPausa->Visible = estado;
				if (pausa) {
					timer1->Stop();
					TiempoTemporizador->Stop();
					MostrarPanelPausa();
					
				}
				else {
					timer1->Start();
					TiempoTemporizador->Start();
					OcultarPanelPausa();
					this->Focus();
				}
			}

		private: System::Void Continuar_PanelPausa(System::Object^ sender, MouseEventArgs^ e) {
			CambiarEstadoPausa(false);
		}

		private: System::Void Salir_PanelPausa(System::Object^ sender, MouseEventArgs^ e) {
			this->Close();
		}

		private: System::Void PresionarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		
			objControladora->CambiarDireccionJugador(true, e->KeyCode);

			if (e->KeyCode == Keys::Escape) {
				CambiarEstadoPausa(!pausa);
			}
		
			if (!pausa) objControladora->GenerarAliado(e->KeyCode, objControladora->GetObjJugador()->GetArea());
			
			objControladora->UsarPoderes(e->KeyCode);
		}

		private: System::Void SoltarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			objControladora->CambiarDireccionJugador(false, e->KeyCode);
		}
		private: System::Void Juego_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			// Distancia desde el centro del sprite hasta la punta del arma
			int distanciaArma = objControladora->GetObjJugador()->GetArea()->GetAncho() / 2;
		
			// Calcular las posiciones de la bala considerando la rotación del jugador
			int xInicialBala = objControladora->GetObjJugador()->GetArea()->GetCentroX() + (int)(distanciaArma) * Math::Cos(objControladora->GetObjJugador()->getAngulo());
			int yInicialBala = objControladora->GetObjJugador()->GetArea()->GetCentroY() + (int)(distanciaArma) * Math::Sin(objControladora->GetObjJugador()->getAngulo());

		
			if ((e->Y < 620 && e->Y > 144) && !pausa /* && (e->X < 814 && e->X > 14)*/) {
				objControladora->GetArrBala()->añadirBala(new Bala(xInicialBala, yInicialBala, objControladora->GetObjJugador()->getAngulo())); 
			}
		}
			   
		private: System::Void Juego_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if ((e->Y < 620 && e->Y > 144) && !pausa  /* && (e->X < 814 && e->X > 14) */) {
				objControladora->GetObjJugador()->calcularAngulo((e->X) - objControladora->GetObjJugador()->GetArea()->GetCentroX(), (e->Y) - objControladora->GetObjJugador()->GetArea()->GetCentroY());
			}
			// -17 y -20
				/*
				try {
					this->Cursor = gcnew System::Windows::Forms::Cursor(
						bmpCursores[objControladora->GetArrBala()->getEstadoArma()]->GetHicon());
				}
				catch (System::Runtime::InteropServices::ExternalException^ ex) {
					this->Cursor = Cursors::Default;
				}
				
			}
			else {
				this->Cursor = Cursors::Default; 
			}
			*/
		
			//this->Invalidate();
		}
	
		private: System::Void TiempoTemporizador_Tick(System::Object^ sender, System::EventArgs^ e) {
			tiempo->cantidadDisminuir();
		}
	

//Botones
		private: System::Void btnAguaZonaResourceTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(TResourceTree, Agua); 
		}
		private: System::Void btnResiduoZonaResourceTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(TResourceTree, Residuo); 
		}
		private: System::Void btnSemillaZonaResourceTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(TResourceTree, Semilla); 
		}
		private: System::Void btnAguaZonaBulletTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(TBulletTree, Agua);
		}
		private: System::Void btnResiduoZonaBulletTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(TBulletTree, Residuo);
		}
		private: System::Void btnSemillaZonaBulletTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(TBulletTree, Semilla);
		}
		private: System::Void btnAguaZonaHealthTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(THealthTree, Agua);
		}
		private: System::Void btnResiduoZonaHealthTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(THealthTree, Residuo);
		}
		private: System::Void btnSemillaZonaHealthTree_Click(System::Object^ sender, System::EventArgs^ e) {
			objControladora->AumentarDatosZona(THealthTree, Semilla); 
		}
	
		private: void MyForm_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e) {
			if (e->KeyCode == Keys::W || e->KeyCode == Keys::S || e->KeyCode == Keys::A || e->KeyCode == Keys::D || e->KeyCode == Keys::Escape) {
				e->IsInputKey = true;
			}

		}
		private: void BotonPerderFoco(System::Object^ sender, System::EventArgs^ e) {
			this->ActiveControl = nullptr; // Restablece el foco al formulario
		}

//Get's
		public:
			Controladora^ getControladora() {
				return this->objControladora;
			}

			int getTiempo() {
				return this->tiempo->getCantidad();
			}

			int getPuntaje() {
				return this->puntaje->getCantidad();
			}
	private: System::Void Juego_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
