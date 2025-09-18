
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
		if (!first) out << " , ";
		out << str;
		first = false;
	}
	out << "}";
	return out;
}
