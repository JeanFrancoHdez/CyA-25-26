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
// Contiene la declaración de la clase "Variable"
// Historial de revisiones
// 03/10/2025 - Creación (primera versión) del código

#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>


class Variable {
  public:
    Variable(int, const std::string&, const std::string&, const std::string& value = "", bool initialized = false);
    int getLine() const { return line_; }
    std::string getType() const { return type_; }
    std::string getName() const { return name_; }
    std::string getValue() const { return value_; }
    bool isInitialized() const { return initialized_; }
    
    friend std::ostream& operator<<(std::ostream& out, const Variable&);
    
  private:
    int line_;
    std::string type_;
    std::string name_;
    std::string value_;
    bool initialized_;
};


#endif