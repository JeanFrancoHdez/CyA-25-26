// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 05/10/2025
// Archivo "Comment.h"
// Contiene el cuerpo de los métodos declarados en "Comment.h"
// Historial de revisiones
// 05/10/2025 - Creación (primera versión) del código

#include "Comment.h"

/**
 * @brief Constructor con parámetros para la clase 'Comment'
 */
Comment::Comment(int start_line, int end_line, const std::string& type, const std::string& content) {
  starting_line_ = start_line;
  ending_line_ = end_line;
  type_ = type;
  content_ = content;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
*/
std::ostream& operator<<(std::ostream& out, const Comment& comment) {
  if (comment.starting_line_ != comment.ending_line_) {
    out << "[Line " << comment.starting_line_ << " - " << comment.ending_line_ << "] ";
  } else {
    out << "[Line " << comment.starting_line_ << "] ";
  }
  return out;
}