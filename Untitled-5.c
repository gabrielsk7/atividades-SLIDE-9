
#include <stdio.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
};

int main() {
    struct Produto produtos[3];
    FILE *arquivo;
    int i;

    for (i = 0; i < 3; i++) {
        printf("\nCodigo do produto: ");
        scanf("%d", &produtos[i].codigo);

        printf("Nome do produto: ");
        scanf(" %49[^\n]", produtos[i].nome);

        printf("Preco: ");
        scanf("%f", &produtos[i].preco);
    }

    arquivo = fopen("estoque.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        fprintf(arquivo, "%d %s %.2f\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].preco);
    }

    fclose(arquivo);

    arquivo = fopen("estoque.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao ler arquivo.\n");
        return 1;
    }

    printf("\n--- ESTOQUE DA LOJA ---\n");

    for (i = 0; i < 3; i++) {
        fscanf(arquivo, "%d %49s %f",
               &produtos[i].codigo,
               produtos[i].nome,
               &produtos[i].preco);

        printf("\nCodigo: %d\n", produtos[i].codigo);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preco: R$ %.2f\n", produtos[i].preco);
    }

    fclose(arquivo);

    return 0;
}
