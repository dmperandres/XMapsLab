#include "tokenizer.h"

// Función auxiliar para procesar la tokenización
std::vector<std::string> _tokenizer::tokenize(const std::string& str, char delimiter) {
  // Reducir repeticiones del delimitador
  std::string reduced_str = std::regex_replace(str, std::regex(std::string(1, delimiter) + "{2,}"), std::string(1, delimiter));

  // Tokenizar la cadena
  std::vector<std::string> tokens;
  std::stringstream ss(reduced_str);
  std::string token;

  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}


