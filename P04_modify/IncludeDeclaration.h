// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 09/10/2025
// Archivo "IncludeDeclaration.h"
// Contiene la declaración de la clase "IncludeDeclaration"

#ifndef INCLUDEDECLARATION_H
#define INCLUDEDECLARATION_H

#include <iostream>
#include <string>

class IncludeDeclaration {
  public:
    IncludeDeclaration(int line, const std::string& filename, const std::string& type);
    
    // Getters
    int getLine() const { return line_; }
    std::string getFilename() const { return filename_; }
    std::string getType() const { return type_; }
    
    // Operator overload
    friend std::ostream& operator<<(std::ostream& out, const IncludeDeclaration& include);
    bool operator<(const IncludeDeclaration& other) const;
    
  private:
    int line_;
    std::string filename_;
    std::string type_; // "<>" or "\"\""
};

#endif