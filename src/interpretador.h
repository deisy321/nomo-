#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include <string>
#include <unordered_map>
#include <vector>

struct Tarefa {
    std::string descricao;
    bool concluida;
};

struct Produto {
    std::string nome;
    int quantidade;
};

void interpretar_comando(
    const std::string& linha,
    std::unordered_map<std::string, int>& variaveis,
    std::vector<Tarefa>& tarefas,
    std::unordered_map<std::string, Produto>& estoque
);

#endif
