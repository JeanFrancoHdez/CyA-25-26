// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 03/10/2025
// Archivo "Statement.h"
// Contiene el cuerpo de los métodos declarados en "Statement.h"
// Historial de revisiones
// 04/10/2025 - Creación (primera versión) del código

#include "Statement.h"

/**
 * @brief Constructor con parámetros para la clase 'Statement'
 */
Statement::Statement(int line, const std::string& type, const std::string& category) {
  line_ = line;
  type_ = type;
  category_ = category;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
*/
std::ostream& operator<<(std::ostream& out, const Statement& statement) {
  out << "[Line " << statement.line_ << "] " << statement.type_ << ": " << statement.category_ << "\n";
  return out;
}