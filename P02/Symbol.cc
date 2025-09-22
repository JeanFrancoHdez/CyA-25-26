// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "Symbol.cc"
// Contiene el cuerpo de los métodos declarados en "Symbol.h"
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#include "Symbol.h"

/**
 * @brief Constructor por defecto
*/
Symbol::Symbol() : symbol_{' '} {}

/**
 * @brief Constructor por parámetros
*/
Symbol::Symbol(char symbol) {
  symbol_ = symbol;
}

/**
 * @brief imprimir un simbolo
*/
void Symbol::printSymbol(std::ostream& out) const {
  out << symbol_;
}

/**
 * @brief Sobrecarga del operador de comparación
 */
bool Symbol::operator<(const Symbol& other) const {
  return symbol_ < other.symbol_;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
*/
std::ostream& operator<<(std::ostream& out, const Symbol& symbol) {
  symbol.printSymbol(out);
  return out;
}