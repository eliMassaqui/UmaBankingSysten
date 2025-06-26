/*  UMA BANKING SYSTEM
    --------------------------------------------------------
    • Contas internas (nomes unicos) com IBAN gerado
    • Persistencia em arquivo (contas.dat / contatos.dat)
    • 10 contatos pessoais para transferencia
    • 3 servicos fixos com planos semanal / mensal:
        - Netflix ............... 5 000 AKZ (sem) | 10 000 AKZ (men)
        - ENDE Energia ..........            8 000 AKZ (men)
        - Internet Fixa 100 Mbps . 15 000 AKZ (sem) | 30 000 AKZ (men)
    --------------------------------------------------------
    Compilar: gcc banco.c -o banco
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* ----------------- constantes ----------------- */
#define MAX_CONTAS   100
#define N_CONTATOS   10
#define N_SERVICOS    3
#define ARQ_CONTAS   "contas.dat"
#define ARQ_CONTATOS "contatos.dat"

/* ----------------- estruturas ----------------- */
typedef struct {
    int   numero;          /* ex. 1001 */
    char  nome[50];        /* nome unico */
    char  iban[35];        /* IBAN AO..  */
    float saldo;
} Conta;

typedef struct {
    int  numero;           /* 4 digitos  */
    char nome[50];
    char iban[35];
} Contato;

/* ----------------- globais ----------------- */
Conta   contas[MAX_CONTAS];
int     totalContas   = 0;
int     proximoNumero = 1001;

Contato contatos[N_CONTATOS];

/* ----------- servicos, planos e precos ----------- */
const char *SERV_NOME[N_SERVICOS]      = {"Netflix", "ENDE Energia", "Internet Fixa 100Mbps"};
const int   SERV_PRECO_SEM[N_SERVICOS] = {  5000,       -1,             15000 };
const int   SERV_PRECO_MES[N_SERVICOS] = { 10000,        8000,          30000 };

/* ================================================= */
/*  IBAN simplificado: AO + chk + banco 0001 + conta  */
void gerarIBAN(int num, char *out)
{
    char bban[19]; sprintf(bban, "00010001%010d", num);
    char tmp[64];  sprintf(tmp,  "%s102400", bban);   /* AO -> 10 24 */
    int mod = 0;
    for (int i = 0; tmp[i]; ++i)
        mod = (mod * 10 + (tmp[i] - '0')) % 97;
    int chk = 98 - mod;
    sprintf(out, "AO%02d%s", chk, bban);
}

/* ----------------- persistencia contas ----------------- */
void salvarContas(void){
    FILE *fp = fopen(ARQ_CONTAS, "wb");
    if(!fp){ puts("Erro ao salvar contas."); return; }
    fwrite(&totalContas, sizeof(int), 1, fp);
    fwrite(contas, sizeof(Conta), totalContas, fp);
    fclose(fp);
}
void carregarContas(void){
    FILE *fp = fopen(ARQ_CONTAS, "rb");
    if(!fp) return;
    fread(&totalContas, sizeof(int), 1, fp);
    fread(contas, sizeof(Conta), totalContas, fp);
    fclose(fp);
    if(totalContas) proximoNumero = contas[totalContas-1].numero + 1;
}

/* ----------------- persistencia contatos ----------------- */
void gerarContatosPadrao(void){
    const char *nomes[N_CONTATOS] = {
        "Carlos Silva","Ana Paula","Jose Mendes","Maria Luisa",
        "Luis Antonio","Sara Daniel","Pedro Bento","Rita Jorge",
        "Paulo Gomes","Clara Sousa"
    };
    srand((unsigned)time(NULL));
    for(int i=0;i<N_CONTATOS;++i){
        contatos[i].numero = 2000 + rand()%8000;
        strcpy(contatos[i].nome, nomes[i]);
        gerarIBAN(contatos[i].numero, contatos[i].iban);
    }
}
void salvarContatos(void){
    FILE *fp = fopen(ARQ_CONTATOS, "wb");
    if(!fp){ puts("Erro ao salvar contatos."); return; }
    fwrite(contatos, sizeof(Contato), N_CONTATOS, fp);
    fclose(fp);
}
void carregarContatos(void){
    FILE *fp = fopen(ARQ_CONTATOS, "rb");
    if(!fp){ gerarContatosPadrao(); salvarContatos(); return; }
    fread(contatos, sizeof(Contato), N_CONTATOS, fp);
    fclose(fp);
}

/* ----------------- utilidades ----------------- */
int buscarConta(int num){
    for(int i=0;i<totalContas;++i)
        if(contas[i].numero == num) return i;
    return -1;
}
int nomeExiste(const char *nome){
    for(int i=0;i<totalContas;++i)
        if(strcmp(contas[i].nome, nome) == 0) return 1;
    return 0;
}

