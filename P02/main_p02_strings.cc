// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2024
// Archivo cya-P02-strings.cc: programa cliente.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 19/09/2024 - Creación (primera versión) del código

#include "Symbol.h"
#include "String.h"
#include "Alphabet.h"
#include <fstream>
#include "Language.h"

void showHelp(void) {
  std::cout << "\nDescripción: Programa que dado un fichero de entrada con la especificación de cadenas, realiza un conjunto de comprobaciones básicas sobre ellas.\n"
            << "Uso de caso general: ./p02_strings filein.txt fileout.txt opcode\n"
            << std::endl;
}

int main (int argc, char *argv[]) {
  // Declaración de variables
  std::string input_filename = argv[1];

  if (input_filename == "-h" || input_filename == "--help") {
    showHelp();
    return 0;
  }

  std::ifstream file_in(input_filename);
  std::string output_filename = argv[2];
  std::ofstream file_out(output_filename);
  std::string string_opcode = argv[3];
  int opcode = std::stoi(string_opcode);

  // Verificación de apertura de archivos
  if (!file_in.is_open() || !file_out.is_open()) {
    std::cerr << "P02: Error al abrir los archivos" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string cadena;
  std::string alphabet;
  //int line_number = 1;
  // Lectura desde el archivo 
  while (file_in >> cadena >> alphabet ) {
    String string(cadena);
    Alphabet alphabet_of_string(alphabet);
    switch (opcode) {
      case 1: { // Alfabeto asociado
        file_out << " " << string.getAlphabet() << std::endl;
        break;
      }
      case 2: { // Longitud
        file_out << " " << string.getLength() << std::endl;
        break;
      }
      case 3: { // Inversa
        file_out << " " << string.getInverse(string) << std::endl;
        break;
      }
      case 4: { // Prefijos
        std::vector<String> prefixes = string.getPrefixes();
        Language language;
        for (const auto& s : prefixes) language.AddString(s);
        file_out << " " << language << std::endl;
        break;
      }
      case 5: { // Sufijos
        std::vector<String> suffixes = string.getSuffixes();
        Language language;
        for (const auto& s : suffixes) language.AddString(s);
        file_out << " " << language << std::endl;
        break;
      }
      default:
        std::cout << "Opción incorrecta o no disponible\n";
        return 0;
    }
    //++line_number;
  }
  return 0;
}