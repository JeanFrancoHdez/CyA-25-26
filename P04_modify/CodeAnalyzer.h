// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones regulares en C++
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 05/10/2025
// Archivo "CodeAnalyzer.h"
// Contiene la declaración de la clase "CodeAnalyzer"

#ifndef CODEANALYZER_H
#define CODEANALYZER_H

#include "Variable.h"
#include "Statement.h" 
#include "Comment.h"
#include "IncludeDeclaration.h"
#include <vector>
#include <string>
#include <fstream>
#include <regex>

class CodeAnalyzer {
  public:
    CodeAnalyzer(const std::string& filename);
    void analyzeCode();
    void generateReport(const std::string& output_filename);
    
  private:
    std::string filename_;
    std::string description_;
    std::vector<Variable> variables_;
    std::vector<Statement> statements_;
    std::vector<Comment> comments_;
    std::vector<IncludeDeclaration> includes_;
    bool has_main_;
    bool has_else_;
    int angle_bracket_includes_count_;
    int quote_includes_count_;
    
    // Métodos auxiliares
    void analyzeVariables(const std::string& line, int line_number);
    void analyzeStatements(const std::string& line, int line_number);
    void analyzeComments(const std::string& line, int line_number);
    void analyzeMain(const std::string& line);
    void analyzeIncludes(const std::string& line, int line_number);
    void extractDescription();
    
    // Expresiones regulares
    std::regex var_regex_;
    std::regex for_regex_;
    std::regex while_regex_;
    std::regex main_regex_;
    std::regex include_angle_regex_;
    std::regex include_quote_regex_;
    std::regex single_comment_regex_;
    std::regex multi_comment_begin_regex_;
    std::regex multi_comment_end_regex_;
};

#endif