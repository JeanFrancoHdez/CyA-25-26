// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Jean Franco Hernández García
// Correo: alu0101538853@ull.edu.es
// Fecha: 19/09/2025
// Archivo "Language.cc"
// Contiene el cuerpo de los métodos declarados en "Language.h"
// Referencias:
// Enlaces de interés
//
// Historial de revisiones
// 19/09/2025 - Creación (primera versión) del código

#include "Language.h"

Language::Language() {}

Language::Language(const std::set<String>& strings) : language_(strings) {}

void Language::AddString(const String& str) {
	language_.insert(str);
}

const std::set<String>& Language::GetStrings() const {
	return language_;
}

size_t Language::Size() const {
	return language_.size();
}

std::ostream& operator<<(std::ostream& out, const Language& language) {
	out << "{";
	bool first = true;
	for (const auto& str : language.language_) {
		if (!first) out << ", ";
		out << str;
		first = false;
	}
	out << "}";
	return out;
}
