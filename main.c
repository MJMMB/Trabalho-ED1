#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

void ler_entrada(char *buffer, int tamanho) {
    // Função para ler entradas, evitando quaisquer erros digitados pelo usuário
    if (fgets(buffer, tamanho, stdin) == NULL) {
        buffer[0] = '\0';
        clearerr(stdin);
    }   
    buffer[strcspn(buffer, "\n")] = '\0';
}

int validar_entradas(const char *prompt, int min, int max) {   
    // Função para ler inteiros com validação (para as dimensões das matrizes)
    char buffer[100];
    
    while (1) {
        printf("%s ", prompt);
        ler_entrada(buffer, sizeof(buffer));
        
        char *ptr;
        long num = strtol(buffer, &ptr, 10);
        
        if (ptr == buffer || *ptr != '\0') {
            printf("Erro: Digite apenas números inteiros.\n");
            ;
            continue;
        }
        
        if (num < min || num > max) {
            printf("Erro: Valor incorreto, tente novamente.\n");
            ;
            continue;
        }
        
        return (int)num;
    }
}

float validar_entradas_float(const char *prompt) {
    // Função para ler valores float com validação (para os elementos das matrizes)
    char buffer[100];
    
    while (1) {
        printf("%s ", prompt);
        ler_entrada(buffer, sizeof(buffer));
        
        char *ptr;
        float num = strtof(buffer, &ptr);
        
        if (ptr == buffer || *ptr != '\0') {
            printf("Erro: Digite apenas números válidos (use ponto para float).\n");
            continue;
        }
        
        return num;
    }
}

void tamanhoMatrizes(int *l1, int *c1, int *l2, int *c2) {  
    /* 
        a multiplicação entre matrizes só é possível se o nº de col da primeira
        for igual ao nº de linhas da segunda
    */
    do { 
        printf("\nDigite Linhas e Colunas da Primeira Matriz:\n");
        *l1 = validar_entradas("Número de linhas (1 a 100):", 1, 100);
        *c1 = validar_entradas("Número de colunas (1 a 100):", 1, 100);
        
        printf("\nDigite Linhas e Colunas da Segunda Matriz:\n");
        *l2 = validar_entradas("Número de linhas (1 a 100):", 1, 100);
        *c2 = validar_entradas("Número de colunas (1 a 100):", 1, 100);
        
        if (*c1 != *l2) {
            printf("Ordem das Matrizes Inválidas, tente novamente\n");
        }
    } while(*c1 != *l2);
}

float** alocarMemoria(int linha, int coluna) {
    float **mat = (float **)calloc(linha, sizeof(float *));
    if (!mat) {
        printf("\nErro ao alocar memória.");
        exit(1);
    }

    for(int i = 0; i < linha; i++) {
        mat[i] = (float *)malloc(coluna * sizeof(float));
        if (!mat[i]) {
            printf("\nErro ao alocar memória.");
            exit(1);
        }
    }

    return mat;
}

void entradaValoresMatriz(float **matriz, int linha, int coluna) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            printf("Matriz [%d][%d]: ", i+1, j+1);
            matriz[i][j] = validar_entradas_float("");
        }
    }
}

int ehInteiro(float num) {
    
  return num == (int)num;
}

void mostrarMatriz(float **matriz, int linha, int coluna) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if(ehInteiro(matriz[i][j]))
                printf("| %d\t", (int)matriz[i][j]);
            else{
                printf("| %.2f\t", matriz[i][j]);
                
            }
        }
        printf("|\n");
    }
}

void zerarMatriz(float **res, int linha, int coluna) {
    /*
        Essa função é necessária para que, enquanto o usuário escolha a opção 1 (repetir a operação),
        os valores da função resposta não se acumulem.
    */
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            res[i][j] = 0;
        }
    }
}

void multiplicarMatriz(float **mat1, float **mat2, float **res, int l1, int c1, int l2, int c2, int linha, int coluna, int k) {
    if(!mat1 || !mat2 || !res) {
        printf("\nErro ao alocar memória.");
        exit(1);
    }

    if (linha >= l1)
        return;
    if (coluna >= c2) {
        multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, linha + 1, 0, 0);
        return;
    }
    if (k >= c1) {
        multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, linha, coluna + 1, 0);
        return;
    }

    res[linha][coluna] += mat1[linha][k] * mat2[k][coluna];
    multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, linha, coluna, k + 1);
}

void liberarMemoria(float **mat1, float **mat2, float **res, int l1, int l2) {
    for (int i = 0; i < l1; i++) {
        free(mat1[i]);
    }
    free(mat1);

    for (int i = 0; i < l2; i++) {
        free(mat2[i]);
    }
    free(mat2);

    for (int i = 0; i < l1; i++) {
        free(res[i]);
    }
    free(res);
}

void repetirProcesso(int *r) {
    *r = validar_entradas("\nDeseja repetir o processo? 1 = SIM | 0 = NÃO -> ", 0, 1);
}

int main() {
    setlocale(LC_ALL, "portuguese");

    // interação de loop com o usuário
    int r = 1;

    do {
        float **mat1, **mat2, **res;
        int l1, c1, l2, c2;

        tamanhoMatrizes(&l1, &c1, &l2, &c2);
        
        mat1 = alocarMemoria(l1, c1);
        mat2 = alocarMemoria(l2, c2);
        res = alocarMemoria(l1, c2);

        printf("\nDigite cada elemento da matriz 1: \n");
        entradaValoresMatriz(mat1, l1, c1);

        printf("\nDigite cada elemento da matriz 2: \n");
        entradaValoresMatriz(mat2, l2, c2);

        // Print Matriz 1
        printf("\nPrimeira Matriz: \n");
        mostrarMatriz(mat1, l1, c1);

        // Print Matriz 2
        printf("\nSegunda Matriz: \n");
        mostrarMatriz(mat2, l2, c2);

        // chamando a função zerar e multiplicarMatriz()
        zerarMatriz(res, l1, c2);
        multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, 0, 0, 0);

        // Resultado da matriz
        printf("\nMultiplicação das Duas Matrizes:\n");
        mostrarMatriz(res, l1, c2);

        // Liberar Memória
        liberarMemoria(mat1, mat2, res, l1, l2);
        
        repetirProcesso(&r);
    } while (r == 1);

    return 0;
}