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
  std::cout << "\nDescripción: Programa que lea un fichero en el que figura la especificación de "
            << "una gramática independiente del contexto y genere otro fichero en el que se especifique una gramática equivalente en FNC\n"
            << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n"
            << std::endl;
}

void Usage(void) {
  std::cerr << "\nUso incorrecto: Error, número de argumentos incorrecto.\n" << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n"
              << "\nSiendo 'input.gra' un fichero de texto en el que figura la especificación de una gramática\n"
              << "Siendo 'output.gra' un fichero de texto en el que figura la especificación en FNC respecto a la gramática recibida\n"
              << "\nPruebe './Grammar2CNF --help' para más información\n"
              << std::endl;
}

int main (int argc, char *argv[]) {
  if (argc == 2 && (std::string(argv[1]) == "--help")) {
    showHelp();
    return 0;
  }

  if (argc != 3) {
    Usage();
    exit(EXIT_FAILURE);
  }

  std::string gra_file_in = argv[1];
  std::string gra_file_out = argv[2];

  Grammar FC_grammar(gra_file_in);
  FC_grammar.ConvertToCNF(gra_file_out);

  return 0;
}