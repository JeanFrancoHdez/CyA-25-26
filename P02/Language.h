// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2024
// Archivo "Language.h"
// Contiene la declaración de la clase "Language"
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 19/09/2024 - Creación (primera versión) del código

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "Symbol.h"
#include "String.h"


class Language {
  public:
    Language();
    Language(const std::set<String>&);
    void AddString(const String&);
    const std::set<String>& GetStrings() const;
    size_t Size() const;
    friend std::ostream& operator<<(std::ostream& out, const Language& language);
  private:
    std::set<String> language_;
};



#endif