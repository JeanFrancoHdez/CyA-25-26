// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/10/2025
// Archivo "FiniteAutomaton.cc"
// Contiene el cuerpo de los métodos declarados en "FiniteAutomaton.h"
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#include "FiniteAutomaton.h"

/**
 * @brief Constructor por parámetros
*/
FiniteAutomaton::FiniteAutomaton(const std::string& file_name) {
  CheckFormatErrors(file_name);
  std::ifstream input_file(file_name);

  if (!input_file.is_open()) {
    std::cerr << "P06: Error al abrir los archivos" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // Leer la primera línea: Símbolos del alfabeto
  std::string line;
  std::getline(input_file, line);
  alphabet_associated_ = Alphabet(line);

  // Leer la segunda línea: Número total de estados
  std::getline(input_file, line);
  number_of_states_ = std::stoi(line);

  // Leer la tercera línea: Estado de arranque
  std::getline(input_file, line);
  initial_state_ = std::stoi(line);

  // Leer las líneas restantes: Información de los estados y transiciones
  while (std::getline(input_file, line)) {
    std::istringstream flujo(line);
    State state;
    bool acceptance;
    int num_transitions;
    flujo >> state >> acceptance >> num_transitions;

    // Almacenar el tipo de estado (aceptación o no)
    kind_of_states_[state] = acceptance;

    // Leer y almacenar cada transición
    for (int i{0}; i < num_transitions; ++i) {
      char symbol_of_transition;
      State destination_state;
      flujo >> symbol_of_transition >> destination_state;

      Symbol symbol(symbol_of_transition);
      transitions_[state][symbol].insert(destination_state);
    }
  }
  input_file.close();
}

/**
 * @brief Método que calcula la epsilon-clausura de un conjunto de estados
 * @param states Conjunto de estados inicial
 * @return Conjunto de estados alcanzables mediante epsilon-transiciones
 */
std::set<State> FiniteAutomaton::computeEpsilonClosure(const std::set<State>& states) const {
  std::set<State> epsilon_closure = states;
  bool added_new_state;
  
  do {
    added_new_state = false;
    std::set<State> new_states;
    
    for (State state : epsilon_closure) {
      auto it = transitions_.find(state);
      if (it != transitions_.end()) {
        auto symbol_it = it->second.find(Symbol('&'));
        if (symbol_it != it->second.end()) {
          for (State next_state : symbol_it->second) {
            if (epsilon_closure.find(next_state) == epsilon_closure.end()) {
              new_states.insert(next_state);
              added_new_state = true;
            }
          }
        }
      }
    }
    epsilon_closure.insert(new_states.begin(), new_states.end());
  } while (added_new_state);
  
  return epsilon_closure;
}

/**
 * @brief Método que obtiene el conjunto de estados siguientes dado un estado y un símbolo
 * @param current_state Estado actual
 * @param symbol Símbolo de entrada
 * @return Conjunto de estados alcanzables
 */
std::set<State> FiniteAutomaton::getNextStates(State current_state, const Symbol& symbol) const {
  std::set<State> next_states;
  
  auto state_it = transitions_.find(current_state);
  if (state_it != transitions_.end()) {
    auto symbol_it = state_it->second.find(symbol);
    if (symbol_it != state_it->second.end()) {
      next_states = symbol_it->second;
    }
  }
  
  return next_states;
}

/**
 * @brief Método que carga un autómata desde un archivo
 * @param file_name Nombre del archivo
 */
void FiniteAutomaton::loadFromFile(const std::string& file_name) {
  CheckFormatErrors(file_name);
  std::ifstream input_file(file_name);

  if (!input_file.is_open()) {
    std::cerr << "P06: Error al abrir los archivos" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  std::string line;
  std::getline(input_file, line);
  alphabet_associated_ = Alphabet(line);

  std::getline(input_file, line);
  number_of_states_ = std::stoi(line);

  std::getline(input_file, line);
  initial_state_ = std::stoi(line);

  while (std::getline(input_file, line)) {
    std::istringstream flujo(line);
    State state;
    bool acceptance;
    int num_transitions;
    flujo >> state >> acceptance >> num_transitions;

    kind_of_states_[state] = acceptance;

    for (int i{0}; i < num_transitions; ++i) {
      char symbol_of_transition;
      State destination_state;
      flujo >> symbol_of_transition >> destination_state;

      Symbol symbol(symbol_of_transition);
      transitions_[state][symbol].insert(destination_state);
    }
  }
  input_file.close();
}

/**
 * @brief Método que imprime la información del autómata
 * @param os Flujo de salida
 */
void FiniteAutomaton::print(std::ostream& os) const {
  os << "Alfabeto: {";
  const auto& symbols = alphabet_associated_.getSymbols();
  bool first = true;
  for (const Symbol& sym : symbols) {
    if (!first) os << ", ";
    os << sym;
    first = false;
  }
  os << "}\n";
  
  os << "Número de estados: " << number_of_states_ << "\n";
  os << "Estado inicial: " << initial_state_ << "\n";
  os << "Estados:\n";
  
  for (const auto& [state, is_acceptance] : kind_of_states_) {
    os << "  Estado " << state << (is_acceptance ? " (Aceptación)" : "") << ":\n";
    
    auto it = transitions_.find(state);
    if (it != transitions_.end()) {
      for (const auto& [symbol, dest_states] : it->second) {
        os << "    " << symbol << " -> {";
        bool first_dest = true;
        for (State dest : dest_states) {
          if (!first_dest) os << ", ";
          os << dest;
          first_dest = false;
        }
        os << "}\n";
      }
    }
  }
}

/**
 * @brief Sobrecarga del operador de inserción en flujo
 */
std::ostream& operator<<(std::ostream& os, const FiniteAutomaton& fa) {
  fa.print(os);
  return os;
}

/**
 * @brief Método que simula el autómata para una cadena específica
 * @param input_string Cadena de entrada
 * @return true si la cadena es aceptada, false en caso contrario
 */
bool FiniteAutomaton::simulate(const std::string& input_string) {
  // Estado inicial
  std::set<State> current_states;
  current_states.insert(initial_state_);

  std::cout << "Cadena de entrada: " << (input_string.empty() ? "&" : input_string) << "\n\n";

  // Clausura epsilon inicial
  std::cout << "Cálculo de ε-clausura inicial:\n";
  current_states = computeEpsilonClosure(current_states);
  std::cout << "Estados actuales: { ";
  bool first = true;
  for (auto s : current_states) {
    if (!first) std::cout << ", ";
    std::cout << s;
    first = false;
  }
  std::cout << " }\n\n";

  // Recorrer cada símbolo de la cadena
  for (size_t i = 0; i < input_string.size(); ++i) {
    Symbol symbol(input_string[i]);
    std::cout << "---------------------------------\n";
    std::cout << "Paso " << i + 1 << "\n";
    std::cout << "Símbolo actual: " << symbol << "\n";
    std::cout << "Estados actuales: { ";
    first = true;
    for (auto s : current_states) {
      if (!first) std::cout << ", ";
      std::cout << s;
      first = false;
    }
    std::cout << " }\n";

    // Calcular transiciones con el símbolo actual
    std::set<State> next_states;
    std::cout << "Reglas de produccion δ(q, " << symbol << "):\n";
    for (auto s : current_states) {
      std::set<State> destinations = getNextStates(s, symbol);
      std::cout << "  δ(" << s << ", " << symbol << ") = { ";
      bool first_dest = true;
      for (auto d : destinations) {
        if (!first_dest) std::cout << ", ";
        std::cout << d;
        first_dest = false;
      }
      std::cout << " }\n";
      next_states.insert(destinations.begin(), destinations.end());
    }

    // Aplicar ε-clausura posterior
    std::cout << "ε-transiciones posteriores:\n";
    next_states = computeEpsilonClosure(next_states);
    std::cout << "Estados siguientes: { ";
    first = true;
    for (auto s : next_states) {
      if (!first) std::cout << ", ";
      std::cout << s;
      first = false;
    }
    std::cout << " }\n";
    current_states = next_states;
    std::cout << "\nPulse la tecla ENTER para continuar...\n";
    std::cin.get();
  }

  // Resultado final
  std::cout << "--- RESULTADO FINAL ---\n";
  std::cout << "Estados finales alcanzados: { ";
  first = true;
  for (auto s : current_states) {
    if (!first) std::cout << ", ";
    std::cout << s;
    first = false;
  }
  std::cout << " }\n";

  bool accepted = false;
  for (auto s : current_states) {
    if (kind_of_states_.at(s)) accepted = true;
  }
  std::cout << "RESULTADO: " << (accepted ? "Aceptada" : "Rechazada") << "\n\n";
  
  return accepted;
}

/**
 * @brief Método que verifica los posibles errores de formato del fichero que define el autómata
 * @param file_name Nombre del archivo de entrada
 */
void FiniteAutomaton::CheckFormatErrors(const std::string& file_name) {
  std::ifstream input_file(file_name);
  if (!input_file.is_open()) {
    std::cerr << "P06: Error al abrir los archivos" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Leer la primera línea: Símbolos del alfabeto
  std::string line;
  std::getline(input_file, line);

  // Verificar que los símbolos del alfabeto están separados por espacios
  std::regex alphabet_regex("^([a-zA-Z0-9] )*[a-zA-Z0-9]$");
  if (!std::regex_match(line, alphabet_regex)) {
    std::cerr << "P06: Los símbolos del alfabeto deben estar separados por espacios" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Verificar que el alfabeto no contiene el símbolo '&'
  Alphabet temp_alphabet(line);
  if (temp_alphabet.Belongs(Symbol('&'))) {
    std::cerr << "P06: El símbolo '&' no puede formar parte del alfabeto" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Leer la segunda línea: Número total de estados
  std::getline(input_file, line);
  std::regex number_regex("^[1-9][0-9]*$");
  if (!std::regex_match(line, number_regex)) {
    std::cerr << "P06: El número de estados debe ser un número natural mayor que 0" << std::endl;
    exit(EXIT_FAILURE);
  }
  int number_of_states = std::stoi(line);

  // Leer la tercera línea: Estado de arranque
  std::getline(input_file, line);

  // Verificar que la tercera línea contiene un solo número natural
  std::regex initial_state_regex("^[0-9]+$");
  if (!std::regex_match(line, initial_state_regex)) {
    std::cerr << "P06: Estado inicial inválido, debe ser un solo número natural" << std::endl;
    exit(EXIT_FAILURE);
  }

  int initial_state = std::stoi(line);

  // Verificar que el estado inicial está en el rango permitido
  if (initial_state < 0 || initial_state >= number_of_states) {
    std::cerr << "P06: Estado inicial fuera de rango" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Leer las líneas restantes: Información de los estados y transiciones
  std::set<State> states_defined;
  while (std::getline(input_file, line)) {
    std::istringstream flujo(line);
    State state;
    int acceptance;
    int num_transitions;
    flujo >> state >> acceptance >> num_transitions;

    // Verificar que el estado está en el rango permitido
    if (state < 0 || state >= number_of_states) {
      std::cerr << "P06: Estado " << state << " fuera de rango" << std::endl;
      exit(EXIT_FAILURE);
    }

    // Verificar que el número de aceptación es 0 o 1
    if (acceptance != 0 && acceptance != 1) {
      std::cerr << "P06: El valor de aceptación debe ser 0 o 1" << std::endl;
      exit(EXIT_FAILURE);
    }

    states_defined.insert(state);

    // Leer y almacenar cada transición
    int transitions_count{0};
    for (int i{0}; i < num_transitions; ++i) {
      char symbol_of_transition;
      State destination_state;
      if (!(flujo >> symbol_of_transition >> destination_state)) {
        std::cerr << "P06: Error en la definición de las transiciones para el estado " << state << std::endl;
        exit(EXIT_FAILURE);
      }

      Symbol symbol(symbol_of_transition);

      // Verificar que el símbolo pertenece al alfabeto o es '&'
      if (!temp_alphabet.Belongs(symbol) && symbol_of_transition != EPSILON) {
        std::cerr << "P06: Símbolo " << symbol_of_transition << " no pertenece al alfabeto" << std::endl;
        exit(EXIT_FAILURE);
      }

      // Verificar que el estado de destino está en el rango permitido
      if (destination_state < 0 || destination_state >= number_of_states) {
        std::cerr << "P06: Estado de destino " << destination_state << " fuera de rango" << std::endl;
        exit(EXIT_FAILURE);
      }

      transitions_count++;
    }

    // Verificar que el número de transiciones coincide con las transiciones definidas
    if (static_cast<int>(transitions_count != num_transitions)) {
      std::cerr << "P06: El número de transiciones no coincide con las transiciones definidas" << std::endl;
      exit(EXIT_FAILURE);
    }

    // Verificar que no hay transiciones adicionales
    if (flujo >> std::ws && !flujo.eof()) {
      std::cerr << "P06: Se han definido más transiciones de las declaradas para el estado " << state << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  // Verificar que todos los estados están definidos
  if (static_cast<int>(states_defined.size()) != number_of_states) {
    std::cerr << "P06: No se han definido todas las líneas para los estados del autómata" << std::endl;
    exit(EXIT_FAILURE);
  }

  input_file.close();
}

/**
 * @brief Método que simula el comportamiento del autómata finito para una serie de cadenas
 * @param file_name Nombre del archivo de entrada
 */
void FiniteAutomaton::SimulatePerformance(const std::string& file_name) {
  std::ifstream input_file(file_name);
  if (!input_file.is_open()) {
    std::cerr << "P06: Error al abrir el archivo de entrada" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  while (std::getline(input_file, line)) {
    // Verificar que la línea contiene solo una cadena sin espacios adicionales
    if (line.find(' ') != std::string::npos) {
      std::cerr << "P06: Error en el archivo de entrada para las cadenas, cada línea debe contener solo una cadena" << std::endl;
      exit(EXIT_FAILURE);
    }

    // Manejar la cadena vacía representada como '&'
    std::string input_string = (line == "&") ? "" : line;
    
    std::cout << "\n--- VISUALIZACIÓN DE TRAZA PARA LA CADENA: " << line << " ---\n";
    simulate(input_string);
    std::cout << "\n(PULSE ENTER PARA LA SIGUIENTE CADENA)";
    std::cin.get();
  }
  
  input_file.close();
}