// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 03/10/2025
// Archivo "Comillas.h"
// Contiene el cuerpo de los métodos declarados en "Comillas.h"
// Historial de revisiones
// 03/10/2025 - Creación (primera versión) del código

#include "Comillas.h"

/**
 * @brief Constructor con parámetros para la clase 'Comillas'
 * @param Línea en la que se encuentra
 */
Comillas::Comillas(const int line) {
  line_ = line;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
*/
std::ostream& operator<<(std::ostream& out, const Comillas& comillas) {
  out << "[Line " << comillas.line_ << "] ";
  return out;
}