#include "jogoDaVida.hpp"

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

    if(!verificarFormatoMatriz(matriz, linhas, colunas)) {
        return nullptr;
    }

    // colocar a matriz no arquivo
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
        return nullptr;
    }

    return matriz;
}

bool verificarFormatoMatriz(int **matriz, int linhas, int colunas) {
    int contador1 = 0;
    int contador0 = 0;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] == 1) {
                contador1++;
            } else {
                contador0++;
            }
        }
    } 

    // A cada 2 0s, tem que ter 1 1
    if ((contador0/2) <= contador1) {
        std::cerr << "A matriz lida do arquivo não está em formato 2 para 1. Tendo " << contador1 << " quantidade de 1s e " << contador0 << " quantidade de 0s." << std::endl;
        return false;
    }
    
    return true;
}

void liberarMatriz(int** matriz, int linhas) {
    for (int i = 0; i < linhas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

int** gerarProximaMatriz(int** matriz, int linhas, int colunas){
    // Alocar a matriz auxiliar dinamicamente
    int **matrizNova = new int*[linhas];
    for (int i = 0; i < linhas; ++i) {
        matrizNova[i] = new int[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matrizNova[i][j] = matriz[i][j];
        }
    }

    // Analisar cada célula da matriz
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {

            // Verificar a quantidade de vizinhos de cada célula
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

            // Aplicar as regras do jogo
            if (matriz[i][j] == 1) { 
                if (vizinhos == 2 || vizinhos == 3) {
                    matrizNova[i][j] = 1;
                } else if (vizinhos < 2 || vizinhos > 3) {
                    matrizNova[i][j] = 0;
                }
            } else {
                if (vizinhos == 3) {
                    matrizNova[i][j] = 1;
                }
            }
        }
    }

    // colocar a matriz no arquivo
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
        return nullptr;
    }

    return matrizNova;
}
