// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 03/10/2025
// Archivo "main_p04_code_analyzer.cc": Programa cliente
// 03/10/2025 - Creación (primera versión) del código

#include "CodeAnalyzer.h"
#include <iostream>

void showHelp() {
  std::cout << "\nDescripción: Programa que analiza el contenido de ficheros de código haciendo uso de expresiones regulares.\n"
            << "Uso de caso general: ./p04_code_analyzer code.cc fileout.txt\n"
            << "\nParámetros:\n"
            << "  code.cc     - Fichero de código C++ sintácticamente correcto\n" 
            << "  fileout.txt - Fichero de salida con el resumen de la estructura\n"
            << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
    showHelp();
    return 0;
  }

  if (argc != 3) {
    std::cerr << "Error: Número de argumentos incorrecto.\n";
    std::cerr << "Uso: ./p04_code_analyzer <archivo_entrada.cc> <archivo_salida.txt>\n";
    std::cerr << "Use -h o --help para más información.\n";
    return EXIT_FAILURE;
  }

  std::string input_file = argv[1];
  std::string output_file = argv[2];

  try {
    CodeAnalyzer analyzer(input_file);
    analyzer.analyzeCode();
    analyzer.generateReport(output_file);
    
    std::cout << "Análisis completado exitosamente.\n";
    std::cout << "Resultado guardado en: " << output_file << "\n";
    
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return 0;
}