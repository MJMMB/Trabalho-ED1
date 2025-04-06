#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void tamanhoMatrizes(int *l1, int *c1, int *l2, int *c2) {  
    /* 
        a multiplicação entre matrizes só é possível se o nº de col da primeira
        for igual ao nº de linhas da segunda
    */
    do { 
        printf("\nDigite Linhas e Colunas da Primeira Matriz:\n");
        scanf("%d %d", l1, c1);
        printf("\nDigite Linhas e Colunas da Segunda Matriz:\n");
        scanf("%d %d", l2, c2);
        
        if (*c1 != *l2) {
            printf("Ordem das Matrizes Inválidas, tente novamente\n");
        }
    } while(*c1 != *l2);
}

int** alocarMemoria(int linha, int coluna) {
    int **mat;
    mat = (int **)calloc(linha, sizeof(int *));

    for(int i = 0; i < linha; i++) {
        mat[i] = (int *)malloc(coluna * sizeof(int));
    }

    return mat;
}

void entradaValoresMatriz(int **matriz, int linha, int coluna) {
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
}

void mostrarMatriz(int **matriz, int linha, int coluna) {
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void zerarMatriz(int **res, int linha, int coluna) {
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

void multiplicarMatriz(int **mat1, int **mat2, int **res, int l1, int c1, int l2, int c2, int linha, int coluna, int k)
{
    if (linha >= l1)
        return;
    if (coluna >= c2)
    {
        multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, linha + 1, 0, 0);
        return;
    }
    if (k >= c1)
    {
        multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, linha, coluna + 1, 0);
        return;
    }


    res[linha][coluna] += mat1[linha][k] * mat2[k][coluna];
    multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, linha, coluna, k + 1);
}

void mostrarResultado(int **res, int linha, int coluna) {
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            printf("%d\t", res[i][j]);
        }
        printf("\n");
    }
}

void liberarMemoria(int **mat1, int **mat2, int **res, int l1, int l2) {
    for (int i = 0; i < l1; i++)
    {
        free(mat1[i]);
    }
    free(mat1);

    for (int i = 0; i < l2; i++)
    {
        free(mat2[i]);
    }
    free(mat2);

    for (int i = 0; i < l1; i++)
    {
        free(res[i]);
    }
    free(res);
}

void repetirProcesso(int *r) {
    do {
        printf("\nDeseja repetir o processo? 1 = SIM / 0 = NÃO -> ");
        scanf("%d", r);
    } while(*r != 0 && *r != 1);
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    //interação de loop com o usuário
    int r = 1;

    do
    {
        int **mat1, **mat2, **res, l1, c1, l2, c2;

        tamanhoMatrizes(&l1, &c1, &l2, &c2);
        
        mat1 = alocarMemoria(l1, c1);
        mat2 = alocarMemoria(l2, c2);
        res  = alocarMemoria(l1, c2);

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

        //chamando a função zerar e multiplicarMatriz()
        zerarMatriz(res, l1, c2);
        multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, 0, 0, 0);

        // Resultado da matriz
        printf("\nMultiplicação das Duas Matrizes:\n");
        mostrarResultado(res, l1, c2);

        // Liberar Memória
        liberarMemoria(mat1, mat2, res, l1, l2);
        
        repetirProcesso(&r);
    } while (r == 1);

    return 0;
}
