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
// Contiene la declaración de la clase "Statements"
// Historial de revisiones
// 04/10/2025 - Creación (primera versión) del código

#ifndef STATEMENT_H
#define STATEMENT_H

#include <iostream>
#include <string>


class Statement {
  public:
    Statement(int line, const std::string& type, const std::string& category);
    int getLine() const { return line_; }
    std::string getType() const { return type_; }
    std::string getCategory() const { return category_; }
    
    friend std::ostream& operator<<(std::ostream& out, const Statement&);
    
  private:
    int line_;
    std::string type_;
    std::string category_;
};


#endif