
#include <stdio.h>

struct Cliente {
    int conta_corrente;
    char nome[50];
    float saldo;
};

int main() {
    struct Cliente cliente;
    FILE *arquivo;
    int conta, encontrado = 0;
    float valor;
    char operacao;

    printf("Digite a conta corrente: ");
    scanf("%d", &conta);

    printf("Digite D para deposito ou S para saque: ");
    scanf(" %c", &operacao);

    printf("Digite o valor: ");
    scanf("%f", &valor);

    arquivo = fopen("clientes.bin", "rb+");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo) == 1) {
        if (cliente.conta_corrente == conta) {
            if (operacao == 'D' || operacao == 'd') {
                cliente.saldo = cliente.saldo + valor;
                encontrado = 1;
            } else if (operacao == 'S' || operacao == 's') {
                if (cliente.saldo >= valor) {
                    cliente.saldo = cliente.saldo - valor;
                    encontrado = 1;
                } else {
                    printf("Saldo insuficiente.\n");
                }
            }

            if (encontrado == 1) {
                fseek(arquivo, -(long)sizeof(struct Cliente), SEEK_CUR);

                fwrite(&cliente, sizeof(struct Cliente), 1, arquivo);

                printf("\nSaldo atualizado: R$ %.2f\n", cliente.saldo);
            }

            break;
        }
    }

    if (encontrado == 0) {
        printf("Conta nao encontrada ou operacao nao realizada.\n");
    }

    fclose(arquivo);

    return 0;
}
