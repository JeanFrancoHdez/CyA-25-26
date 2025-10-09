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
// Contiene la declaración de la clase "Comment"
// Historial de revisiones
// 05/10/2025 - Creación (primera versión) del código

#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include <string>


class Comment {
  public:
    Comment(int start_line, int end_line, const std::string& type, const std::string& content);
    int getStartLine() const { return starting_line_; }
    int getEndLine() const { return ending_line_; }
    std::string getType() const { return type_; }
    std::string getContent() const { return content_; }
    bool isDescription() const { return starting_line_ == 1; }
    
    friend std::ostream& operator<<(std::ostream& out, const Comment&);
    
  private:
    int starting_line_;
    int ending_line_;
    std::string type_;
    std::string content_;
};


#endif