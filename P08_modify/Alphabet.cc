// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "Alphabet.cc"
// Contiene el cuerpo de los métodos declarados en "Alphabet.h"
// Referencias:
// Enlaces de interés
//
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#include "Alphabet.h"
#include "String.h"

/**
 * @brief Constructor por parámetros
*/
Alphabet::Alphabet(const std::string& string_for_create) {
  for (unsigned int i{0}; i < string_for_create.length(); i++) {
    alphabet_.insert(string_for_create[i]);
  }
  size_ = alphabet_.size();
}

/**
 * @brief Constructor por parámetros
*/
Alphabet::Alphabet(const String& string_for_create) {
  for (unsigned int i{0}; i < string_for_create.getLength(); i++) {
    alphabet_.insert(string_for_create.getElement(i));
  }
  size_ = alphabet_.size();
}

/**
 * @brief Constructor por parámetros
*/
Alphabet::Alphabet(const std::set<Symbol>& symbols) : alphabet_(symbols) {}

/**
 * @brief Método getter para obtener los símbolos que conforman un alfabeto
 * @return Una estructura 'set' que contiene los símbolos del alfabeto
*/
const std::set<Symbol>& Alphabet::getSymbols(void) const {
  return alphabet_;
}

/**
 * @brief Método que verifica si un simbolo pertenece al alfabeto
 * @param (Symbol) objeto de la clase Simbolo
 * @return Booleano que indica si el simbolo pertenece al alfabeto
 */
bool Alphabet::Belongs(const Symbol& symbol) const {
  return alphabet_.find(symbol) != alphabet_.end();
}

/**
 * @brief Método para insertar un símbolo en el alfabeto
 * @param symbol El símbolo a insertar
 */
void Alphabet::Insert(const Symbol& symbol) {
  auto result = alphabet_.insert(symbol);
  if (result.second) { // Si el símbolo fue insertado (no estaba previamente)
    ++size_;
  }
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
*/
std::ostream& operator<<(std::ostream& out, Alphabet& alphabet) {
  bool begin = true;
  out << "{";
  for (const Symbol& element : alphabet.getSymbols()) {
    if (!begin) {
      out << ", ";
    }
    element.printSymbol(out);
    begin = false;
  }
  out << "}";
  return out;
}