// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo main_p06.cc: programa cliente.
// Historial de revisiones
// 19/10/2025 - Creación (primera versión) del código

#include "FiniteAutomaton.h"

void showHelp(void) {
  std::cout << "\nDescripción: Programa que lee desde un fichero las especificaciones de un autómata finito (FA) y"
            << ", a continuación, simula el comportamiento del autómata para una serie de cadenas\n"
            << "Modo de empleo: ./p06_automata_simulator input.fa input.txt\n"
            << std::endl;
}

void Usage(void) {
  std::cerr << "\nP06: Error, número de argumentos incorrecto.\n" << "Modo de empleo: ./p06_automata_simulator input.fa input.txt\n"
              << "\nSiendo 'input.fa' un fichero de texto en el que figura la especificación de un autómata finito\n"
              << "Siendo 'input.txt' un fichero de texto en el que figura una serie de cadenas sobre el alfabeto del autómata especificado en el primero de los ficheros\n"
              << "\nPruebe './p06_automata_simulator --help' para más información\n"
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

  std::string fa_file = argv[1];
  std::string strings_filename = argv[2];

  FiniteAutomaton fa(fa_file);
  fa.SimulatePerformance(strings_filename);

  return 0;
}