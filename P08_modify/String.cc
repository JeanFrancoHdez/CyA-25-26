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
 * @brief Constructor que convierte una std::string en una String
*/
String::String(const std::string& string_to_convert) {
  for (unsigned int i{0}; i < string_to_convert.length(); i++) {
    Symbol symbol(string_to_convert[i]);
    string_.push_back(symbol);
    alphabet_.Insert(symbol);
  }
  length_ = string_to_convert.length();
}

/**
 * @brief Constructor que convierte un vector de Symbol en una String
*/
String::String(const std::vector<Symbol>& symbols) {
  for (const auto& symbol : symbols) {
    string_.push_back(symbol);
    alphabet_.Insert(symbol);
  }
  length_ = symbols.size();
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
 * @brief Método para reemplazar un símbolo en una posición específica de la cadena
 * @param position La posición del símbolo a reemplazar
 * @param new_symbol El nuevo símbolo que reemplazará al antiguo
 */
void String::replace(unsigned int position, const Symbol& new_symbol) {
  if (position < length_) {
    string_[position] = new_symbol;
  } else {
    std::cerr << "Error: posición fuera de rango" << std::endl;
  }
}

/**
 * @brief Sobrecarga del operador de asignación
 * @param other Otra cadena de la clase String
 * @return Referencia a la cadena actual
 */
String& String::operator=(const String& other) {
  if (this != &other) {
    string_ = other.string_;
    alphabet_ = other.alphabet_;
    length_ = other.length_;
  }
  return *this;
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