// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo cya-P02-strings.cc: programa cliente.
// Referencias:
// Enlaces de interés
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#include "Symbol.h"
#include "String.h"
#include "Alphabet.h"
#include <fstream>
#include "Language.h"

void showHelp(void) {
  std::cout << "\nDescripción: Programa que dado un fichero de entrada con una especificación de cadenas, realiza un conjunto de operaciones básicas sobre ellas.\n"
            << "Uso de caso general: ./p02_strings filein.txt fileout.txt opcode\n"
            << std::endl;
}

int main (int argc, char *argv[]) {
  std::string input_filename = argv[1];
  if (argc == 2 && (input_filename == "-h" || input_filename == "--help")) {
    showHelp();
    return 0;
  }

  // Comprobar número de argumentos
  if (argc != 4) {
    std::cerr << "Error: Número de argumentos incorrecto.\nUso de caso general: ./p02_strings filein.txt fileout.txt opcode" << std::endl;
    return EXIT_FAILURE;
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
  
  // Lectura desde el archivo 
  while (file_in >> cadena >> alphabet ) {
    String string(cadena);
    Alphabet alphabet_of_string(alphabet);
    // Validar que todos los símbolos de la cadena están en el alfabeto
    bool valid = true;
    const std::set<Symbol>& symbols = alphabet_of_string.getSymbols();
    for (unsigned int i = 0; i < string.getLength(); ++i) {
      if (symbols.find(string.getElement(i)) == symbols.end()) {
        std::cerr << "Error: La cadena '" << cadena << "' contiene símbolos no presentes en el alfabeto '" << alphabet << "'. Línea omitida." << std::endl;
        valid = false;
        break;
      }
    }
    if (!valid) continue;
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
      case 6: {
        std::vector<String> prefixes = string.getPrefixes();
        std::vector<String> suffixes = string.getSuffixes();
        Language language;
        for (auto& p : prefixes) {
          for (auto& s : suffixes) language.AddStrings(s, p);
        }
        file_out << " " << language << std::endl;
        break;
      }
      default:
        std::cout << "Opción incorrecta o no disponible\n";
        return 0;
    }
  }
  return 0;
}