// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "Symbol.h"
// Contiene la declaración de la clase "Symbol"
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cassert>

class Symbol {
  public:
    Symbol();
    Symbol(char);
    void printSymbol(std::ostream&) const;
    bool operator<(const Symbol&) const;
    explicit operator char() const { return symbol_; }

  private:
    char symbol_;
};

std::ostream& operator<<(std::ostream& out, const Symbol&);

#endif