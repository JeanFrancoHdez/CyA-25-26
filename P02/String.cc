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

const char EPSILON = '&';

bool String::operator<(const String& other) const {
  // Ordenar por longitud y luego lexicográficamente
  if (length_ != other.length_) return length_ < other.length_;
  for (unsigned int i = 0; i < length_; ++i) {
    if (string_[i].operator char() != other.string_[i].operator char())
      return string_[i].operator char() < other.string_[i].operator char();
  }
  return false;
}

/**
 * @brief Constructor por defecto
*/
String::String() {
  string_.push_back(EPSILON);
  length_ = 0;
}

/**
 * @brief Constructor por parámetros
*/
String::String(const std::string& string_to_convert) {
  for (unsigned int i{0}; i < string_to_convert.length(); i++) {
    string_.push_back(string_to_convert[i]);
  }
  length_ = string_to_convert.length();
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

Alphabet String::getAlphabet() const {
  return Alphabet(*this);
}

std::vector<String> String::getPrefixes() const {
  std::vector<String> prefixes;
  String prefix;
  // Prefijo vacío (epsilon)
  prefixes.push_back(String("&"));
  for (unsigned int i = 0; i < string_.size(); ++i) {
    std::string temp;
    for (unsigned int j = 0; j <= i; ++j) {
      temp += string_[j].operator char();
    }
    prefixes.push_back(String(temp));
  }
  return prefixes;
}

std::vector<String> String::getSuffixes() const {
  std::vector<String> suffixes;
  // Sufijo vacío (epsilon)
  suffixes.push_back(String("&"));
  for (unsigned int i = 0; i < string_.size(); ++i) {
    std::string temp;
    for (unsigned int j = i; j < string_.size(); ++j) {
      temp += string_[j].operator char();
    }
    suffixes.push_back(String(temp));
  }
  return suffixes;
}

/**
 * @brief Obtener la inversa de una cadena
 * @param - Cadena de entrada
 * @return Cadena inversa correspondiente a la cadena de entrada
 */
String String::getInverse(String& string_to_convert) {
  String inverse;
  inverse.string_.resize(string_to_convert.getLength());
  inverse.length_ = string_to_convert.getLength();
  for (unsigned int i{0}; i < string_to_convert.getLength(); i++) {
    inverse.string_[i] = string_to_convert.getElement(string_to_convert.getLength() - i - 1);
  }
  return inverse;
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