#pragma once
#include "ZonaArboles.h"

ref class SeccionArboles {
private:
	int x;
	int y;
	List<ZonaArboles^>^ listZona;
	const int distanciaArboles = 77;
	const int intervaloGeneracionFruta = 10000;

	Bitmap^ imgBotonAgua;
	Bitmap^ imgBotonSemilla;
	Bitmap^ imgBotonResiduo;

	Bitmap^ imgBotonAguaRojo;
	Bitmap^ imgBotonSemillaRojo;
	Bitmap^ imgBotonResiduoRojo;



public:
	SeccionArboles(int _x, int _y) {
		x = _x;
		y = _y;
		listZona = gcnew List<ZonaArboles^>();
		ZonaArboles^ zonaResourceTree = gcnew ZonaArboles(x, y, TResourceTree);
		ZonaArboles^ zonaBulletTree = gcnew ZonaArboles((x + AnchoZona) + distanciaArboles, y, TBulletTree);
		ZonaArboles^ zonaHealthTree = gcnew ZonaArboles((x + (AnchoZona * 2)) + distanciaArboles * 2, y, THealthTree);

		listZona->Add(zonaResourceTree);
		listZona->Add(zonaBulletTree);
		listZona->Add(zonaHealthTree);

		imgBotonAguaRojo = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BotonesRecursos\\BotonAguaNecesario.png");
		imgBotonSemillaRojo = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BotonesRecursos\\BotonSemillaNecesaria.png");
		imgBotonResiduoRojo = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BotonesRecursos\\BotonResiduoNecesario.png");

		imgBotonSemilla = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BotonesRecursos\\BotonSemilla.png");
		imgBotonAgua = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BotonesRecursos\\BotonAgua.png");
		imgBotonResiduo = gcnew Bitmap("..\\SpriteFinalizados\\Png\\BotonesRecursos\\BotonResiduo.png");

	}

	~SeccionArboles() {
		delete imgBotonAgua, imgBotonSemilla, imgBotonResiduo;
		delete imgBotonAguaRojo, imgBotonSemillaRojo, imgBotonResiduoRojo;
		for (int i = 2; i >= 0; i--) {
			delete listZona[i];
		}
	}

	void Mostrar(BufferedGraphics^ buffer, Graphics^ g) {
		ActualizarEstadoFrutosArboles();
		for each (ZonaArboles ^ zona in listZona) {
			zona->Mostrar(buffer, g);
		}
	}

	List<ZonaArboles^>^ getArr() {
		return listZona;
	}

	Void AumentarDatosZona(TipoArboles TipoZona, TipoRecurso recurso) {
		for each (auto zona in listZona) {
			if (zona->getTipo() == TipoZona) {
				AumentarRecursosEnZonaX(zona, recurso);
			}
		}

	}

	//Unicamnete usado en la clase AumentarDatosZona
	Void AumentarRecursosEnZonaX(ZonaArboles^ ptrZona, TipoRecurso recurso) {
		switch (recurso)
		{
		case Semilla:	ptrZona->AgregarSemilla();
			break;
		case Agua:		ptrZona->AgregarAgua();
			break;
		case Residuo:	ptrZona->AgregarResiduo();
			break;
		default:
			break;
		}
	}

	Void ActualizarEstadoFrutosArboles() {
		for each (auto zona in listZona) {
			if (zona->getObjArbol()->GetEstadoFruto() == Reposo && zona->getFase() >= Fase3) {
				if (clock() - zona->GetUltimaVezProducidaFruta() >= intervaloGeneracionFruta) {
					zona->getObjArbol()->SetEstadoFruto(Fructuacion);
					zona->SetUltimaVezProducidaFruta(clock());
				}
			}
		}
	}

	Void UsarPoderes(TipoArboles tipoArbol) {
		if (listZona[tipoArbol]->GetEstadoFruto() == EstadoArboles::Fructuacion) {
			if (tipoArbol == TBulletTree) {
				listZona[tipoArbol]->getObjArbol()->SetEstadoFruto(Reposo);
				listZona[tipoArbol]->SetUltimaVezProducidaFruta(clock() + TiempoPoderBalasInfinitas);
			}

			else if (tipoArbol == TResourceTree) {
				listZona[tipoArbol]->getObjArbol()->SetEstadoFruto(Reposo);
				listZona[tipoArbol]->SetUltimaVezProducidaFruta(clock() + TiempoPoderRecursos);
			}

			else {
				listZona[tipoArbol]->getObjArbol()->SetEstadoFruto(Reposo);
				listZona[tipoArbol]->SetUltimaVezProducidaFruta(clock());
			}
		}

	}

	void CambiarBordesBotones(List<Button^>^ listBotones) {

		int contadorTotal = 0;
		int i = 0;

		for each (auto zona in listZona) {
			FasesArboles faseActual = zona->getFase();

			if (zona->getCantidadSemilla() <= faseActual) {
				Button^ but = listBotones[i * 3];
				but->Image = imgBotonSemillaRojo;
			}
			else {
				Button^ but = listBotones[i * 3];
				but->Image = imgBotonSemilla;
			}

			///////////

			if (zona->getCantidadAgua() <= faseActual) {
				Button^ but = listBotones[(i * 3) + 1];
				but->Image = imgBotonAguaRojo;
			}
			else {
				Button^ but = listBotones[(i * 3) + 1];
				but->Image = imgBotonAgua;
			}

			/////////

			if (zona->getCantidadResiduo() <= faseActual) {
				Button^ but = listBotones[(i * 3) + 2];
				but->Image = imgBotonResiduoRojo;
			}
			else {
				Button^ but = listBotones[(i * 3) + 2];
				but->Image = imgBotonResiduo;
			}


			i++;
		}
	}

	

};