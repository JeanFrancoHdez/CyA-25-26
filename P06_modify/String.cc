// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "String.cc"
// Contiene el cuerpo de los métodos declarados en "String.h"
// Referencias:
// Enlaces de interés
//
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#include "String.h"
#include "Alphabet.h"

/**
 * @brief Constructor por defecto
*/
String::String() : alphabet_(EMPTY_STRING) {
  char epsilon = '&';
  string_.push_back(epsilon);
  length_ = 0;
}

/**
 * @brief Constructor por parámetros
*/
String::String(const std::string& string_to_convert, const Alphabet& alphabet_of_string) : alphabet_(alphabet_of_string) {
  if (string_to_convert == EMPTY_STRING) {
    string_.push_back(Symbol(EPSILON));
    length_ = 0;
  } else {
    for (unsigned int i{0}; i < string_to_convert.length(); i++) {
      if (alphabet_of_string.Belongs(string_to_convert[i])) { // Comprobar si pertenece al alfabeto
        string_.push_back(string_to_convert[i]);
      } else {
        std::cerr << "Error en la cadena: " << string_to_convert << std::endl;
        std::cerr << "El símbolo '" << string_to_convert[i] << "' no pertenece al alfabeto" << std::endl;
      }
    }
    length_ = string_to_convert.length();
  }
}

/**
 * @brief obtener la longitud de una cadena
 */
unsigned int String::getLength(void) const {
  return length_;
}

/**
 * @brief obtener el elemento de una cadena dada su posición en la misma
 */
Symbol String::getElement(unsigned int position) const {
  return string_[position];
}


/**
 * @brief Obtener el alfabeto asociado a una cadena
 * @param - Cadena de entrada
 * @return Alfabeto asociado a la cadena de entrada
 */
Alphabet String::getAlphabet(void) const {
  return alphabet_;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
*/
std::ostream& operator<<(std::ostream& out, const String& string) {
  for (unsigned int i{0}; i < string.getLength(); i++) {
    out << string.getElement(i);
    if (i == string.getLength()) {
      out << string.getElement(i) << std::endl;
    }
  }
  return out;
}