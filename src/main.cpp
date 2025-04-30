#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <windows.h>  // Para usar Sleep()
#include <sstream>    // Para stringstream (conversão de strings)

int main() {
    std::unordered_map<std::string, int> variaveis;
    std::string linha;

    std::cout << "NOMO Interpreter v0.4 iniciado. Digite 'fim' para sair.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, linha);

        if (linha == "fim") {
            std::cout << "Encerrando NOMO...\n";
            break;
        }

        // Comando: pass
        if (linha == "pass") {
            continue;
        }

        // Comando: definir nome como valor
        if (linha.rfind("definir ", 0) == 0) {
            size_t comoPos = linha.find(" como ");
            if (comoPos != std::string::npos) {
                std::string nomeVar = linha.substr(8, comoPos - 8);
                int valorVar = std::stoi(linha.substr(comoPos + 6));
                variaveis[nomeVar] = valorVar;
            } else {
                std::cout << "[ERRO] Sintaxe: definir nome como valor\n";
            }
            continue;
        }

        // Comando: calcular expressao
        if (linha.rfind("calcular ", 0) == 0) {
            std::string expressao = linha.substr(9);
            std::istringstream iss(expressao);
            int num1, num2;
            char operacao;

            // Lê a expressão, ex: "10 + 5"
            if (iss >> num1 >> operacao >> num2) {
                int resultado = 0;
                switch (operacao) {
                    case '+':
                        resultado = num1 + num2;
                        break;
                    case '-':
                        resultado = num1 - num2;
                        break;
                    case '*':
                        resultado = num1 * num2;
                        break;
                    case '/':
                        if (num2 != 0) {
                            resultado = num1 / num2;
                        } else {
                            std::cout << "[ERRO] Divisão por zero!\n";
                            continue;
                        }
                        break;
                    default:
                        std::cout << "[ERRO] Operação inválida. Use +, -, * ou /.\n";
                        continue;
                }

                // Armazena o resultado em uma variável chamada "resultado"
                variaveis["resultado"] = resultado;
                std::cout << "Resultado: " << resultado << std::endl;
            } else {
                std::cout << "[ERRO] Sintaxe inválida para calcular. Use: calcular num1 operação num2\n";
            }
            continue;
        }

        // Comando: espera 2 (Agora usando Sleep() do Windows)
        if (linha.rfind("espera ", 0) == 0) {
            try {
                int segundos = std::stoi(linha.substr(7));
                Sleep(segundos * 1000);  // Sleep espera em milissegundos
            } catch (...) {
                std::cout << "[ERRO] espera precisa de número válido.\n";
            }
            continue;
        }

        // Comando: eco
        if (linha.rfind("eco ", 0) == 0) {
            std::string mensagem = linha.substr(4);
            // Substituir @variaveis
            for (auto it = variaveis.begin(); it != variaveis.end(); ++it) {
                std::string marcador = "@" + it->first;
                size_t pos = 0;
                while ((pos = mensagem.find(marcador, pos)) != std::string::npos) {
                    mensagem.replace(pos, marcador.length(), std::to_string(it->second));
                }
            }
            std::cout << mensagem << std::endl;
            continue;
        }

        std::cout << "[ERRO] Comando desconhecido.\n";
    }

    return 0;
}
