#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100

typedef struct {
    int numeroConta;
    char nome[100];
    char bilhete[20];
    char nacionalidade[50];
    char dataNascimento[15];
    float saldo;
    char iban[30];
} Conta;

Conta contas[MAX_CLIENTES];
int totalContas = 0;

// Gerador simples de número de conta e IBAN
int gerarNumeroConta() {
    return 1000 + totalContas;
}

void gerarIBAN(int numeroConta, char* iban) {
    sprintf(iban, "AO06BANK%06d", numeroConta);
}

// Função 1: Abrir conta
void abrirConta() {
    Conta nova;
    nova.numeroConta = gerarNumeroConta();
    printf("Nome completo: ");
    getchar(); fgets(nova.nome, 100, stdin);
    printf("Número do bilhete: ");
    fgets(nova.bilhete, 20, stdin);
    printf("Nacionalidade: ");
    fgets(nova.nacionalidade, 50, stdin);
    printf("Data de nascimento: ");
    fgets(nova.dataNascimento, 15, stdin);
    nova.saldo = 0.0;
    gerarIBAN(nova.numeroConta, nova.iban);

    contas[totalContas++] = nova;
    printf("Conta criada com sucesso! Nº: %d | IBAN: %s\n", nova.numeroConta, nova.iban);
}

// Função 2: Depositar
void depositar() {
    int numero;
    float valor;
    printf("Número da conta: ");
    scanf("%d", &numero);
    printf("Valor do depósito: ");
    scanf("%f", &valor);
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numeroConta == numero) {
            contas[i].saldo += valor;
            printf("Depósito feito. Saldo atual: %.2f\n", contas[i].saldo);
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

// Função 3: Levantar
void levantar() {
    int numero;
    float valor;
    printf("Número da conta: ");
    scanf("%d", &numero);
    printf("Valor do levantamento: ");
    scanf("%f", &valor);
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numeroConta == numero) {
            if (contas[i].saldo >= valor) {
                contas[i].saldo -= valor;
                printf("Levantamento feito. Saldo atual: %.2f\n", contas[i].saldo);
            } else {
                printf("Saldo insuficiente.\n");
            }
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

// Função 4: Consultar
void consultar() {
    int numero;
    printf("Número da conta: ");
    scanf("%d", &numero);
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numeroConta == numero) {
            printf("Nome: %sSaldo: %.2f | IBAN: %s\n", contas[i].nome, contas[i].saldo, contas[i].iban);
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

// Função 5: Transferência
void transferir() {
    int origem, destino;
    float valor;
    printf("Conta origem: ");
    scanf("%d", &origem);
    printf("Conta destino: ");
    scanf("%d", &destino);
    printf("Valor: ");
    scanf("%f", &valor);

    Conta *c1 = NULL, *c2 = NULL;
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numeroConta == origem) c1 = &contas[i];
        if (contas[i].numeroConta == destino) c2 = &contas[i];
    }

    if (c1 && c2 && c1->saldo >= valor) {
        c1->saldo -= valor;
        c2->saldo += valor;
        printf("Transferência concluída.\n");
    } else {
        printf("Erro: Conta(s) inválida(s) ou saldo insuficiente.\n");
    }
}

// Função 6: Pagamento de serviços
void pagarServico() {
    int numero;
    float valor;
    printf("Número da conta: ");
    scanf("%d", &numero);
    printf("Valor do serviço: ");
    scanf("%f", &valor);
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numeroConta == numero) {
            if (contas[i].saldo >= valor) {
                contas[i].saldo -= valor;
                printf("Pagamento realizado. Saldo atual: %.2f\n", contas[i].saldo);
            } else {
                printf("Saldo insuficiente.\n");
            }
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

// Menu principal
void menu() {
    int op;
    do {
        printf("\n--- UMA Banking System ---\n");
        printf("1. Abrir Conta\n2. Depositar\n3. Levantar\n4. Consultar\n5. Transferir\n6. Pagar Serviço\n0. Sair\nEscolha: ");
        scanf("%d", &op);
        switch (op) {
            case 1: abrirConta(); break;
            case 2: depositar(); break;
            case 3: levantar(); break;
            case 4: consultar(); break;
            case 5: transferir(); break;
            case 6: pagarServico(); break;
        }
    } while (op != 0);
}

int main() {
    menu();
    return 0;
}
