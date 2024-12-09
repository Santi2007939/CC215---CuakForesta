#include "Biblioteca.h"
class Area {
private:
    float x, y;
    int ancho, alto;
public:
    Area(float _x, float _y, int _ancho, int _alto) {
        x = _x;
        y = _y;
        ancho = _ancho;
        alto = _alto;
    }
    int GetX()const {
        return x;
    }
    int GetY()const {
        return y;
    }
    int GetAncho()const {
        return ancho;
    }
    int GetAlto()const {
        return alto;
    }
    int GetCentroX()const {
        return x + ancho / 2;
    }
    int GetCentroY()const {
        return y + alto / 2;
    }
    void SetX(int x) {
        this->x = x;
    }
    void SetY(int y) {
        this->y = y;
    }
    void SetAncho(int ancho) {
        this->ancho = ancho;
    }
    void SetAlto(int alto) {
        this->alto = alto;
    }
    float DistanciaCon(Area* otraEntidad) const {
        float x1 = x, y1 = y;
        float x2 = x + ancho, y2 = y + alto;
        float ox1 = otraEntidad->GetX(), oy1 = otraEntidad->GetY();
        float ox2 = otraEntidad->GetX() + otraEntidad->GetAncho(), oy2 = otraEntidad->GetY() + otraEntidad->GetAlto();
        float dx = max(0.0f, max(ox1 - x2, x1 - ox2)); 
        float dy = max(0.0f, max(oy1 - y2, y1 - oy2));
        if (dx == 0.0f && dy == 0.0f) {
            return 0.0f;
        }
        return sqrt(dx * dx + dy * dy);
    }

    int IndiceAreaMasCercana(vector<Area*> vectorEntidad) const {
        float minDistancia = std::numeric_limits<float>::max();
        int indiceMasCercano = -1;
        for (int i = 0; i < vectorEntidad.size(); i++) {
            float distancia = DistanciaCon(vectorEntidad[i]);
            if (distancia < minDistancia) {
                minDistancia = distancia;
                indiceMasCercano = i;
            }
        }
        return indiceMasCercano;
    }
    Area* AreaMasCercana(vector<Area*> vectorEntidad) const {
        float minDistancia = std::numeric_limits<float>::max();
        int indiceMasCercano = -1;
        for (int i = 0; i < vectorEntidad.size(); i++) {
            float distancia = DistanciaCon(vectorEntidad[i]);
            if (distancia < minDistancia) {
                minDistancia = distancia;
                indiceMasCercano = i;
            }
        }
        return vectorEntidad[indiceMasCercano];
    }
    bool InterseccionaCon(Area* other) const {
        if (other == nullptr) return false;
        return !(x + ancho < other->x ||
            other->x + other->ancho < x ||
            y + alto < other->y ||
            other->y + other->alto < y);
    }
    bool Contiene(int px, int py) const {
        return px >= x && px <= x + ancho &&
            py >= y && py <= y + alto;
    }
    bool Contiene(Area* other) const {
        if (other == nullptr) return false;
        return other->x >= x &&
            other->y >= y &&
            other->x + other->ancho <= x + ancho &&
            other->y + other->alto <= y + alto;
    }
    void Expandir(int dAncho, int dAlto) {
        x -= dAncho;
        y -= dAlto;
        ancho += 2 * dAncho;
        alto += 2 * dAlto;
    }
    void SetArea(int _x, int _y, int _ancho, int _alto) {
        this->x = _x;
        this->y = _y;
        this->ancho = _ancho;
        this->alto = _alto;
    }
};