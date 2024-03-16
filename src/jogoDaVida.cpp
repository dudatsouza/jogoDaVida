#include "jogoDaVida.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int** lerMatriz(std::string nomeArquivo, int& linhas, int& colunas) {
    // Abrindo o arquivo
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return nullptr;
    }

    // Determinando o tamanho da matriz
    linhas = 0;
    colunas = 0;
    std::string linha;
    int auxColuna = 0;

    while (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        int valor;
        colunas = 0;
        while (iss >> valor) {
            colunas++;
        }

        if (linhas == 0) {
            auxColuna = colunas;
        } else {
            if (auxColuna != colunas) {
                std::cerr << "A matriz lida do arquivo não é retangular." << std::endl;
                arquivo.close();
                return nullptr;
            }
        }

        linhas++;
    }

    // Verificar se a matriz tem no mínimo 5x5
    if (linhas < 5 || colunas < 5) {
        std::cerr << "A matriz lida do arquivo deve ter no mínimo 5x5." << std::endl;
        arquivo.close();
        return nullptr;
    }

    // Reposicionar o ponteiro do arquivo para o início
    arquivo.clear();
    arquivo.seekg(0);

    // Alocar a matriz dinamicamente
    int** matriz = new int*[linhas];
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new int[colunas];
    }

    // Ler os valores do arquivo para a matriz
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arquivo >> matriz[i][j];
        }
    }
    // Fechar o arquivo
    arquivo.close();

// colocara matriz no arquivo geracoes.mps
    std::ofstream arquivo2("datasets/geracoes.mps");
    if (arquivo2.is_open()) {
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                arquivo2 << matriz[i][j] << " ";
            }
            arquivo2 << std::endl;
        }
        arquivo2 << std::endl;
        arquivo2.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo geracoes.mps" << std::endl;
    }


    return matriz;
}

void liberarMatriz(int** matriz, int linhas) {
    for (int i = 0; i < linhas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

int** gerarProximaMatriz(int** matriz, int linhas, int colunas){
// - Uma célula viva com menos de dois vizinhos vivos morre (solidão).
// - Uma célula viva com mais de três vizinhos vivos morre (superpopulação).
// - Uma célula viva com dois ou três vizinhos vivos sobrevive.
// - Uma célula morta com exatamente três vizinhos vivos se torna viva (reprodução).

//  A cada interação, faça as avaliações utilizando a matriz atual e produza os
// resultados da avaliação em uma nova matriz. Feito isso, salve a matriz avaliada
// como parte de seus resultados em um arquivo chamado geracoes.mps.

    int **matrizNova = new int*[linhas];
    for (int i = 0; i < linhas; ++i) {
        matrizNova[i] = new int[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matrizNova[i][j] = matriz[i][j];
        }
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int vizinhos = 0;
            if (i > 0 && j > 0 && matriz[i-1][j-1] == 1) {
                vizinhos++;
            }
            if (i > 0 && matriz[i-1][j] == 1) {
                vizinhos++;
            }
            if (i > 0 && j < colunas-1 && matriz[i-1][j+1] == 1) {
                vizinhos++;
            }
            if (j > 0 && matriz[i][j-1] == 1) {
                vizinhos++;
            }
            if (j < colunas-1 && matriz[i][j+1] == 1) {
                vizinhos++;
            }
            if (i < linhas-1 && j > 0 && matriz[i+1][j-1] == 1) {
                vizinhos++;
            }
            if (i < linhas-1 && matriz[i+1][j] == 1) {
                vizinhos++;
            }
            if (i < linhas-1 && j < colunas-1 && matriz[i+1][j+1] == 1) {
                vizinhos++;
            }

            if (matriz[i][j] == 1) {
                if (vizinhos < 2 || vizinhos > 3) {
                    matrizNova[i][j] = 0;
                }
            } else {
                if (vizinhos == 3) {
                    matrizNova[i][j] = 1;
                }
            }
        }
    }

// o arquivo tem q salvar todas as gerações, ou seja, nao pode sobrescrever
    std::ofstream arquivo("datasets/geracoes.mps", std::ios::app);
    if (arquivo.is_open()) {
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                arquivo << matrizNova[i][j] << " ";
            }
            arquivo << std::endl;
        }
        arquivo << std::endl;
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo geracoes.mps" << std::endl;
    }

    return matrizNova;
}