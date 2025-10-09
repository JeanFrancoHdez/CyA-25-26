// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 03/10/2025
// Archivo "Variable.h"
// Contiene el cuerpo de los métodos declarados en "Variable.h"
// Historial de revisiones
// 03/10/2025 - Creación (primera versión) del código

#include "Variable.h"
#include <algorithm>
#include <cctype>

/**
 * @brief Constructor con parámetros para la clase 'Variable'
 */
Variable::Variable(int line, const std::string& type, const std::string& name, const std::string& value, bool initialized) {
  line_ = line;
  type_ = type;
  name_ = name;
  value_ = value;
  initialized_ = initialized;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
*/
std::ostream& operator<<(std::ostream& out, const Variable& variable) {
  // Convertir tipo a mayúsculas
  std::string type_upper = variable.type_;
  std::transform(type_upper.begin(), type_upper.end(), type_upper.begin(), ::toupper);
  
  out << "[Line " << variable.line_ << "] " << type_upper << ": " << variable.name_;
  
  if (variable.initialized_ && !variable.value_.empty()) {
    out << " = " << variable.value_;
  }
  
  out << "\n";
  return out;
}