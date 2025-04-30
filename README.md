# Documentação da Linguagem NOMO

## Visão Geral

**NOMO** é uma linguagem de programação simples e intuitiva criada para ensinar conceitos básicos de programação e facilitar a criação de scripts interativos. Com **NOMO**, você pode definir variáveis, executar operações aritméticas, exibir mensagens e muito mais.

## Comandos da Linguagem NOMO

### 1. `definir [nome] como [valor]`

**Descrição**: Define uma variável e atribui a ela um valor.

**Exemplo**:

```nomo
definir nome como Deisy
definir idade como 25
### 2. `eco [mensagem] ´

**Descrição: Exibe uma mensagem na tela, podendo substituir variáveis dentro dela com o prefixo @.

Exemplo:

nomo
Copiar
Editar
eco Olá, @nome! Você tem @idade anos.

3. calcular [num1] [operador] [num2]
Descrição: Realiza uma operação aritmética simples entre dois números.

Operadores disponíveis: +, -, *, /

Exemplo:

calcular 10 + 5
calcular 15 - 7
calcular 3 * 4
calcular 20 / 4

espera [segundos]
Descrição: Faz o programa esperar por um número de segundos antes de continuar.

Exemplo:


espera 5

5. fim
Descrição: Encerra a execução do interpretador NOMO.

Exemplo:


fim
6. pass
Descrição: Comando vazio para ignorar a linha de comando sem execução.

Exemplo:


pass

7. mostrar [variável]
Descrição: Exibe o valor de uma variável no console.

Exemplo:


mostrar nome

8. listar
Descrição: Lista todas as variáveis definidas e seus valores.

Exemplo:


listar
Funções Adicionais e Expansões Futuras
Além dos comandos básicos, a linguagem NOMO pode ser expandida para incluir funções como:

Condicionais: se / senão

Laços: enquanto (loop while) e para (loop for)

Funções: Permitir que o usuário defina funções próprias.

Exemplo Completo

definir nome como Deisy
definir idade como 25
eco Olá, @nome! Você tem @idade anos.
calcular 10 + 5
eco O resultado de 10 + 5 é @resultado
espera 3
fim

Instruções de Uso
Compile o código usando o compilador C++:


g++ -std=c++11 src\\main.cpp -o 1c-.exe
Execute o interpretador NOMO:
.\\1c-.exe