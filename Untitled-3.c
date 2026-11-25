
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Professor {
    int registro;
    int horas_aula;
};

void lerArquivo(int quantidade) {
    struct Professor *professores;
    FILE *arquivo;
    int i;

    professores = malloc(quantidade * sizeof(struct Professor));

    if (professores == NULL) {
        printf("Erro na memoria.\n");
        return;
    }

    arquivo = fopen("folha.dat", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        free(professores);
        return;
    }

    fread(professores, sizeof(struct Professor), quantidade, arquivo);

    printf("\n--- PROFESSORES CADASTRADOS ---\n");

    for (i = 0; i < quantidade; i++) {
        printf("\nRegistro: %d\n", professores[i].registro);
        printf("Horas aula: %d\n", professores[i].horas_aula);
    }

    fclose(arquivo);
    free(professores);
}

int main() {
    struct Professor *professores;
    char *buffer;
    FILE *arquivo;
    int quantidade, i;

    printf("Quantos professores deseja cadastrar? ");
    scanf("%d", &quantidade);

    professores = malloc(quantidade * sizeof(struct Professor));
    buffer = malloc(quantidade * sizeof(struct Professor));

    if (professores == NULL || buffer == NULL) {
        printf("Erro na memoria.\n");
        free(professores);
        free(buffer);
        return 1;
    }

    for (i = 0; i < quantidade; i++) {
        printf("\nRegistro do professor: ");
        scanf("%d", &professores[i].registro);

        printf("Horas de aula: ");
        scanf("%d", &professores[i].horas_aula);
    }

    memcpy(buffer, professores,
           quantidade * sizeof(struct Professor));

    arquivo = fopen("folha.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo.\n");
        free(professores);
        free(buffer);
        return 1;
    }

    fwrite(buffer, sizeof(struct Professor), quantidade, arquivo);

    fclose(arquivo);

    printf("\nDados salvos com sucesso!\n");

    free(professores);
    free(buffer);

    lerArquivo(quantidade);

    return 0;
}
