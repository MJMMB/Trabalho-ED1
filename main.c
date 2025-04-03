#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

int main()
{

    setlocale(LC_ALL, "portuguese");

    while (1)
    {

        int **mat1, **mat2, **res, i, j, l1, c1, l2, c2;

        // Verifica se Multiplicação é Possível
        do
        {
            // Dimensão das Matrizes
            printf("\nDigite Linhas e Colunas da Primeira Matriz:\n");
            scanf("%d %d", &l1, &c1);
            printf("\nDigite Linhas e Colunas da Segunda Matriz:\n");
            scanf("%d %d", &l2, &c2);
            
            if (c1 != l2)
            {
                printf("Ordem das Matrizes Inválidas, tente novamente\n");
                
            }
            
            
        } while (c1 != l2);
        
            
        // Alocar Memória da Matriz 1
        mat1 = (int **)malloc(l1 * sizeof(int *));
        for (i = 0; i < l1; i++)
        {
            mat1[i] = (int *)malloc(c1 * sizeof(int));
        }
        // Alocar Memória da Matriz 2
        mat2 = (int **)malloc(l2 * sizeof(int *));
        for (i = 0; i < l2; i++)
        {
            mat2[i] = (int *)malloc(c2 * sizeof(int));
        }
        // Alocar Memória da Matriz Multiplicada
        res = (int **)calloc(l1, sizeof(int *));
        for (i = 0; i < l1; i++)
        {
            res[i] = (int *)calloc(c2, sizeof(int));
        }
        // Digitar Elementos da Matriz
        printf("\nDigite cada elemento da matriz 1: \n");
        for (i = 0; i < l1; i++)
        {
            for (j = 0; j < c1; j++)
            {
                scanf("%d", &mat1[i][j]);
            }
        }
        // Digitar Elementos da Matriz 2
        printf("\nDigite cada elemento da matriz 2: \n");
        for (i = 0; i < l2; i++)
        {
            for (j = 0; j < c2; j++)
            {
                scanf("%d", &mat2[i][j]);
            }
        }
        // Print Matriz 1
        printf("\nPrimeira Matriz: \n");
        for (i = 0; i < l1; i++)
        {
            for (j = 0; j < c1; j++)
            {
                printf("%d ", mat1[i][j]);
            }
            printf("\n");
        }
        // Print Matriz 2
        printf("\nSegunda Matriz: \n");
        for (i = 0; i < l2; i++)
        {
            for (j = 0; j < c2; j++)
            {
                printf("%d ", mat2[i][j]);
            }
            printf("\n");
        }

        //chamando a função (multiplicarMatriz())
        multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, 0, 0, 0);

        // Resultado da Matéria
        printf("\nMultiplicação das Duas Matrizes:\n");
        for (i = 0; i < l1; i++)
        {
            for (j = 0; j < c2; j++)
            {
                printf("%d\t", res[i][j]);
            }
            printf("\n");
        }
        // Liberar Memória
        for (i = 0; i < l1; i++)
        {
            free(mat1[i]);
        }

        free(mat1);
        for (i = 0; i < l2; i++)
        {
            free(mat2[i]);
        }

        free(mat2);
        for (i = 0; i < l1; i++)
        {
            free(res[i]);
        }

        free(res);

        //interação de loop com o usuário
        int r = 1;
        
        do
        {
            
            printf("\nDeseja repetir o processso? 1 = SIM / 0 = NÃO -> ");
            scanf("%d", &r);
            if (r == 0)
            {
                exit(0);
            }
        } while (0 > r || 1 < r);
        
    }
    return 0;
}
