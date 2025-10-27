// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 01/11/2025
// Archivo "Grammar.cc"
// Contiene el cuerpo de los métodos declarados en "FiniteAutomaton.h"
// Historial de revisiones
// 01/11/2025 - Creación (primera versión) del código

#include "Grammar.h"

/**
 * @brief Constructor por parámetros
*/
Grammar::Grammar(const std::string& file_name) {
  CheckFormatErrors(file_name);
  std::ifstream input_file(file_name);

  if (!input_file.is_open()) {
    std::cerr << "ERROR: Error al abrir los archivos" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  
  std::getline(input_file, line);
  number_of_terminal_symbols_ = std::stoi(line);
  
  for (unsigned int i{0}; i < number_of_terminal_symbols_; ++i) {
    std::getline(input_file, line);
    terminal_symbols_.Insert(line[0]);
  }

  std::getline(input_file, line);
  number_of_non_terminal_symbols_ = std::stoi(line);
  
  for (unsigned int i{0}; i < number_of_non_terminal_symbols_; ++i) {
    std::getline(input_file, line);
    non_terminal_symbols_.insert(Symbol(line[0]));
    if (i == 0) {
      start_symbol_ = Symbol(line[0]); // El primer símbolo no terminal es el símbolo de arranque
    }
  }

  std::getline(input_file, line);
  number_of_productions_ = std::stoi(line);
  
  for (unsigned int i{0}; i < number_of_productions_; ++i) {
    std::getline(input_file, line);
    std::istringstream production_stream(line);
    char left_side;
    std::string right_side;
    production_stream >> left_side >> right_side;
    productions_.insert({Symbol(left_side), String(right_side)});
  }

  DetectEmptyProductions();
  DetectUnitaryProductions();

  input_file.close();
}

/**
 * @brief Método que verifica los posibles errores de formato del fichero que define el autómata
 * @param file_name Nombre del archivo de entrada
 */
void Grammar::CheckFormatErrors(const std::string& file_name) {
  std::ifstream input_file(file_name);
  if (!input_file.is_open()) {
    std::cerr << "ERROR: Error al abrir los archivos" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  
  // Verificar el número de símbolos terminales
  if (!std::getline(input_file, line) || line.empty()) {
    std::cerr << "ERROR: Formato inválido en el número de símbolos terminales" << std::endl;
    exit(EXIT_FAILURE);
  }
  unsigned int num_terminal_symbols;
  try {
    num_terminal_symbols = std::stoi(line);
  } catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: Número de símbolos terminales inválido" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::set<Symbol> terminal_symbols;
  
  // Verificar los símbolos terminales
  for (unsigned int i{0}; i < num_terminal_symbols; ++i) {
    if (!std::getline(input_file, line) || line.empty()) {
      std::cerr << "ERROR: Formato inválido en los símbolos terminales" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (line.length() != 1 || isupper(line[0]) || line[0] == '&') {
      std::cerr << "ERROR: Símbolo terminal inválido" << std::endl;
      exit(EXIT_FAILURE);
    }
    terminal_symbols.insert(Symbol(line[0]));
  }

  // Verificar el número de símbolos no terminales
  if (!std::getline(input_file, line) || line.empty()) {
    std::cerr << "ERROR: Formato inválido en el número de símbolos no terminales" << std::endl;
    exit(EXIT_FAILURE);
  }
  unsigned int num_non_terminal_symbols;
  try {
    num_non_terminal_symbols = std::stoi(line);
  } catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: El número de símbolos terminales definidos no coincide con el indicado" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::set<Symbol> non_terminal_symbols;
  Symbol start_symbol;
  
  // Verificar los símbolos no terminales
  for (unsigned int i{0}; i < num_non_terminal_symbols; ++i) {
    if (!std::getline(input_file, line) || line.empty()) {
      std::cerr << "ERROR: Formato inválido en los símbolos no terminales" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (line.length() != 1 || !isupper(line[0])) {
      std::cerr << "ERROR: Símbolo no terminal inválido" << std::endl;
      exit(EXIT_FAILURE);
    }
    Symbol non_terminal(line[0]);
    non_terminal_symbols.insert(non_terminal);
    if (i == 0) {
      start_symbol = non_terminal; // El primer símbolo no terminal es el símbolo de arranque
    }
  }

  // Verificar el número de producciones
  if (!std::getline(input_file, line) || line.empty()) {
    std::cerr << "ERROR: Formato inválido en el número de producciones" << std::endl;
    exit(EXIT_FAILURE);
  }
  unsigned int num_productions;
  try {
    num_productions = std::stoi(line);
  } catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: El número de símbolos no terminales definidos no coincide con el indicado" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::multimap<Symbol, String> productions;
  
  // Verificar las producciones
  unsigned int production_count = 0;
  while (std::getline(input_file, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream production_stream(line);
    char left_side;
    std::string right_side;
    production_stream >> left_side >> right_side;
    if (!isupper(left_side) || right_side.empty()) {
      std::cerr << "ERROR: Producción inválida" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (right_side == "&" && left_side != start_symbol.getSymbol()) {
      std::cerr << "ERROR: Producción inválida con símbolo '&'" << std::endl;
      exit(EXIT_FAILURE);
    }
    for (char production : right_side) {
      if (production == '&' && right_side != "&") {
        std::cerr << "ERROR: Símbolo '&' no permitido en la producción" << std::endl;
        exit(EXIT_FAILURE);
      }
      if (production == '&' && left_side == start_symbol.getSymbol() && right_side == "&") {
        continue; // Permitir la producción S -> &
      }
      if (terminal_symbols.find(Symbol(production)) == terminal_symbols.end() && non_terminal_symbols.find(Symbol(production)) == non_terminal_symbols.end()) {
        std::cerr << "ERROR: Símbolo en la producción no definido (" << production << ")" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    productions.insert({Symbol(left_side), String(right_side)});
    production_count++;
  }

  if (production_count != num_productions) {
    std::cerr << "ERROR: El número de producciones definidas no coincide con el indicado" << std::endl;
    exit(EXIT_FAILURE);
  }

  input_file.close();
}

/**
 * @brief Método para detectar producciones vacías
 */
void Grammar::DetectEmptyProductions() {
  bool first_production = true;
  for (const auto& production : productions_) {
    const Symbol& left_side = production.first;
    const String& right_side = production.second;
    if (right_side.getLength() == 0 || (right_side.getLength() == 1 && right_side.getElement(0).getSymbol() == '&')) {
      if (first_production && left_side == start_symbol_) {
        first_production = false;
      } else {
        std::cerr << "ERROR: Producción vacía detectada en " << left_side.getSymbol() << " -> " << right_side << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
}

/**
 * @brief Método para detectar producciones unitarias
 */
void Grammar::DetectUnitaryProductions() {
  for (const auto& production : productions_) {
    const Symbol& left_side = production.first;
    const String& right_side = production.second;
    if (right_side.getLength() == 1 && non_terminal_symbols_.find(right_side.getElement(0)) != non_terminal_symbols_.end()) {
      std::cerr << "ERROR: Producción unitaria detectada en " << left_side.getSymbol() << " -> " << right_side << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

/**
 * @brief Método para convertir la gramática a Forma Normal de Chomsky (CNF)
 * @param output_file Nombre del archivo donde se escribirá la gramática en CNF
 */
void Grammar::ConvertToCNF(const std::string& output_file) {
  ReplaceTerminalsInProductions();
  DecomposeProductions();
  WriteCNFToFile(output_file);
}

/**
 * @brief Método para reemplazar los símbolos terminales en las producciones
 */
void Grammar::ReplaceTerminalsInProductions() {
  std::map<char, Symbol> terminal_to_non_terminal;
  char counter = 'A';
  
  // Encontrar una letra disponible para los nuevos no terminales
  while (non_terminal_symbols_.find(Symbol(counter)) != non_terminal_symbols_.end()) {
    counter++;
    if (counter > 'Z') {
      std::cerr << "ERROR: No hay suficientes símbolos no terminales disponibles" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  
  std::multimap<Symbol, String> new_productions;
  
  for (const auto& production : productions_) {
    const Symbol& left_side = production.first;
    String right_side = production.second;
    
    if (right_side.getLength() > 1) {
      std::vector<Symbol> new_right_side;
      
      // Reemplazar terminales por no terminales
      for (unsigned int i{0}; i < right_side.getLength(); ++i) {
        Symbol current_symbol = right_side.getElement(i);
        char symbol_char = current_symbol.getSymbol();
        
        // Si es un terminal, reemplazarlo
        if (terminal_symbols_.Belongs(current_symbol)) {
          // Si aún no hemos creado un no terminal para este terminal
          if (terminal_to_non_terminal.find(symbol_char) == terminal_to_non_terminal.end()) {
            Symbol new_non_terminal(counter);
            terminal_to_non_terminal[symbol_char] = new_non_terminal;
            non_terminal_symbols_.insert(new_non_terminal);
            
            new_productions.insert({new_non_terminal, String(std::string(1, symbol_char))});
            counter++;

            while (counter <= 'Z' && non_terminal_symbols_.find(Symbol(counter)) != non_terminal_symbols_.end()) {
              counter++;
            }
          }
          
          new_right_side.push_back(terminal_to_non_terminal[symbol_char]);
        } else {
          new_right_side.push_back(current_symbol);
        }
      }
      
      new_productions.insert({left_side, String(new_right_side)});
    } else {
      new_productions.insert(production);
    }
  }
  
  productions_ = new_productions;
}

/**
 * @brief Método para descomponer las producciones con más de dos símbolos no terminales
 */
void Grammar::DecomposeProductions() {
  std::multimap<Symbol, String> new_productions;
  char counter = 'A';
  
  // Encontrar una letra disponible para los nuevos no terminales
  while (non_terminal_symbols_.find(Symbol(counter)) != non_terminal_symbols_.end()) {
    counter++;
    if (counter > 'Z') {
      std::cerr << "ERROR: No hay suficientes símbolos no terminales disponibles" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  
  for (const auto& production : productions_) {
    const Symbol& left_side = production.first;
    const String& right_side = production.second;
    
    if (right_side.getLength() > 2) {
      Symbol current_left = left_side;
      
      // Descomponer la producción de izquierda a derecha
      for (unsigned int i{0}; i < right_side.getLength() - 2; ++i) {
        Symbol new_non_terminal(counter);
        non_terminal_symbols_.insert(new_non_terminal);
        
        std::vector<Symbol> new_right_vec;
        new_right_vec.push_back(right_side.getElement(i));
        new_right_vec.push_back(new_non_terminal);
        String new_right(new_right_vec);
        new_productions.insert({current_left, new_right});
        
        current_left = new_non_terminal;
        counter++;
        
        while (counter <= 'Z' && non_terminal_symbols_.find(Symbol(counter)) != non_terminal_symbols_.end()) {
          counter++;
        }
      }
      
      std::vector<Symbol> last_vec;
      last_vec.push_back(right_side.getElement(right_side.getLength() - 2));
      last_vec.push_back(right_side.getElement(right_side.getLength() - 1));
      String last_production(last_vec);
      new_productions.insert({current_left, last_production});
    } else {
      new_productions.insert(production);
    }
  }
  
  productions_ = new_productions;
}

/**
 * @brief Método para escribir la gramática en CNF en un archivo
 * @param output_file Nombre del archivo donde se escribirá la gramática en CNF
 */
void Grammar::WriteCNFToFile(const std::string& output_file) {
  std::ofstream output(output_file);
  if (!output.is_open()) {
    std::cerr << "ERROR: Error al abrir el archivo de salida" << std::endl;
    exit(EXIT_FAILURE);
  }

  output << terminal_symbols_.getSymbols().size() << std::endl;
  for (const auto& terminal : terminal_symbols_.getSymbols()) {
    output << terminal.getSymbol() << std::endl;
  }

  output << non_terminal_symbols_.size() << std::endl;
  for (const auto& non_terminal : non_terminal_symbols_) {
    output << non_terminal.getSymbol() << std::endl;
  }

  output << productions_.size() << std::endl;
  for (const auto& production : productions_) {
    output << production.first.getSymbol() << " ";
    for (unsigned int i{0}; i < production.second.getLength(); ++i) {
      output << production.second.getElement(i).getSymbol();
    }
    output << std::endl;
  }

  output.close();
}