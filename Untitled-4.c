
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Eleitor {
    char titulo[12];
    int zona;
};

struct Cedula {
    struct Eleitor eleitor;
    int numero_voto;
};

struct Cedula *recuperarVotos(int *quantidade) {
    struct Cedula *votos;
    FILE *arquivo;
    long tamanho;

    arquivo = fopen("urnas.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    tamanho = ftell(arquivo);

    *quantidade = tamanho / sizeof(struct Cedula);

    rewind(arquivo);

    votos = malloc(tamanho);

    if (votos == NULL) {
        printf("Erro na memoria.\n");
        fclose(arquivo);
        return NULL;
    }

    fread(votos, sizeof(struct Cedula), *quantidade, arquivo);

    fclose(arquivo);

    return votos;
}

int main() {
    struct Cedula *votos = NULL;
    struct Cedula *backup;
    int quantidade = 0, i;
    FILE *arquivo;

    char continuar;

    do {
        backup = realloc(votos, (quantidade + 1) * sizeof(struct Cedula));

        if (backup == NULL) {
            printf("Erro na memoria.\n");
            free(votos);
            return 1;
        }

        votos = backup;

        printf("\nTitulo de eleitor: ");
        scanf(" %11s", votos[quantidade].eleitor.titulo);

        printf("Zona eleitoral: ");
        scanf("%d", &votos[quantidade].eleitor.zona);

        printf("Numero do voto: ");
        scanf("%d", &votos[quantidade].numero_voto);

        quantidade++;

        printf("Deseja cadastrar outro voto? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's');

    arquivo = fopen("urnas.bin", "wb");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo.\n");
        free(votos);
        return 1;
    }

    fwrite(votos, sizeof(struct Cedula), quantidade, arquivo);

    fclose(arquivo);

    printf("\nVotos salvos com sucesso!\n");

    free(votos);

    votos = recuperarVotos(&quantidade);

    if (votos != NULL) {
        printf("\n--- VOTOS RECUPERADOS ---\n");

        for (i = 0; i < quantidade; i++) {
            printf("\nTitulo: %s\n", votos[i].eleitor.titulo);
            printf("Zona: %d\n", votos[i].eleitor.zona);
            printf("Voto: %d\n", votos[i].numero_voto);
        }

        free(votos);
    }

    return 0;
}
