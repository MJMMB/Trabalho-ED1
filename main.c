#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// fun��o limpar buffer
void limpar()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

// fun��o para ler entradas, evitando quaisquer erros digitados pelo usu�rio
void ler_entrada(char *buffer, int tamanho)
{
    if (fgets(buffer, tamanho, stdin) == NULL)
    {
        buffer[0] = '\0';
        clearerr(stdin);
    }   
    buffer[strcspn(buffer, "\n")] = '\0';
}

// Fun��o para ler inteiros com valida��o (para as dimens�es das matrizes)
int validar_entradas(const char *prompt, int min, int max) 
{   
    char buffer[100];
    
    while (1) {
        printf("%s ", prompt);
        ler_entrada(buffer, sizeof(buffer));
        
        char *ptr;
        long num = strtol(buffer, &ptr, 10);
        
        if (ptr == buffer || *ptr != '\0') {
            printf("Erro: Digite apenas n�meros inteiros.\n");
            limpar();
            continue;
        }
        
        if (num < min || num > max) {
            printf("Erro: Valor incorreto, tente novamente.\n");
            limpar();
            continue;
        }
        
        return (int)num;
    }
}

// Fun��o para ler valores float com valida��o (para os elementos das matrizes)
float validar_entradas_float(const char *prompt)
{
    char buffer[100];
    
    while (1) {
        printf("%s ", prompt);
        ler_entrada(buffer, sizeof(buffer));
        
        char *ptr;
        float num = strtof(buffer, &ptr);
        
        if (ptr == buffer || *ptr != '\0') {
            printf("Erro: Digite apenas n�meros v�lidos (use ponto para float).\n");
            continue;
        }
        
        return num;
    }
}

// func�o recursiva para multiplica��o de matrizes (agora com floats)
void multiplicarMatriz(float **mat1, float **mat2, float **res, int l1, int c1, int l2, int c2, int linha, int coluna, int k)
{
    if(!mat1 || !mat2 || !res) 
    {
        printf("\n Erro ao alocar mem�ria.");
        exit(1);
    }

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
        float **mat1, **mat2, **res;
        int i, j, l1, c1, l2, c2;

        // Verifica se Multiplica��o � Poss�vel
        do
        {
            // Dimens�o das Matrizes
            printf("\nDigite Linhas e Colunas da Primeira Matriz:\n");
            l1 = validar_entradas(" Numero de linhas (1 a 100):", 1, 100);
            c1 = validar_entradas(" Numero de colunas (1 a 100):", 1, 100);
            
            printf("\nDigite Linhas e Colunas da Segunda Matriz:\n");
            l2 = validar_entradas(" Numero de linhas: (1 a 100):", 1, 100);
            c2 = validar_entradas(" Numero de colunas: (1 a 100):", 1, 100);
            
            if (c1 != l2)
            {
                printf("Ordem das Matrizes Inv�lidas, tente novamente\n");
            }
        } while (c1 != l2);

        // Alocar Mem�ria da Matriz 1
        mat1 = (float **)malloc(l1 * sizeof(float *));       
        for (i = 0; i < l1; i++)
        {
            mat1[i] = (float *)malloc(c1 * sizeof(float));
        }
        // Alocar Mem�ria da Matriz 2
        mat2 = (float **)malloc(l2 * sizeof(float *));
        for (i = 0; i < l2; i++)
        {
            mat2[i] = (float *)malloc(c2 * sizeof(float));
        }
        // Alocar Mem�ria da Matriz Multiplicada
        res = (float **)calloc(l1, sizeof(float *));
        for (i = 0; i < l1; i++)
        {
            res[i] = (float *)calloc(c2, sizeof(float));
        }
        
        // Digitar Elementos da Matriz 1
        printf("\nDigite cada elemento da matriz 1: \n");
        for (i = 0; i < l1; i++)
        {
            for (j = 0; j < c1; j++)
            {
                printf("Matriz 1 [%d][%d]: ", i+1, j+1);
                mat1[i][j] = validar_entradas_float("");
            }
        }
        
        // Digitar Elementos da Matriz 2
        printf("\nDigite cada elemento da matriz 2: \n");
        for (i = 0; i < l2; i++)
        {
            for (j = 0; j < c2; j++)
            {
                printf("Matriz 2 [%d][%d]: ", i+1, j+1);
                mat2[i][j] = validar_entradas_float("");
            }
        }
        
        // Print Matriz 1
        printf("\nPrimeira Matriz: \n");
        for (i = 0; i < l1; i++)
        {
            for (j = 0; j < c1; j++)
            {
                printf("| %.2f\t", mat1[i][j]);
            }
            printf("|\n");
        }
        
        // Print Matriz 2
        printf("\nSegunda Matriz: \n");
        for (i = 0; i < l2; i++)
        {
            for (j = 0; j < c2; j++)
            {
                printf("| %.2f\t", mat2[i][j]);
            }
            printf("|\n");
        }

        // chamando a fun��o (multiplicarMatriz())
        multiplicarMatriz(mat1, mat2, res, l1, c1, l2, c2, 0, 0, 0);

        // Resultado da Mat�ria
        printf("\nMultiplica��o das Duas Matrizes:\n");
        for (i = 0; i < l1; i++)
        {
            for (j = 0; j < c2; j++)
            {
                printf("| %.2f\t", res[i][j]);
            }
            printf("|\n");
        }
        
        // Liberar Mem�ria
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

        
        // intera��o com o usu�rio com um "loop"
        int opcao = validar_entradas("\nDeseja repetir o processo? 1 = SIM | 0 = N�O -> ", 0, 1);
        if (opcao == 0) {
            break;
        }
        
    }
    return 0;
}