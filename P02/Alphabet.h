// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "Alphabet.h"
// Contiene la declaración de la clase "Alphabet"
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#ifndef ALPHABET_H
#define ALPHABET_H

#include "Symbol.h"
#include "String.h"

class String;

class Alphabet {
  public:
    Alphabet(const std::string&);
    Alphabet(const String&);
    const std::set<Symbol>& getSymbols(void) const;

  private: 
    std::set<Symbol> alphabet_; 
    unsigned int size_;
};

std::ostream& operator<<(std::ostream& out, const Alphabet& alphabet);

#endif