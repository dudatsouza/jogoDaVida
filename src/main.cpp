#include <iostream>
#include <string>
#include "jogoDaVida.hpp"

void pedirNumeroGeracoes(int& qntGeracoes) {
    std::cout << "Digite a quantidade de gerações: ";
    std::cin >> qntGeracoes;
}

void execucaoJogoDaVida(int** matriz, int linhas, int colunas, int qntGeracoes) {
    int** matrizNova = matriz;
    if (matriz != nullptr) {
        for (int i = 0; i < qntGeracoes; i++) {
            matrizNova = gerarProximaMatriz(matrizNova, linhas, colunas);
            std::cout << "Geração " << i + 1 << " finalizada com sucesso!" << std::endl;
        }
    }

    std::cout << "Todas as gerações finalizadas com sucesso! Os resultados estao disponiveis no arquivo 'geracoes.mps'" << std::endl;
    liberarMatriz(matrizNova, linhas);
}

int main() {
    std::string nomeArquivo = "datasets/input.mps"; // Caminho para o arquivo input.mps
    int linhas, colunas;
    int** matriz = lerMatriz(nomeArquivo, linhas, colunas);
    int qntGeracoes; 

    pedirNumeroGeracoes(qntGeracoes);
    execucaoJogoDaVida(matriz, linhas, colunas, qntGeracoes);
    liberarMatriz(matriz, linhas);
    return 0;
}
