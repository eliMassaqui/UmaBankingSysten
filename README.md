# 💳 UMA Banking System (Simulação em C)

Sistema bancário pessoal feito em linguagem **C**, com funcionalidades completas de gestão de contas, transferências, pagamentos e interação com contatos. Voltado para uso **educacional e demonstrativo**.

---

## 📚 Objetivo

Este sistema simula um banco simples onde o usuário pode:

* Criar e gerenciar **contas bancárias pessoais**
* Realizar **depósitos, levantamentos** e **consultar saldo**
* Fazer **transferências** internas (entre contas do sistema) ou para **contatos externos** (amigos, familiares)
* Efetuar **pagamento de serviços** com planos semanais ou mensais
* Visualizar **contatos cadastrados** (com nome, número e IBAN)
* Armazenar tudo de forma persistente em arquivos `.dat`

---

## 🔹 Funcionalidades detalhadas

### 1. Criar Conta

* Solicita nome do titular (sem acentos)
* Gera número sequencial da conta (1001, 1002, ...)
* Gera automaticamente um **IBAN** (padrão simulado: AO)
* Verifica se o nome já existe (nomes não podem se repetir)
* Saldo inicial é 0.0
* Dados são salvos em `contas.dat`

### 2. Depositar

* Solicita número da conta
* Adiciona valor ao saldo se a conta for encontrada

### 3. Levantar

* Solicita número da conta e valor
* Verifica saldo disponível e realiza o levantamento

### 4. Consultar Saldo

* Exibe dados da conta:

  * Titular
  * Número
  * IBAN
  * Saldo atual

### 5. Transferir

* Solicita conta origem e destino
* Permite transferência para:

  * Outra conta interna (criadas no sistema)
  * Um dos 10 contatos externos
* Verifica saldo, conta e realiza operação

### 6. Pagar Serviço

* Lista três serviços fixos com planos e preços:

| Serviço                | Semanal    | Mensal     | Info Extra          |
| ---------------------- | ---------- | ---------- | ------------------- |
| Netflix                | 5 000 AKZ  | 10 000 AKZ | Plano Family        |
| ENDE Energia           | —          | 8 000 AKZ  | Tarifa única mensal |
| Internet Fixa 100 Mbps | 15 000 AKZ | 30 000 AKZ | Velocidade 100 Mbps |

* O usuário seleciona o serviço e o tipo de plano (quando aplicável)
* O valor é debitado diretamente da conta

### 7. Ver Contatos

* Lista os 10 contatos pré-cadastrados com:

  * Nome
  * Número (4 dígitos aleatórios)
  * IBAN

### 8. Sair

* Encerra o sistema e grava os dados persistentes nos arquivos

---

## 📝 Estrutura dos Dados

### `Conta`

```c
typedef struct {
    int numero;
    char nome[50];
    char iban[35];
    float saldo;
} Conta;
```

### `Contato`

```c
typedef struct {
    int numero;
    char nome[50];
    char iban[35];
} Contato;
```

---

## 🔄 Geração do IBAN (simulada)

* Formato: `AOxx00010001##########`
* Estrutura:

  * Prefixo fixo: Banco 0001 + Conta de 10 dígitos
  * Verificação de controle com algoritmo mod 97
* Exemplo:

```
AO71 0001 0001 0000 0000 1001
```

---

## 📂 Armazenamento de Dados

### Arquivos utilizados:

| Ficheiro       | Conteúdo                             |
| -------------- | ------------------------------------ |
| `contas.dat`   | Lista de contas criadas pelo usuário |
| `contatos.dat` | Lista de 10 contatos predefinidos    |

* Arquivos binários simples
* Gerados automaticamente caso não existam

---

## 🚀 Execução e Compilação

### Compilar (Linux/macOS):

```bash
gcc banco.c -o banco
```

### Compilar (Windows):

```cmd
gcc banco.c -o banco.exe
```

### Executar:

```bash
./banco
```

---

## 🎯 Exemplo de Uso

```bash
--- UMA BANKING SYSTEM ---
1 Criar Conta
2 Depositar
...
Escolha: 1
Nome do titular: ELIAS
Conta criada! Numero 1001 | IBAN AO71...

Escolha: 2
Numero da conta: 1001
Valor do deposito: 20000
Deposito ok! Saldo 20000.00
```

---

## 💡 Ideias Futuras

* Sistema de login (com PIN por conta)
* Exportação de extratos e histórico
* Interface gráfica (modo texto com ncurses ou SDL)
* Relatórios mensais e balanços

---

## 👍 Para que serve esse projeto?

* Aprender sobre **structs**, **arquivos binários** e **modularização em C**
* Simular um ambiente bancário offline
* Desenvolver lógica de negócio
* Aplicar boas práticas na manipulação de dados

---

## 🌐 Autor

**Elísio Massaqui**
Estudante de Engenharia Informática
Universidade Metodista de Angola

---

## 📄 Licença

Este projeto é livre para uso acadêmico e pessoal.
Sinta-se à vontade para melhorar, traduzir ou adaptar.

---

> Projeto criado com foco em aprendizagem de C puro, manipulação de arquivos e gestão de dados bancários simulados.
