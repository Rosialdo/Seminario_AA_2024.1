#include <stdio.h>
#include <stdlib.h>

void sum_elements(int *array, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {  // Espera apenas um argumento (arquivo de entrada)
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");

    if (!infile) {
        return 1;
    }

    int n;
    fscanf(infile, "%d", &n); // Lê o número de elementos

    int *array = (int *)malloc(n * sizeof(int));  // Aloca memória para o array

    if (!array) {
        fclose(infile);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(infile, "%d", &array[i]); // Lê os elementos do arquivo
    }

    sum_elements(array, n);

    // Fechar o arquivo de entrada
    fclose(infile);
    free(array);  // Libera a memória alocada para o array

    return 0;
}
