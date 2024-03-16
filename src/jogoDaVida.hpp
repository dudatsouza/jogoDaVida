#ifndef JOGODAVIDA_HPP
#define JOGODAVIDA_HPP

#include <string>

int** lerMatriz(std::string nomeArquivo, int& linhas, int& colunas);
void liberarMatriz(int** matriz, int linhas);
int** gerarProximaMatriz(int** matriz, int linhas, int colunas);

#endif // JOGODAVIDA_HPP
