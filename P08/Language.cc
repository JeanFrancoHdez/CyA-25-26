// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "Language.cc"
// Contiene el cuerpo de los métodos declarados en "Language.h"
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#include "Language.h"

/**
 * @brief Sobrecarga del operador de inserción en flujo
*/
std::ostream& operator<<(std::ostream& out, const Language& language) {
  out << "{";  
  for (auto it = language.language_.begin(); it != language.language_.end(); it++) {
    if (it != language.language_.begin()) {
      out << ", ";
    }
    out << *it;
  }
  out << "}";
  return out;
}