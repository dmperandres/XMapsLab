#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>

class _tokenizer {
public:
  // Constructor por defecto
  _tokenizer() = default;

  // Función miembro para tokenizar
  // std::vector<std::string> get_tokens(const std::string& str, char delimiter) const {
  //     return tokenize(str, delimiter);
  // }

  // Función estática para tokenizar
  static std::vector<std::string> get_tokens(const std::string& str, char delimiter) {
      return tokenize(str, delimiter);
  }

private:
  // Función auxiliar para procesar la tokenización
  static std::vector<std::string> tokenize(const std::string& str, char delimiter);
};
#endif
