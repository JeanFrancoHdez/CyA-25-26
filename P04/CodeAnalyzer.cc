// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 05/10/2025
// Archivo "CodeAnalyzer.cc"
// Contiene la implementación de la clase "CodeAnalyzer"

#include "CodeAnalyzer.h"
#include <iostream>
#include <sstream>

CodeAnalyzer::CodeAnalyzer(const std::string& filename) {
  filename_ = filename;
  has_main_ = false;
  var_regex_ = std::regex(R"(^\s*(int|double)\s+(\w+)\s*(?:=\s*([^;]+))?\s*;)");
  for_regex_ = std::regex(R"(^\s*for\s*\()");
  while_regex_ = std::regex(R"(^\s*while\s*\()");
  main_regex_ = std::regex(R"(\bint\s+main\s*\()");
  single_comment_regex_ = std::regex(R"(^\s*//(.*)$)");
  multi_comment_begin_regex_ = std::regex(R"(/\*(.*)$)");
  multi_comment_end_regex_ = std::regex(R"(^(.*)\*/)");
}

void CodeAnalyzer::analyzeCode() {
  std::ifstream file(filename_);
  if (!file.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + filename_);
  }
  
  std::string line;
  int line_number = 0;
  bool in_multiline_comment = false;
  int multiline_start = 0;
  std::string multiline_content = "";
  
  while (std::getline(file, line)) {
    line_number++;
    
    std::smatch match;
    
    if (std::regex_search(line, match, single_comment_regex_)) {
      std::string content = match[1].str();
      comments_.emplace_back(line_number, line_number, "//", content);
      if (line_number == 1) {
        description_ += line + "\n";
      }
      continue; // Si es un comentario, no analizar como código
    }
    
    if (std::regex_search(line, match, multi_comment_begin_regex_) && !in_multiline_comment) {
      in_multiline_comment = true;
      multiline_start = line_number;
      multiline_content = line + "\n";
      if (line_number == 1) {
        description_ += line + "\n";
      }
      
      if (std::regex_search(line, multi_comment_end_regex_)) {
        in_multiline_comment = false;
        comments_.emplace_back(multiline_start, line_number, "/**/", multiline_content);
        multiline_content = "";
      }
      continue;
    }
    
    if (in_multiline_comment) {
      multiline_content += line + "\n";
      if (line_number == 1 || (multiline_start == 1)) {
        description_ += line + "\n";
      }
      
      if (std::regex_search(line, multi_comment_end_regex_)) {
        in_multiline_comment = false;
        comments_.emplace_back(multiline_start, line_number, "/**/", multiline_content);
        multiline_content = "";
      }
      continue;
    }
    
    analyzeVariables(line, line_number);
    analyzeStatements(line, line_number);
    analyzeMain(line);
  }
  
  file.close();
}

void CodeAnalyzer::analyzeVariables(const std::string& line, int line_number) {
  std::smatch match;
  if (std::regex_match(line, match, var_regex_)) {
    std::string type = match[1].str();
    std::string name = match[2].str();
    std::string value = match[3].str();
    bool initialized = !value.empty();
    
    variables_.emplace_back(line_number, type, name, value, initialized);
  }
}

void CodeAnalyzer::analyzeStatements(const std::string& line, int line_number) {
  std::smatch match;
  
  if (std::regex_search(line, match, for_regex_)) {
    statements_.emplace_back(line_number, "LOOP", "for");
  }
  
  if (std::regex_search(line, match, while_regex_)) {
    statements_.emplace_back(line_number, "LOOP", "while");
  }
}

void CodeAnalyzer::analyzeMain(const std::string& line) {
  if (std::regex_search(line, main_regex_)) {
    has_main_ = true;
  }
}

void CodeAnalyzer::generateReport(const std::string& output_filename) {
  std::ofstream file(output_filename);
  if (!file.is_open()) {
    throw std::runtime_error("No se pudo crear el archivo: " + output_filename);
  }
  
  file << "PROGRAM: " << filename_ << "\n";
  
  file << "DESCRIPTION:\n";
  if (!description_.empty()) {
    file << description_;
  }
  file << "\n";
  
  file << "VARIABLES:\n";
  for (const auto& var : variables_) {
    file << var;
  }
  
  file << "\nSTATEMENTS:\n";
  for (const auto& stmt : statements_) {
    file << stmt;
  }
  
  file << "\nMAIN:\n";
  file << (has_main_ ? "True" : "False") << "\n";
  
  file << "\nCOMMENTS:\n";
  for (const auto& comment : comments_) {
    if (comment.getStartLine() == 1) {
      file << comment << "DESCRIPTION\n";
    } else {
      if (comment.getType() == "//") {
        file << comment << "//" << comment.getContent() << "\n";
      } else {
        file << comment << "\n" << comment.getContent() << "\n";
      }
    }
  }
  
  file.close();
}