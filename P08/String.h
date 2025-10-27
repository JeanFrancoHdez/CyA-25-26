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
#include "Alphabet.h"

class Alphabet;

const char EPSILON = '&';
const std::string EMPTY_STRING = "&";

class String {
  public:
    String(void);
    String(const std::string&, const Alphabet&);
    String(const std::string&);
    String(const std::vector<Symbol>&);
    unsigned int getLength(void) const;
    Symbol getElement(unsigned int) const;
    Alphabet getAlphabet(void) const;
    void replace(unsigned int, const Symbol&);
    String& operator=(const String&);
    
  private: 
    std::vector<Symbol> string_;
    Alphabet alphabet_;
    unsigned int length_; 
};

std::ostream& operator<<(std::ostream& out, const String&);

#endif