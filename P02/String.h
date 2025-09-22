// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "String.h"
// Contiene la declaración de la clase "String"
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#ifndef STRING_H
#define STRING_H

#include "Symbol.h"
class Alphabet;

class String {
  public:
    String(void);
    String(const std::string&);
    unsigned int getLength(void) const;
    Symbol getElement(unsigned int) const;
    Alphabet getAlphabet() const;
    String getInverse(String&);
    std::vector<String> getPrefixes() const;
    std::vector<String> getSuffixes() const;
    bool operator<(const String& other) const;

  private:
    std::vector<Symbol> string_;
    unsigned int length_; 
};

std::ostream& operator<<(std::ostream& out, const String&);

#endif