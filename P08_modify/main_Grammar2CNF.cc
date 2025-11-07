// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 02/11/2025
// Archivo main_Grammar2CNF.cc: programa cliente.
// Historial de revisiones
// 02/11/2025 - Creación (primera versión) del código

#include "Grammar.h"

void showHelp(void) {
  std::cout << "\nDescripción: Programa que procesa gramáticas independientes del contexto\n"
            << "Modo de empleo: ./Grammar2CNF input.gra output.gra [modo]\n"
            << "\nModos disponibles:\n"
            << "  cnf       - Convierte la gramática a Forma Normal de Chomsky (FNC) [por defecto]\n"
            << "  simplify  - Simplifica la gramática eliminando no terminales que solo producen terminales\n"
            << std::endl;
}

void Usage(void) {
  std::cerr << "\nUso incorrecto: Error, número de argumentos incorrecto.\n" 
            << "Modo de empleo: ./Grammar2CNF input.gra output.gra [modo]\n"
            << "\nSiendo 'input.gra' un fichero de texto en el que figura la especificación de una gramática\n"
            << "Siendo 'output.gra' un fichero de texto en el que figura la especificación procesada\n"
            << "Siendo 'modo' opcional: 'cnf' (por defecto) o 'simplify'\n"
            << "\nPruebe './Grammar2CNF --help' para más información\n"
            << std::endl;
}

int main (int argc, char *argv[]) {
  if (argc == 2 && (std::string(argv[1]) == "--help")) {
    showHelp();
    return 0;
  }

  if (argc < 3 || argc > 4) {
    Usage();
    exit(EXIT_FAILURE);
  }

  std::string gra_file_in = argv[1];
  std::string gra_file_out = argv[2];
  std::string mode = (argc == 4) ? argv[3] : "cnf";

  Grammar FC_grammar(gra_file_in);
  
  if (mode == "simplify") {
    FC_grammar.SimplifyGrammar(gra_file_out);
  } else if (mode == "cnf") {
    FC_grammar.ConvertToCNF(gra_file_out);
  } else {
    std::cerr << "ERROR: Modo desconocido '" << mode << "'. Use 'cnf' o 'simplify'." << std::endl;
    Usage();
    exit(EXIT_FAILURE);
  }

  return 0;
}