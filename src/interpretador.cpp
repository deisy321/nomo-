#include "interpretador.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <windows.h>
#include <algorithm>

// Função auxiliar para remover espaços extras
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Função para normalizar strings (ignorar maiúsculas/minúsculas e espaços extras)
std::string normalizar(const std::string& s) {
    std::string out = s;
    // Converter para minúsculas
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    // Remover espaços extras
    out.erase(remove(out.begin(), out.end(), ' '), out.end());
    return out;
}

void interpretar_comando(
    const std::string& linhaOriginal,
    std::unordered_map<std::string, int>& variaveis,
    std::vector<Tarefa>& tarefas,
    std::unordered_map<std::string, Produto>& estoque
) {
    std::string linha = trim(linhaOriginal);

    if (linha == "pass") return;

    // Comando "definir"
    if (linha.rfind("definir ", 0) == 0) {
        size_t comoPos = linha.find(" como ");
        if (comoPos != std::string::npos) {
            std::string nomeVar = trim(linha.substr(8, comoPos - 8));
            int valorVar = std::stoi(linha.substr(comoPos + 6));
            variaveis[nomeVar] = valorVar;
        } else {
            std::cout << "[ERRO] Sintaxe: definir nome como valor\n";
        }
        return;
    }

    // Comando "eco"
    if (linha.rfind("eco ", 0) == 0) {
        std::string mensagem = linha.substr(4);
        for (std::unordered_map<std::string, int>::iterator it = variaveis.begin(); it != variaveis.end(); ++it) {
            std::string marcador = "@" + it->first;
            size_t pos = 0;
            while ((pos = mensagem.find(marcador, pos)) != std::string::npos) {
                mensagem.replace(pos, marcador.length(), std::to_string(it->second));
            }
        }
        std::cout << mensagem << std::endl;
        return;
    }

     // Se o comando for "calcular"
    if (linha.rfind("calcular ", 0) == 0) {
        std::string expressao = linha.substr(9);  // Pega a expressão depois de "calcular"
        std::istringstream iss(expressao);
        int num1, num2;
        char operacao;

        // Tenta interpretar a expressão no formato "numero1 operador numero2"
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
            std::cout << "Resultado: " << resultado << std::endl;
        } else {
            std::cout << "[ERRO] Sintaxe inválida para calcular. Use: calcular num1 operador num2\n";
        }
        return;
    }


    // Comando "espera"
    if (linha.rfind("espera ", 0) == 0) {
        try {
            int segundos = std::stoi(linha.substr(7));
            Sleep(segundos * 1000);
        } catch (...) {
            std::cout << "[ERRO] espera precisa de número válido.\n";
        }
        return;
    }

    // Comando "ler"
    if (linha.rfind("ler ", 0) == 0) {
        std::string nomeVariavel = trim(linha.substr(4));
        int valor;
        std::cout << "Digite um valor para " << nomeVariavel << ": ";
        std::cin >> valor;
        variaveis[nomeVariavel] = valor;
        return;
    }

    // Comando "adicionar tarefa"
    if (linha.rfind("adicionar tarefa ", 0) == 0) {
        std::string desc = trim(linha.substr(18));
        tarefas.push_back({desc, false});
        std::cout << "Tarefa \"" << desc << "\" adicionada!\n";
        return;
    }

    // Comando "listar tarefas"
    if (linha == "listar tarefas") {
        for (const auto& tarefa : tarefas) {
            std::cout << "[" << (tarefa.concluida ? "Concluída" : "Pendente") << "] " << tarefa.descricao << "\n";
        }
        return;
    }

    // Comando "marcar concluída"
    if (linha.rfind("marcar concluída ", 0) == 0) {
        std::string desc = trim(linha.substr(18));
        bool achou = false;
        for (auto& tarefa : tarefas) {
            if (normalizar(tarefa.descricao) == normalizar(desc)) {
                tarefa.concluida = true;
                achou = true;
                break;
            }
        }
        if (!achou) {
            std::cout << "[ERRO] Tarefa \"" << desc << "\" não encontrada.\n";
        }
        return;
    }

    // Comando "adicionar produto"
    if (linha.rfind("adicionar produto ", 0) == 0) {
        size_t emPos = linha.find(" em ");
        if (emPos != std::string::npos) {
            std::string nome = trim(linha.substr(18, emPos - 18));
            int qtd = std::stoi(linha.substr(emPos + 4));
            estoque[nome] = {nome, qtd};
            std::cout << "Produto \"" << nome << "\" adicionado ao estoque. Quantidade: " << qtd << "\n";
        } else {
            std::cout << "[ERRO] Sintaxe: adicionar produto NOME em QUANTIDADE\n";
        }
        return;
    }

    // Comando "listar estoque"
    if (linha == "listar estoque") {
        for (std::unordered_map<std::string, Produto>::iterator it = estoque.begin(); it != estoque.end(); ++it) {
            std::cout << it->second.nome << ": " << it->second.quantidade << " unidades\n";
        }
        return;
    }

    // Caso não seja um comando válido
    std::cout << "[ERRO] Comando desconhecido.\n";
}