/* ----------------- operacoes ----------------- */
void criarConta(void){
    if(totalContas >= MAX_CONTAS){ puts("Limite de contas."); return; }

    char nome[50];
    printf("Nome do titular: ");
    scanf(" %49[^\n]", nome);
    if(nomeExiste(nome)){ puts("Ja existe conta com esse nome."); return; }

    Conta c;
    c.numero = proximoNumero++;
    strcpy(c.nome, nome);
    gerarIBAN(c.numero, c.iban);
    c.saldo = 0;
    contas[totalContas++] = c;
    salvarContas();

    printf("Conta criada! Numero %d | IBAN %s\n", c.numero, c.iban);
}
void depositar(void){
    int num; float v;
    printf("Numero da conta: "); scanf("%d",&num);
    int i = buscarConta(num); if(i<0){ puts("Conta nao encontrada."); return; }
    printf("Valor do deposito: "); scanf("%f",&v);
    if(v<=0){ puts("Valor invalido."); return; }
    contas[i].saldo += v; salvarContas();
    printf("Deposito ok! Saldo %.2f\n", contas[i].saldo);
}
void levantar(void){
    int num; float v;
    printf("Numero da conta: "); scanf("%d",&num);
    int i = buscarConta(num); if(i<0){ puts("Conta nao encontrada."); return; }
    printf("Valor do levantamento: "); scanf("%f",&v);
    if(v<=0 || v>contas[i].saldo){ puts("Saldo insuficiente ou valor invalido."); return; }
    contas[i].saldo -= v; salvarContas();
    printf("Levantamento ok! Saldo %.2f\n", contas[i].saldo);
}
void consultar(void){
    int num; printf("Numero da conta: "); scanf("%d",&num);
    int i = buscarConta(num); if(i<0){ puts("Conta nao encontrada."); return; }
    printf("Titular: %s\nNumero: %d\nIBAN: %s\nSaldo: %.2f\n",
           contas[i].nome, contas[i].numero, contas[i].iban, contas[i].saldo);
}
void listarContatos(void){
    puts("\n--- CONTATOS ---");
    for(int k=0;k<N_CONTATOS;++k)
        printf("%2d) %s | Numero %d | IBAN %s\n",
               k+1, contatos[k].nome, contatos[k].numero, contatos[k].iban);
}
void transferir(void){
    int orig,dest; float v;
    printf("Conta origem: "); scanf("%d",&orig);
    int i = buscarConta(orig); if(i<0){ puts("Conta origem nao encontrada."); return; }

    printf("Conta destino: "); scanf("%d",&dest);
    int j = buscarConta(dest);
    int idxContato = -1;
    if(j<0){
        for(int k=0;k<N_CONTATOS;++k)
            if(contatos[k].numero == dest){ idxContato=k; break; }
        if(idxContato < 0){ puts("Destino nao existente."); return; }
    }

    printf("Valor da transferencia: "); scanf("%f",&v);
    if(v<=0 || v>contas[i].saldo){ puts("Saldo insuficiente ou valor invalido."); return; }

    contas[i].saldo -= v;
    if(j>=0) contas[j].saldo += v;   /* interna */
    salvarContas();

    if(j>=0) puts("Transferencia interna concluida!");
    else     printf("Transferencia para %s ok!\n", contatos[idxContato].nome);
}

/* ----------------- pagar servico ----------------- */
void pagarServico(void){
    int num; printf("Numero da conta: "); scanf("%d",&num);
    int i = buscarConta(num); if(i<0){ puts("Conta nao encontrada."); return; }

    puts("\n--- SERVICOS DISPONIVEIS ---");
    for(int s=0;s<N_SERVICOS;++s){
        printf("%2d) %s  ", s+1, SERV_NOME[s]);
        if(SERV_PRECO_SEM[s]>0) printf("Sem: %d  ", SERV_PRECO_SEM[s]);
        if(SERV_PRECO_MES[s]>0) printf("Mes: %d", SERV_PRECO_MES[s]);
        puts("");
    }

    int sel; printf("Escolha servico (1-%d): ", N_SERVICOS); scanf("%d",&sel);
    if(sel<1 || sel>N_SERVICOS){ puts("Servico invalido."); return; }
    --sel;

    int preco = -1;
    if(SERV_PRECO_SEM[sel]>0 && SERV_PRECO_MES[sel]>0){
        int op;
        printf("Plano (1 Semanal / 2 Mensal): "); scanf("%d",&op);
        preco = (op==1) ? SERV_PRECO_SEM[sel] : (op==2 ? SERV_PRECO_MES[sel] : -1);
    }else if(SERV_PRECO_SEM[sel]>0){
        puts("Plano semanal selecionado.");
        preco = SERV_PRECO_SEM[sel];
    }else{
        puts("Plano mensal selecionado.");
        preco = SERV_PRECO_MES[sel];
    }

    if(preco<0){ puts("Opcao invalida."); return; }
    if(preco > contas[i].saldo){ puts("Saldo insuficiente."); return; }

    contas[i].saldo -= preco; salvarContas();
    printf("Pagamento '%s' ok. Valor %d  | Saldo %.2f\n",
           SERV_NOME[sel], preco, contas[i].saldo);
}

/* ----------------- menu ----------------- */
void menu(void){
    int op;
    do{
        puts("\n--- UMA BANKING SYSTEM ---");
        puts("1 Criar Conta");
        puts("2 Depositar");
        puts("3 Levantar");
        puts("4 Consultar Saldo + IBAN");
        puts("5 Transferir");
        puts("6 Pagar Servico");
        puts("7 Ver Contatos");
        puts("8 Sair");
        printf("Escolha: ");
        scanf("%d",&op);

        switch(op){
            case 1: criarConta();     break;
            case 2: depositar();      break;
            case 3: levantar();       break;
            case 4: consultar();      break;
            case 5: transferir();     break;
            case 6: pagarServico();   break;
            case 7: listarContatos(); break;
            case 8: puts("Saindo..."); break;
            default: puts("Opcao invalida.");
        }
    }while(op!=8);
}

/* ----------------- main ----------------- */
int main(void){
    carregarContas();
    carregarContatos();
    menu();
    return 0;
}
