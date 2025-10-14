// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// 
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "FiniteAutomaton.h"
// Contiene la declaración de la clase "FiniteAutomaton"
// Historial de revisiones
// 19/10/2025 - Creación (primera versión) del código

#ifndef FINITEAUTOMATON_H
#define FINITEAUTOMATON_H

typedef int State;

#include "Symbol.h"
#include "String.h"
#include "Alphabet.h"
#include <utility>
#include <sstream>
#include <regex>

class FiniteAutomaton {
  public:
    FiniteAutomaton(const std::string&);
    
    // Métodos de E/S
    void loadFromFile(const std::string&);
    void print(std::ostream& os = std::cout) const;
    friend std::ostream& operator<<(std::ostream& os, const FiniteAutomaton& fa);
    
    // Métodos de simulación
    bool simulate(const std::string& input_string);
    void SimulatePerformance(const std::string&);
    
    // Métodos de acceso a transiciones
    std::set<State> getNextStates(State current_state, const Symbol& symbol) const;

  private: 
    void CheckFormatErrors(const std::string&);
    std::set<State> computeEpsilonClosure(const std::set<State>& states) const;

    Alphabet alphabet_associated_;
    int number_of_states_;
    State initial_state_;
    std::map<State, bool> kind_of_states_;
    std::map<State, std::map<Symbol, std::set<State>>> transitions_;
};


#endif