#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include <string>
#include <unordered_map>

void interpretar_comando(const std::string& linha, std::unordered_map<std::string, int>& variaveis);

#endif  // INTERPRETADOR_H
