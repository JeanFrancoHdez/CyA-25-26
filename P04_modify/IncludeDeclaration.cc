// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 09/10/2025
// Archivo "IncludeDeclaration.cc"
// Contiene la implementación de la clase "IncludeDeclaration"

#include "IncludeDeclaration.h"

/**
 * @brief Constructor con parámetros para la clase 'IncludeDeclaration'
 * @param line Línea en la que se encuentra el include
 * @param filename Nombre del archivo incluido
 * @param type Tipo de include: "<>" o "\"\""
 */
IncludeDeclaration::IncludeDeclaration(int line, const std::string& filename, const std::string& type) {
  line_ = line;
  filename_ = filename;
  type_ = type;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
 */
std::ostream& operator<<(std::ostream& out, const IncludeDeclaration& include) {
  out << "[Line " << include.line_ << "] " << include.type_ << ": " << include.filename_;
  return out;
}

/**
 * @brief Sobrecarga del operador < para ordenamiento
 */
bool IncludeDeclaration::operator<(const IncludeDeclaration& other) const {
  return line_ < other.line_;
}