# UMA Banking System (Projeto Em C)

Sistema bancário **offline** de consola, pensado para aprendizagem de C puro.

---

## 📑 Funcionalidades

| # | Função                              | Descrição curta                                                                           |
|:-:|-------------------------------------|-------------------------------------------------------------------------------------------|
| 1 | **Criar conta**                     | Nome único, número sequencial (1001…), IBAN gerado, saldo 0                                |
| 2 | **Depositar**                       | Aumenta saldo da conta escolhida                                                          |
| 3 | **Levantar**                        | Diminui saldo se houver saldo suficiente                                                  |
| 4 | **Consultar saldo + IBAN**          | Mostra titular, número, IBAN e saldo atual                                                |
| 5 | **Transferir dinheiro**             | Conta → Conta (interna) ou Conta → Contato (externo)                                      |
| 6 | **Pagar serviço**                   | Netflix, ENDE Energia, Internet Fixa 100 Mbps (planos semanal/mensal conforme tabela)     |
| 7 | **Ver contatos**                    | Lista 10 contatos pré-cadastrados (amigos/familiares)                                     |
| 8 | **Sair**                            | Encerra o programa preservando os ficheiros `.dat`                                        |

---

## 🗂️ Arquivos gerados

| Ficheiro        | Conteúdo                                      |
|-----------------|-----------------------------------------------|
| `banco.c`       | Código-fonte completo                         |
| `contas.dat`    | Base de dados binária das contas internas     |
| `contatos.dat`  | Base de dados binária dos 10 contatos         |

---

## 💸 Serviços disponíveis

| Serviço                | Plano semanal | Plano mensal | Observação           |
|------------------------|--------------:|-------------:|----------------------|
| Netflix                | 5 000 AKZ     | 10 000 AKZ   |                     |
| ENDE Energia           | —             | 8 000 AKZ    | Tarifa única mensal  |
| Internet Fixa 100 Mbps | 15 000 AKZ    | 30 000 AKZ   | Velocidade 100 Mbps  |

> Valores deduzidos diretamente do saldo da conta.

---

## 🧩 Estruturas de dados

```c
typedef struct {
    int   numero;     // 1001, 1002…
    char  nome[50];   // único
    char  iban[35];   // AOxx00010001##########
    float saldo;
} Conta;

typedef struct {
    int  numero;      // 4 dígitos aleatórios (2000–9999)
    char nome[50];    // amigo/familiar
    char iban[35];
} Contato;
