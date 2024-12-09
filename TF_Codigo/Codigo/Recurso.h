#pragma once
#include "EntidadAvanzada.h"
class Recurso : public EntidadAvanzada {
private:
	TipoRecurso tipo;
	bool recogido;
	string rutaSprite;
public:
	Recurso(int _x, int _y, TipoRecurso _tipo)
	: EntidadAvanzada(_x,_y,18,19){
		tipo = _tipo;
		recogido = false;
		switch (tipo) {
		case Semilla:
			rutaSprite = "..\\SpriteFinalizados\\Png\\RecursoSueltoSemilla.png";
			break;

		case Agua:
			rutaSprite = "..\\SpriteFinalizados\\Png\\RecursoSueltoAgua.png";
			break;

		case Residuo:
			rutaSprite = "..\\SpriteFinalizados\\Png\\RecursoSueltoResiduo.png";
			break;

		default:
			break;
		}

	}

	void Mostrar(BufferedGraphics^ buffer, Graphics^ g) {
		buffer->Graphics->DrawImage(Img(), int(area->GetX()), int(area->GetY()), area->GetAncho(), area->GetAlto());
	}

	const TipoRecurso getTipo() {
		return tipo;
	}

	Bitmap^ Img() {
		String^ rutaManaged = gcnew String(rutaSprite.c_str());
		Bitmap^ bitmap = gcnew Bitmap(rutaManaged);
		return bitmap;
	}

	void SetRecogidos(bool value) {
		recogido = value;
	}

	bool GetRecogido() {
		return recogido;
	}
};
