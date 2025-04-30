#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "interpretador.h"

int main() {
    std::unordered_map<std::string, int> variaveis;

    // Aqui você escreve seus comandos NOMO como se fosse um script
    std::vector<std::string> comandos = {
        "pass",
        "definir idade como 25",
        "eco Minha idade é @idade",
        "calcular 10 + 5",
        "eco Resultado da soma é @resultado",
        "espera 2",
        "eco Fim do script!"
    };

    for (const std::string& cmd : comandos) {
        interpretar_comando(cmd, variaveis);
    }

    return 0;
}
