#include "jogoDaVida.hpp"

void pedirNumeroGeracoes(int& qntGeracoes) {
    system("clear");
    std::cout << "--- Jogo da Vida ---\n";
    std::cout << "Seja bem-vindo! \nQuantas gerações você deseja simular? (Digite um número inteiro)\n";
    std::cin >> qntGeracoes;
    std::cout << "\nIniciando simulação do Jogo da Vida com " << qntGeracoes << " gerações...\n--------" << std::endl;
}

void execucaoJogoDaVida(int** matriz, int linhas, int colunas, int qntGeracoes) {
    int** matrizNova = matriz;
    if (matriz != nullptr) {
        for (int i = 0; i < qntGeracoes; i++) {
            matrizNova = gerarProximaMatriz(matrizNova, linhas, colunas);
            std::cout << "Geração " << i + 1 << " finalizada com sucesso!" << std::endl;
        }
    }

    std::cout << "\nTodas as gerações finalizadas com sucesso! \nOs resultados estao disponiveis no arquivo 'geracoes.mps'\n--------" << std::endl;
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
