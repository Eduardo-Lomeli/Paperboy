#pragma once
#include<list>
#include<string>
#include<Vector.hpp>

using namespace std;

class Dibujo
{
private:
    list<string> lineas;
    Vector posicion;
    Vector velocidad;
public:
    Dibujo();

    ~Dibujo();

    void AgregarLinea(string linea){
        this->lineas.push_back(linea);
    }
    list<string> ObtenerLineas(){
        return this ->lineas;
    }
};