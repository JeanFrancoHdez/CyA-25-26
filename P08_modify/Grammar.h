// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// 
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 01/11/2025
// Archivo "Grammar.h"
// Contiene la declaración de la clase "Grammar"
// Historial de revisiones
// 01/11/2025 - Creación (primera versión) del código

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Symbol.h"
#include "String.h"
#include "Alphabet.h"
#include <utility>
#include <sstream>
#include <regex>

class Grammar {
  public:
    Grammar(const std::string&);
    void CheckFormatErrors(const std::string&);
    void DetectEmptyProductions(void);
    void DetectUnitaryProductions();
    void ConvertToCNF(const std::string&);
    void SimplifyGrammar(const std::string&);
    void WriteCNFToFile(const std::string&);
    void ReplaceSingleTerminalNonterminals(void);
    void ReplaceTerminalsInProductions(void);
    void DecomposeProductions(void);
    std::set<Symbol> GetAccessibleNonTerminals(void);

  private:
    unsigned int number_of_terminal_symbols_;
    unsigned int number_of_non_terminal_symbols_;
    unsigned int number_of_productions_;
    Alphabet terminal_symbols_;
    std::set<Symbol> non_terminal_symbols_;
    Symbol start_symbol_;
    std::multimap<Symbol, String> productions_;
};


#endif