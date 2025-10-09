// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 05/10/2025
// Archivo "Comillas.h"
// Contiene la declaración de la clase "Comillas"
// Historial de revisiones
// 05/10/2025 - Creación (primera versión) del código

#ifndef COMILLAS_H
#define COMILLAS_H

#include <iostream>
#include <string>


class Comillas {
  public:
    Comillas(const int line);
    friend std::ostream& operator<<(std::ostream& out, const Comillas&);
    
  private:
    int line_;
};


#endif