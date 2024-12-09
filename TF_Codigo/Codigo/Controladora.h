#pragma once
#include "ArrAliado.h"
#include "ArrRecurso.h"
#include "ArrDatoRecurso.h"
#include "Jugador.h"
#include "SeccionArboles.h"
#include "ArrBalaJugador.h"
#include "ArrContaminante.h"
#include "PoderBalasInfinitas.h"
#include "PoderVidas.h"
#include "PoderRecursos.h"
#include "DatoArbol.h"
ref class Controladora {
private:
	ArrAliado* objArrAliado;  
	ArrRecurso* objArrRecurso;
	Jugador* objJugador;
	SeccionArboles^ objSeccionArboles;
	ArrBalaJugador* arrBalaJugador; 
	ArrDatoRecurso* arrDatoRecurso;
	
	PoderBalasInfinitas* poderBalasInfinitas;
	PoderVidas* poderVidas;
	PoderRecursos* poderRecursos;


	ArrBala* arrBalaEnemigo;
	ArrContaminante* contaminanteArr;

	DatoArbol* objDatoArbol;

	int ultimoVezGeneradoRecurso;
	int intervaloGeneracionRecurso;
	const int distanciaBotonJugador = 150;

	Bitmap^ bmpJugador; 
	Bitmap^ imgAliado; 
	Bitmap^ bmpDatoCorazon; 
	Bitmap^ bmpBala;
	Bitmap^ bmpBalaRecargando;
	Bitmap^ bmpBalaSinBala;
	Bitmap^ bmpDatoBala; 
	Bitmap^ bmpRecursoDatoSemilla, ^ bmpRecursoDatoAgua, ^ bmpRecursoDatoResiduo;
	Bitmap^ bmpPoderBalasInfinitas;
	Bitmap^ bmpPoderVidas;
	Bitmap^ bmpPoderRecursos;


	Bitmap^ bmpContaminante1;
	Bitmap^ bmpContaminante2;
	Bitmap^ bmpContaminante3;
	Bitmap^ bmpEnemigo1;
	Bitmap^ bmpEnemigo2;
	Bitmap^ bmpEnemigo3;

public:
	Controladora(Graphics^ g) {
		bmpJugador = gcnew Bitmap("..\\SpriteFinalizados\\Png\\PatoTopDownSolo.png");
		imgAliado = gcnew Bitmap("..\\SpriteFinalizados\\Png\\AliadoTopDown.png");
		bmpDatoCorazon = gcnew Bitmap("..\\SpriteFinalizados\\Png\\Vida.png"); 
		bmpBala = gcnew Bitmap("..\\SpriteFinalizados\\Png\\DisparoMapa.png");
		bmpDatoBala = gcnew Bitmap("..\\SpriteFinalizados\\Png\\Bala.png"); 

		bmpRecursoDatoSemilla = gcnew Bitmap("..\\SpriteFinalizados\\Png\\DatoSemilla.png");
		bmpRecursoDatoAgua = gcnew Bitmap("..\\SpriteFinalizados\\Png\\DatoAgua.png");
		bmpRecursoDatoResiduo = gcnew Bitmap("..\\SpriteFinalizados\\Png\\DatoResiduo.png");


		bmpPoderBalasInfinitas = gcnew Bitmap("..\\SpriteFinalizados\\Poderes\\MunicioInfinita.png");
		bmpPoderVidas = gcnew Bitmap("..\\SpriteFinalizados\\Poderes\\RecuperarVida.png");
		bmpPoderRecursos = gcnew Bitmap("..\\SpriteFinalizados\\Poderes\\DobleRecurso.png");

		bmpContaminante1= gcnew Bitmap("..\\SpriteFinalizados\\Png\\BarrilNormalToast.png");
		bmpContaminante2 = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BarrilCrawlerToast.png");
		bmpContaminante3 = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BarrilTankDuck.png");

		bmpEnemigo1= gcnew Bitmap ("..\\SpriteFinalizados\\Png\\NormalToast.png");
		bmpEnemigo2= gcnew Bitmap("..\\SpriteFinalizados\\Png\\CrawlerToast.png");
		bmpEnemigo3 = gcnew Bitmap("..\\SpriteFinalizados\\Png\\TopDownTankDuck.png");

		objArrAliado = new ArrAliado();
		objArrRecurso = new ArrRecurso();
		objJugador = new Jugador(100, 300);
		ultimoVezGeneradoRecurso = 0;
		intervaloGeneracionRecurso = 5000;
		objSeccionArboles = gcnew SeccionArboles(37,10);
		arrBalaJugador = new ArrBalaJugador(); 
		arrDatoRecurso = new ArrDatoRecurso(390, 650);

		arrBalaEnemigo=new ArrBala();
	    contaminanteArr=new ArrContaminante();
		/*
		Contaminante* conta1 = new Contaminante(20, 100, 300, Tipo1);
		Contaminante* conta2 = new Contaminante(20, 500, 400, Tipo2);
		Contaminante* conta3 = new Contaminante(20,700, 300, Tipo3);
		contaminanteArr->AgregarContaminante(conta1);
		contaminanteArr->AgregarContaminante(conta2);
		contaminanteArr->AgregarContaminante(conta3);
		*/
		poderBalasInfinitas = new PoderBalasInfinitas(arrBalaJugador);
		poderVidas = new PoderVidas();
		poderRecursos = new PoderRecursos();

		objDatoArbol = new DatoArbol(g); 
	}

	~Controladora() {
		delete objArrAliado, objJugador, objSeccionArboles, arrBalaJugador, arrBalaEnemigo, arrBalaEnemigo;
		delete objArrRecurso, arrDatoRecurso, contaminanteArr;
		delete bmpJugador, imgAliado, bmpDatoCorazon, bmpBala, bmpDatoBala, bmpRecursoDatoAgua, bmpRecursoDatoResiduo, bmpRecursoDatoSemilla;
		delete bmpContaminante1, bmpContaminante2, bmpContaminante3, bmpEnemigo1, bmpEnemigo2, bmpEnemigo3;
		delete poderBalasInfinitas, poderVidas, poderRecursos;
		delete bmpBalaRecargando, bmpBalaSinBala;
		delete objDatoArbol;
	}

	void Mostrar(BufferedGraphics^ buffer, Graphics^ g) {
		poderBalasInfinitas->ActualizarEstadoImagen(arrBalaJugador, objSeccionArboles->getArr()[1]);
		poderVidas->ActualizarEstadoImagen(objJugador->getVida(), objSeccionArboles->getArr()[2]);
		poderRecursos->ActualizarEstadoImagen(arrDatoRecurso, objSeccionArboles->getArr()[0]);
		objDatoArbol->AumentarPorcentaje(objSeccionArboles);

		poderBalasInfinitas->Mostrar(buffer, bmpPoderBalasInfinitas, g);
		poderVidas->Mostrar(buffer, bmpPoderVidas, g);
		poderRecursos->Mostrar(buffer, bmpPoderRecursos, g);
		contaminanteArr->ProcesarMovimientos(objJugador);
		contaminanteArr->MostrarContaminantesyEnemigos(buffer, bmpContaminante1, bmpEnemigo1, bmpContaminante2, bmpEnemigo2, bmpContaminante3, bmpEnemigo3);

		arrBalaEnemigo->moverTodo();
		arrBalaEnemigo->mostrarTodoBasico(buffer);
		ColisionJugadorRecurso(); 
		ColisionJugadorAliado();
		Colisiones();
		objArrAliado->Mostrar(buffer, imgAliado);
		objArrRecurso->Mostrar(buffer,g); 
		objSeccionArboles->Mostrar(buffer,g); 
		arrDatoRecurso->Mostrar(buffer, bmpRecursoDatoSemilla, bmpRecursoDatoAgua, bmpRecursoDatoResiduo, g);

		arrBalaJugador->aumentarTiempoBala();
		arrBalaJugador->moverTodo();
		arrBalaJugador->mostrarTodo(buffer, bmpBala, bmpDatoBala, g);

		objDatoArbol->mostrar(buffer, g);

		objJugador->mostrar(buffer, bmpJugador, bmpDatoCorazon, g); 
		objJugador->Mover();
		GenerarRecursoAlea(g); 
	}

	void GenerarAliado(Keys tecla, Area* AreaJugador) {
		if (tecla == Keys::Q) {
			int cantidad = arrDatoRecurso->GetArr()[2]->getCantidad();
			int AliadoY = 0;
			if (cantidad > 0) {
				int diferencia = ((2 * (objArrAliado->GetArr().size() + 1)) + AreaJugador->GetAlto());
				if (diferencia > 150) diferencia = 150;

				if (AreaJugador->GetY() > AreaJugador->GetAlto() + 300) {
					AliadoY = AreaJugador->GetY() - (diferencia + 20);
				}
				else {
					AliadoY = AreaJugador->GetY() + (diferencia + 20);
				}
				arrDatoRecurso->GetArr()[2]->cantidadDisminuir();
				Aliado* nuevoAliado = new Aliado(AreaJugador->GetX(), AliadoY);
				objArrAliado->AgregarAliado(nuevoAliado);
			}
		}
	}
	void CambiarDireccionJugador(bool confirmacion ,Keys tecla) {
		if (confirmacion) {
			switch (tecla) 
			{
			case Keys::A:
				objJugador->setDireccion(Izquierda);
				break;
			case Keys::D:
				objJugador->setDireccion(Derecha);
				break;
			case Keys::W:
				objJugador->setDireccion(Arriba);
				break;
			case Keys::S:
				objJugador->setDireccion(Abajo);
				break;
			}
		}
		else {	
			objJugador->setDireccion(Ninguno);
		}

	}
	void GenerarRecursoAlea(Graphics^ g) {
		if (clock() - ultimoVezGeneradoRecurso >= intervaloGeneracionRecurso) {
			TipoRecurso tipoAleaR = TipoRecurso(rand() % 3);
			int X_Alea;
			int Y_Alea;
			int ancho = 18;
			int alto = 119;

			int limiteSuperior = (AltoZona + 1 + 30) + alto;
			int limiteInferior = g->VisibleClipBounds.Height - alto;
			int limiteDerecho = g->VisibleClipBounds.Width - ancho;
			int limiteIzquierdo = ancho;

			do {
				X_Alea = rand() % (limiteDerecho - limiteIzquierdo) + limiteIzquierdo;
				Y_Alea = rand() % (limiteSuperior - limiteInferior) + limiteSuperior;
			} while (ComprobarColisionesRecursos(new Area(X_Alea, Y_Alea, ancho, alto)));
			Recurso* nuevoRecurso = new Recurso(X_Alea, Y_Alea, tipoAleaR);
			objArrRecurso->agregarRecurso(nuevoRecurso);
			ultimoVezGeneradoRecurso = clock();
		}
	}
	//Usado solo para evitar que los recursos se generen encima de otros objetos
	bool ComprobarColisionesRecursos(Area* obj) {
		if (obj->InterseccionaCon(objJugador->GetArea())) return true;
		for each (auto rec in objArrRecurso->GetArr()) {
			if (obj->InterseccionaCon(objJugador->GetArea())) return true;
		}
		return false;
	}
	void ColisionJugadorRecurso() {
		for each (auto recurso in objArrRecurso->GetArr()) {
			if (recurso->GetArea()->InterseccionaCon(objJugador->GetArea())) {
				recurso->SetRecogidos(true);
				int indexTipo = int(recurso->getTipo());
				int aumento;
				if (arrDatoRecurso->GetPoderActivado()) {
					aumento = 6;
				}
				else {
					aumento = 3;
				}
				arrDatoRecurso->GetArr()[indexTipo]->cantidadAumentar(aumento);
			}
		}
		objArrRecurso->eliminarAutomaticamente();
	}
	void ColisionJugadorAliado() {
		int cantidadAliado = objArrAliado->GetArr().size();
		for (int i = cantidadAliado - 1; i >= 0; i--) {
			if (objJugador->GetArea()->InterseccionaCon(objArrAliado->GetArr()[i]->GetArea())) {
				objArrAliado->EliminarAliado(i);
				arrBalaJugador->getDatoBala()->cantidadAumentar(10);
			}
		}
	}
	void Colisiones() {
		//aumentar tiempo bala
		arrBalaEnemigo->aumentarTiempoBala();
		
		vector<Contaminante*> conta = contaminanteArr->GetContaminantes();
		for (auto& contamin : conta) {
			vector<Enemigo*> EnemigosArea = contamin->GetEnemigos();
			for (Enemigo* EnemigoArea : EnemigosArea) {
				// Colisión Personaje-Enemigo
				if (objJugador->GetArea()->InterseccionaCon(EnemigoArea->GetArea())) {
					objJugador->getVida()->cantidadDisminuir();
				}
				//Disparar Enemigo 3
				if (contamin->GetTipo() == TipoContaminante::Tipo3) {
					Enemigo3* enemigo3 = dynamic_cast<Enemigo3*>(EnemigoArea);
					if (enemigo3 && enemigo3->SiDisparar(objJugador)) {
						Bala* nbala = new Bala(enemigo3->GetArea()->GetCentroX(), enemigo3->GetArea()->GetCentroY(), enemigo3->GetAngulo());
						arrBalaEnemigo->añadirBala(nbala);
					}
				}
				// Colisión Contaminante-Enemigo
				bool colisiono = false;
				for (auto& contaminParaComparar : conta) {
					Area* AreaParaComparar = contaminParaComparar->GetAreaContaminada();
					if (AreaParaComparar->InterseccionaCon(EnemigoArea->GetArea())) {
						colisiono = true;
						break;
					}
				}
				if (!colisiono) {
					EnemigoArea->getVida()->cantidadDisminuir();
				}
			}
		}
		// Colisión BalaEnemiga-Jugador 
		vector<Bala*> balas = arrBalaEnemigo->getBalas();
		for (int i = balas.size() - 1; i >= 0; --i) {
			Bala* bala = balas[i];
			if (objJugador->GetArea()->InterseccionaCon(bala->GetArea())) {
				objJugador->getVida()->cantidadDisminuir();
				arrBalaEnemigo->eliminarBala(i);
			}
		}
		//Colision BalaJugador-Enemigos 
		vector<Bala*> balasJugador = arrBalaJugador->getBalas();
		for (int i = balasJugador.size() - 1; i >= 0; --i) {
			Bala* balaJugador = balasJugador[i];
			for (auto& contamin : conta) {
				vector<Enemigo*> EnemigosArea = contamin->GetEnemigos();
				for (int j = EnemigosArea.size() - 1; j >= 0; --j) {
					Enemigo* EnemigoArea = EnemigosArea[j];
					if (balaJugador->GetArea()->InterseccionaCon(EnemigoArea->GetArea())) {
						EnemigoArea->getVida()->cantidadDisminuir(10);
						arrBalaJugador->eliminarBala(i);
						break; 
					}
				}
			}
		}

	}
	Jugador* GetObjJugador() {
		return objJugador;
	}
	ArrAliado* GetArrAliado() {
		return objArrAliado;
	}
	ArrBalaJugador* GetArrBala() {
		return arrBalaJugador;
	}
	ArrBala* GetArrBalaEnemigos() {
		return arrBalaEnemigo;
	}
	ArrRecurso* GetArrRecurso() {
		return objArrRecurso;
	}
	ArrDatoRecurso* GetArrDatoRecurso() {
		return arrDatoRecurso;
	}
	SeccionArboles^ GetObjSeccionArboles() {
		return objSeccionArboles;
	}

	ArrContaminante* GetArrContaminante() {
		return contaminanteArr;
	}

	PoderBalasInfinitas* GetPoderBalasInfinitas() {
		return poderBalasInfinitas;
	}
	PoderVidas* GetPoderVidas() {
		return poderVidas;
	}
	PoderRecursos* GetPoderRecursos() {
		return poderRecursos;
	}

	void AumentarDatosZona(TipoArboles TipoZona, TipoRecurso recurso) {
		int CantidadRecursoXJugador = arrDatoRecurso->GetArr().at(recurso)->getCantidad();
		if (CantidadRecursoXJugador != 0) {
			objSeccionArboles->AumentarDatosZona(TipoZona, recurso);
			arrDatoRecurso->GetArr().at(recurso)->setCantidad(CantidadRecursoXJugador - 1);
		}
	}
	void ActualizarEstadoBotones(List<Button^>^ listBotones) {

		this->objSeccionArboles->CambiarBordesBotones(listBotones);

		int indice = 0;
		int comtador = 0;
		int indiceZona = 0;
		//Este algoritmo funciona gracias al orden conveniente en el que estan posicionados los
		//botones en listBotones
		//(0)semilla - (1)agua - (2)residuo - (3)semilla - (4)agua - (5)residuo - (6)semilla - ... - (8)residuo
		for each (auto boton in listBotones) {
			TipoRecurso indiceRecurso = TipoRecurso(indice);
			

			if (comtador < 3) {
				indiceZona = TResourceTree;
			}
			else if (comtador < 6) {
				indiceZona = TBulletTree; 
			}
			else if (comtador < 9) {
				indiceZona = THealthTree; 
			}

			auto zona = objSeccionArboles->getArr()[indiceZona];

			if (arrDatoRecurso->GetArr().at(indiceRecurso)->getCantidad() != 0 && zona->getFase()!=Fase5) { 

				int distancia = Math::Sqrt(Math::Pow(objJugador->GetArea()->GetX() - boton->Location.X, 2) + Math::Pow(objJugador->GetArea()->GetY() - boton->Location.Y, 2));
				boton->Enabled = (distancia < distanciaBotonJugador);

			}
			else {
				boton->Enabled = false;
			}

			indice >= Residuo ? indice = Semilla : indice++;
			comtador++; 
		}
	}

	void UsarPoderes(Keys tecla) {
		if (tecla == Keys::D3) {
			arrDatoRecurso->iniciarEjecucionPoder(objSeccionArboles->getArr()[TResourceTree]);
			objSeccionArboles->UsarPoderes(TipoArboles::TResourceTree);
		}

		else if (tecla == Keys::D2) {
			arrBalaJugador->inciarEjecucionPoder(objSeccionArboles->getArr()[TBulletTree]);
			objSeccionArboles->UsarPoderes(TipoArboles::TBulletTree);
		}

		else if (tecla == Keys::D1) {
			poderVidas->iniciarEjecucionPoder(objSeccionArboles->getArr()[THealthTree]);
			objJugador->getVida()->inciarEjecucionPoder(objSeccionArboles->getArr()[THealthTree]);
			objSeccionArboles->UsarPoderes(TipoArboles::THealthTree);
		}
	}

	bool victoria() {
		return objDatoArbol->ganar();
	}
};