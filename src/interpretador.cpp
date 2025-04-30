#include "interpretador.h"
#include <iostream>
#include <sstream>
#include <windows.h>

void interpretar_comando(const std::string& linha, std::unordered_map<std::string, int>& variaveis) {
    if (linha == "pass") return;

    if (linha.rfind("definir ", 0) == 0) {
        size_t comoPos = linha.find(" como ");
        if (comoPos != std::string::npos) {
            std::string nomeVar = linha.substr(8, comoPos - 8);
            int valorVar = std::stoi(linha.substr(comoPos + 6));
            variaveis[nomeVar] = valorVar;
        } else {
            std::cout << "[ERRO] Sintaxe: definir nome como valor\n";
        }
        return;
    }

    if (linha.rfind("calcular ", 0) == 0) {
        std::string expressao = linha.substr(9);
        std::istringstream iss(expressao);
        int num1, num2;
        char operacao;

        if (iss >> num1 >> operacao >> num2) {
            int resultado = 0;
            switch (operacao) {
                case '+': resultado = num1 + num2; break;
                case '-': resultado = num1 - num2; break;
                case '*': resultado = num1 * num2; break;
                case '/':
                    if (num2 != 0) resultado = num1 / num2;
                    else {
                        std::cout << "[ERRO] Divisão por zero!\n";
                        return;
                    }
                    break;
                default:
                    std::cout << "[ERRO] Operação inválida.\n";
                    return;
            }

            variaveis["resultado"] = resultado;
            std::cout << "Resultado: " << resultado << std::endl;
        } else {
            std::cout << "[ERRO] Sintaxe inválida para calcular\n";
        }
        return;
    }

    if (linha.rfind("espera ", 0) == 0) {
        try {
            int segundos = std::stoi(linha.substr(7));
            Sleep(segundos * 1000);
        } catch (...) {
            std::cout << "[ERRO] espera precisa de número válido.\n";
        }
        return;
    }

    if (linha.rfind("eco ", 0) == 0) {
        std::string mensagem = linha.substr(4);
        // Alteração: Loop tradicional (compatível com GCC 6.3.0)
        for (auto it = variaveis.begin(); it != variaveis.end(); ++it) {
            std::string marcador = "@" + it->first;
            size_t pos = 0;
            while ((pos = mensagem.find(marcador, pos)) != std::string::npos) {
                mensagem.replace(pos, marcador.length(), std::to_string(it->second));
            }
        }
        std::cout << mensagem << std::endl;
        return;
    }

    std::cout << "[ERRO] Comando desconhecido.\n";
}
