#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>
#include "interpretador.h"

int main() {
    std::unordered_map<std::string, int> variaveis;
    std::vector<Tarefa> tarefas;
    std::unordered_map<std::string, Produto> estoque;

    std::string entrada;
    std::cout << "Calculadora NOMO - Digite uma expressão (ex: 3 + 5), ou 'sair' para finalizar.\n";

    while (true) {
        std::cout << "Digite a expressão: ";
        std::getline(std::cin, entrada);

        if (entrada == "sair") {
            break;  // Encerra o programa
        }

        // Adiciona o comando "calcular" ao que foi digitado
        std::string comando = "calcular " + entrada;
        
        // Interpreta o comando
        interpretar_comando(comando, variaveis, tarefas, estoque);
    }

    return 0;
}
